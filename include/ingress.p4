#define CMS_HEIGHT 2048
#define DROP_VALUE 150000
#define ECN_VALUE 100000

#define THRESHOLD_INI 5000000
#define RATE_INI 0
#define TOLERANCE 20000
#define TERNARY_NEG_CHECK 32w0x80000000 &&& 32w0x80000000
#define TERNARY_POS_CHECK 32w0 &&& 32w0x80000000
#define TERNARY_ZERO_CHECK 32w0 &&& 32w0xffffffff
#define MINUEND 4294967295


control FSMMF_igr(
        inout header_t hdr, 
        inout metadata_t md,
        inout ingress_intrinsic_metadata_for_deparser_t ig_dprsr_md,
        in ingress_intrinsic_metadata_t ig_intr_md,        
        inout ingress_intrinsic_metadata_for_tm_t ig_tm_md) {

    #include "ingress_objects.p4"
    apply {
        tiForward.apply();
        aiSetfid();
        // tiSetfid.apply();
        aiFcount();
        aiSetTableKey();

        // ********************** compute  RC ******************** //
        // ∆t = ts - last_time
        // RC(t, f) = RC(last_time, f) + pkt_len - ∆t*rate

        aiTs(); //  ts = copy(ingress_mac_tstamp);
        aiCaldT(); //  ∆t = ts - last_time 
        test_dt();
        tiCalc_log_dt.apply(); 
        // lookup table to get rate
        tiRate.apply();       
        test_rate();

        // compute ∆t*rate
        tiCalc_dt_x_rate.apply();
        test_dt_x_rate();

        //compute new RC 
        aiSetpktlen();
        // test_pktlen();
        aiCalc_pktlen_minus_dt_x_rate();
        aiSetRC();
        
        tiRC_nag.apply();

        // ******************** burst control ***************** //
        aiSetburstStage();
        if (ifburstStage == 1) { 
            aiCalcbursttolerance();
            aiTs_ms();
            aiCalburst_t();
        }
        if ( dt_ms != 0) {
            aiCalc_gapRC();
        }
        aiCalc_gap_minus_tolerance();  
        tiGapRC_pos.apply();
        test_burstdrop();
        test_gapRC();
        

        // ******************** rate control ****************** //
        //Threshold < RC(t, f): drop
        // udp drop_flag
        bit<1> drop_flag = 0;
        md.bottlenecked_flag = 0;
        aiCal_RC_minus_threshold(); 
        if (RC_minus_threshold != 0) {
            drop_flag = 0x1;
            aiSetdropflag();
            aiSetecnflag();
        }
        else {
            aiSetnodropflag();
            aiSetnoecnflag(); 
        }

        if (RC_nag == 1){
            md.bottlenecked_flag = 1;
            aiSetBottleneck();
        }
        

        bool tcp_isValid=hdr.tcp.isValid();
        if (tcp_isValid) {
            if(tcp_drop_flag!=0){
                ig_dprsr_md.drop_ctl = 1;
            }else if(burst != 0 && gapRC != 0 && RC_nag == 0){
                ig_dprsr_md.drop_ctl = 1;
            }else if(hdr.ip.ecn != 0 && ecn_flag!=0){
                hdr.ip.ecn = 0b11;
                ig_dprsr_md.drop_ctl = 0;
            }else if(ecn_flag!=0){
                ig_dprsr_md.drop_ctl = 1;
            }else {
                ig_dprsr_md.drop_ctl = 0;
            }
        }
        else if (!tcp_isValid){
            if(drop_flag!=0){
                ig_dprsr_md.drop_ctl = 1;
            }else if(burst != 0 && gapRC != 0 && RC_nag != 0){
                ig_dprsr_md.drop_ctl = 1;
            }else{
                ig_dprsr_md.drop_ctl = 0;
            }
        }
    
    }
}          

