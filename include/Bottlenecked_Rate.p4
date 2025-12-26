control Bottlenecked_Rate(
                          in bit<32> src_ip,
                          in bit<32> dst_ip,
                          in bit<8> proto,
                          in bit<16> src_port,
                          in bit<16> dst_port,
                          in bit<32> sketch_input,
                          out bit<32> sketch_output,
                          in bit<11> fid)  {

    Lpf<bit<32>, bit<11>>(size=CMS_HEIGHT) lpf_1;
    Lpf<bit<32>, bit<11>>(size=CMS_HEIGHT) lpf_2;
    Lpf<bit<32>, bit<11>>(size=CMS_HEIGHT) lpf_3;

    bit<32> cms_output_1_;
    bit<32> cms_output_2_;
    bit<32> cms_output_3_;

    Hash<bit<11>>(HashAlgorithm_t.CRC16) hash_1;
    Hash<bit<11>>(HashAlgorithm_t.CRC16) hash_2;
    Hash<bit<11>>(HashAlgorithm_t.CRC16) hash_3;



    action read_cms_act1_() {
        cms_output_1_ = (bit<32>) lpf_1.execute(sketch_input, 
                                                   hash_1.get({ src_ip,
                                                                dst_ip,
                                                                proto,
                                                                src_port,
                                                                dst_port}));
    }
    action read_cms_act2_() {
        cms_output_2_ = (bit<32>) lpf_2.execute(sketch_input,
                                                   hash_2.get({ src_ip,
                                                                3w0,
                                                                dst_ip,
                                                                3w0,
                                                                proto,
                                                                src_port,
                                                                dst_port}));
    }
    action read_cms_act3_() {
        cms_output_3_ = (bit<32>) lpf_3.execute(sketch_input,
                                                   hash_3.get({ src_ip,
                                                                dst_ip,
                                                                2w0,
                                                                proto,
                                                                2w0,
                                                                src_port,
                                                                1w0,
                                                                dst_port}));
    }

    Register<bit<32>, bit<11>>(2048, 0) bottleneckedRate; 
    RegisterAction<bit<32>, bit<11>, bit<32>>(bottleneckedRate) raSetbottleneckedRate = {
        void apply(inout bit<32> mem, out bit<32> rv){
            mem = sketch_output;
        }
    };
    apply {

        read_cms_act1_();
        read_cms_act2_();
        read_cms_act3_();

        // Get the minimum of all register contents
        sketch_output = min<bit<32>>(cms_output_1_, cms_output_2_);
        sketch_output = min<bit<32>>(sketch_output, cms_output_3_);
        sketch_output = sketch_output>>8; 

        raSetbottleneckedRate.execute(fid);

    }
}
