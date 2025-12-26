
    action aiSetEgress(bit<9> egr_port) {
        ig_tm_md.ucast_egress_port = egr_port;
    }
    action aiNoop(){ }
    table tiForward {
        key = {
            hdr.ethernet.dst_addr : exact;
        }
        actions = {
            aiSetEgress;
            aiNoop();
        }
        const default_action = aiNoop();
    }

    // *********************** hash flow ********************** //
    // md.fid = hash_index.get({hdr.ip.src_addr, hdr.ip.dst_addr, hdr.ip.protocol, md.sport, md.dport})
    // The fCount register is used to store the number of packets bytes in a flow
    Hash<bit<11>>(HashAlgorithm_t.CRC16) hash_index;
    Register<bit<32>, bit<11>>(2048, 0) fCount;
    RegisterAction<bit<32>, bit<11>, bit<32>>(fCount) raFCount = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = (bit<32>) hdr.ip.total_len;
        }
    };
    action aiSetfid() {
        md.fid = hash_index.get({hdr.ip.src_addr, hdr.ip.dst_addr, hdr.ip.protocol, md.sport, md.dport});
    }

//     action aiSetfid(bit<11> fid) {
//         md.fid = fid;
//     }
//     table tiSetfid {
//         key = {
//             hdr.ip.src_addr : exact;
//             hdr.ip.dst_addr : exact;
//             md.dport : exact;
//         }
//         actions = {
//             aiSetfid;
//             aiNoop();
//         }
//         const default_action = aiNoop();
//         const entries = {
// #include "tiSetfid_const_entries.p4inc"
//         }
//     }

    bit<32> table_key;
    action aiSetTableKey() {
        table_key = (bit<32>) md.fid;
    }
    action aiFcount(){
        raFCount.execute(md.fid);
    }

    // **************************** compute RC *************************** //  
    // ∆t = ts - last_time
    // RC(t, f) = RC(last_time, f) + pkt_len - ∆t*rate
    bit<32> dt_LSB;
    bit<32> dt;
    bit<32> ts;
    bit<32> rate;

    // compute ∆t = ts - last_time
    CRCPolynomial<bit<32>>(1, false, false, false, 0, 0) identity_poly; 
    Hash<bit<32>>(HashAlgorithm_t.CUSTOM, identity_poly) identity_hasher0;
    Hash<bit<32>>(HashAlgorithm_t.CUSTOM, identity_poly) identity_hasher1;
    Hash<bit<32>>(HashAlgorithm_t.CUSTOM, identity_poly) identity_hasher2;
    action aiTs() {
        ts = identity_hasher1.get({ig_intr_md.ingress_mac_tstamp[38:7]});
    }  

    Register<bit<32>, bit<11>>(2048, 0) riTs;
    RegisterAction<bit<32>, bit<11>, bit<32>>(riTs) raSetTs = {
        void apply(inout bit<32> mem, out bit<32> rv){
            rv = ts - mem;
            mem = ts;
        }
    };
    action aiCaldT() { 
        dt = raSetTs.execute(md.fid);
    }
    
    bit<16> log_dt;
    @hidden
    action aiCalc_log_dt(bit<16> log_d_t) {log_dt = log_d_t;}
    @hidden
    table tiCalc_log_dt {
        key = { dt : ternary; }
        actions = { aiCalc_log_dt; }
        const entries = {
#include "tiCalc_log_dt.p4inc"
        }
    }

    // get rate
    action aiRate(bit<32> Allocate_rate) {
        rate = Allocate_rate;
    }
    table tiRate {
        key = {
            table_key : exact;
        }
        actions = {
            aiRate;
        }
        const default_action = aiRate(RATE_INI);
    }
    

    bit<32> dt_x_rate;
    bit<32> dt_x_rate_B;
    action aiCalc_dt_x_rate(bit<32> Calc_dt_x_rate, bit<32> Calc_dt_x_rate_B) {
        dt_x_rate = Calc_dt_x_rate;
        dt_x_rate_B = Calc_dt_x_rate_B;
    }
    table tiCalc_dt_x_rate {
        key = {
            log_dt : exact;
            rate   : exact;
        }
        actions = {
            aiCalc_dt_x_rate;
        }
        size = 2048;
        default_action = aiCalc_dt_x_rate(1, 1);
    }
    
    
    // compute ∆t*rate - pkt_len
    // compute threshold - (pkt_len - ∆t*rate)
    // bit<32> pktlen;
    action aiSetpktlen() {
        md.pktlen = identity_hasher0.get({hdr.ip.total_len>>6});
    }
    bit<32> pktlen_minus_dt_x_rate;
    action aiCalc_pktlen_minus_dt_x_rate() {
       pktlen_minus_dt_x_rate = md.pktlen - dt_x_rate_B;
    }

    Register<bit<32>,bit<11>>(2048, 0) riRC;
    RegisterAction<bit<32>, bit<11>, bit<32>>(riRC) raSetRC = {
        void apply(inout bit<32> mem, out bit<32> rv){   
            rv = mem + pktlen_minus_dt_x_rate;  
            if (mem > THRESHOLD_INI) {  
                mem = mem - dt_x_rate_B;
            }
            else {
                mem = rv;
            }
            
        }
    };
    action aiSetRC() {
        md.RC = raSetRC.execute(md.fid);
    }

    bit<1> RC_nag = 0;
    action aiRC_neg() {
        RC_nag = 1;
        md.RC = 0;
    }
    action aiRC_pos() { }
    table tiRC_nag {
        key = {
            md.RC : ternary;
        }
        actions = {
            aiRC_neg;
            aiRC_pos;
        }
        const entries = {
            TERNARY_NEG_CHECK : aiRC_neg();
            TERNARY_POS_CHECK : aiRC_pos();
            TERNARY_ZERO_CHECK : aiRC_neg();
        }
        
    }

    // ******************** burst control ***************** //
    bit<1> ifburstStage;
    bit<32> ts_ms = 0;
    bit<32> dt_ms = 0;
    bit<32> gapRC = 0;
    bit<32> bursttolerance = 0;
    bit<32> gap_minus_tolerance = 0;
    bit<32> burst = 0;
    Register<bit<32>,bit<11>>(2048, 1) riburstStage;
    RegisterAction<bit<32>, bit<11>, bit<32>>(riburstStage) raburstStage = {
        void apply(inout bit<32> mem, out bit<32> rv){   
            rv = mem;
        }
    };
    action aiSetburstStage() { 
        ifburstStage = (bit<1>) raburstStage.execute(md.fid);
    }
    action aiCalcbursttolerance() {
        bursttolerance = rate << 3;
    }
    action aiTs_ms() { 
        ts_ms = identity_hasher2.get({ig_intr_md.ingress_mac_tstamp[43:12]});
    }
    Register<bit<32>, bit<11>>(2048, 0) ri_ts_ms;
    RegisterAction<bit<32>, bit<11>, bit<32>>(ri_ts_ms) ra_ts_ms = {
        void apply(inout bit<32> mem, out bit<32> rv){
            rv = ts_ms - mem;
            mem = ts_ms;
        }
    };
    action aiCalburst_t() { 
        dt_ms = ra_ts_ms.execute(md.fid);
    }
    Register<bit<32>, bit<11>>(2048, 0) ri_gapRC;
    RegisterAction<bit<32>, bit<11>, bit<32>>(ri_gapRC) ra_gapRC = {
        void apply(inout bit<32> mem, out bit<32> rv){
            rv = md.RC |-| mem;
            mem = md.RC;
        }
    };
    action aiCalc_gapRC() { 
        gapRC = ra_gapRC.execute(md.fid);
    }
    action aiCalc_gap_minus_tolerance() {
        burst = gapRC |-| TOLERANCE;
    } 
    
    action aiGapRC_neg() {
        gapRC = 0;
    }
    action aiGapRC_pos() { }
    table tiGapRC_pos {
        key = {
            gapRC : ternary;
        }
        actions = {
            aiGapRC_neg; 
            aiGapRC_pos;
        }
        const entries = {
            TERNARY_NEG_CHECK : aiGapRC_neg();
            TERNARY_POS_CHECK : aiGapRC_pos();
            TERNARY_ZERO_CHECK : aiGapRC_neg();
        }
        
    }


    // ********************** rate control  ******************* //
    bit<32> RC_minus_threshold;
    action aiCal_RC_minus_threshold() {
        RC_minus_threshold = md.RC |-| THRESHOLD_INI;
    }

    bit<1> tcp_drop_flag = 0;
    bit<8> ecn_flag = 1;
    Register<bit<32>, bit<11>>(size=2048) count_til_drop;
    Register<bit<32>, bit<11>>(size=2048) count_til_ecn;
    RegisterAction<bit<32>, bit<11>, bit<8>>(count_til_drop) periodic_drop = {
        void apply(inout bit<32> stored, out bit<8> returned) {
            if (stored < (bit<32>) hdr.ip.total_len) {
                stored = DROP_VALUE;
                returned = 1;
            } else {
                stored = stored - (bit<32>) hdr.ip.total_len;
                returned = 0;
            }
        }
    };
    RegisterAction<bit<32>, bit<11>, bit<8>>(count_til_drop) periodic_nodrop = {
        void apply(inout bit<32> stored, out bit<8> returned) {
            if (stored < (bit<32>) hdr.ip.total_len) {
                stored = 0;
                returned = 0;
            } else {
                stored = stored - (bit<32>) hdr.ip.total_len;
                returned = 0;
            }
        }
    };
    RegisterAction<bit<32>, bit<11>, bit<8>>(count_til_ecn) flag_ecn = {
        void apply(inout bit<32> stored, out bit<8> returned) {
            if (stored < (bit<32>) hdr.ip.total_len) {
                stored = ECN_VALUE;
                returned = 1;
            } else {
                stored = stored - (bit<32>) hdr.ip.total_len;
                returned = 0;
            }
        }
    };
    RegisterAction<bit<32>, bit<11>, bit<8>>(count_til_ecn) flag_noecn = {
        void apply(inout bit<32> stored, out bit<8> returned) {
            if (stored < (bit<32>) hdr.ip.total_len) {
                stored = 0;
                returned = 0;
            } else {
                stored = stored - (bit<32>) hdr.ip.total_len;
                returned = 0;
            }
        }
    };
    action aiSetdropflag() {
        tcp_drop_flag = (bit<1>) periodic_drop.execute(md.fid);
    }
    action aiSetecnflag() {
        ecn_flag = flag_ecn.execute(md.fid);
    }
    action aiSetnodropflag() {
        tcp_drop_flag = (bit<1>) periodic_nodrop.execute(md.fid);
    }
    action aiSetnoecnflag() {
        ecn_flag = flag_noecn.execute(md.fid);
    }


    
    Register<bit<32>, bit<11>>(2048, 0) bottleneckF;
    RegisterAction<bit<32>, bit<11>, bit<32>>(bottleneckF) raSetBottleneckF = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = 1;
        }
    };
    action aiSetBottleneck() {
        raSetBottleneckF.execute(md.fid);
    }




    
// // test
    Register<bit<32>, bit<11>>(2048, 0) ritestburstdrop;
    RegisterAction<bit<32>, bit<11>, bit<32>>(ritestburstdrop) ratestburstdrop = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            if(burst != 0) {
                mem = burst;
            }
            
        }
    };

    action test_burstdrop() {
        ratestburstdrop.execute(md.fid);
    }
    Register<bit<32>, bit<11>>(2048, 0) ritestgapRC;
    RegisterAction<bit<32>, bit<11>, bit<32>>(ritestgapRC) ratestgapRC = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            if (gapRC != 0) {
                mem = gapRC;
            }
            
        }
    };
    action test_gapRC() {
        ratestgapRC.execute(md.fid);
    }

    
    Register<bit<32>, bit<11>>(2048, 0) ridt;
    RegisterAction<bit<32>, bit<11>, bit<32>>(ridt) radt = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = dt;
        }
    };

    action test_dt() {
        radt.execute(md.fid);
    }

    Register<bit<32>, bit<11>>(2048, 0) ri_lograte;
    RegisterAction<bit<32>, bit<11>, bit<32>>(ri_lograte) ra_lograte = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = rate;
        }
    };
    action test_rate() {
        ra_lograte.execute(md.fid);
    }

    Register<bit<32>, bit<11>>(2048, 0) ri_dt_x_rate;
    RegisterAction<bit<32>, bit<11>, bit<32>>(ri_dt_x_rate) ra_dt_x_rate = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = dt_x_rate_B;
        }
    };
    action test_dt_x_rate() {
        ra_dt_x_rate.execute(md.fid);
    }







