/*
 * The structure of this file is inspired by the Cebinae project:
 *   https://github.com/eniac/Cebinae
 *
 * All implementation in this file is original unless otherwise stated.
*/

#include "libs/mgr.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <tofino/pdfixed/pd_common.h>
#include <pipe_mgr/pipe_mgr_intf.h>
#include <pipe_mgr/pipe_mgr_mirror_intf.h>
#include <dvm/bf_drv_intf.h>

#include <tofino/pdfixed/pd_ms.h>

#include <time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <bfsys/bf_sal/bf_sys_assert.h>
#include <bfsys/bf_sal/bf_sys_sem.h>
#include <bfsys/bf_sal/bf_sys_mem.h>
    
#ifdef __cplusplus
}
#endif

#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <set>
#include <map>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

// platform level configuration
#define NUM_FID 2048
// Builtins for using the tofino drivers
#define PIPE_MGR_SUCCESS 0
#define ALL_PIPES 0xffff
#define NUM_PIPES 2 
#define TEST_PIPE 1

#define THRESHOLD 85
#define CAPACITY 96
#define ERROR 0.4
#define BURSTY 200000

#include "pd_helpers.hpp"


p4_pd_dev_target pd_dev_tgt_tables;
p4_pd_sess_hdl_t pd_sess_hdl;
void setup_dev_tgt() {
  pd_sess_hdl = 1;
  pd_dev_tgt_tables.device_id = 0;
  pd_dev_tgt_tables.dev_pipe_id = ALL_PIPES;
}

typedef p4_pd_status_t (*range_reader_t)(p4_pd_sess_hdl_t, p4_pd_dev_target_t, int, int, int, uint32_t*, uint32_t*, int*); 
typedef p4_pd_status_t (*reset_t)(p4_pd_sess_hdl_t, p4_pd_dev_target_t);
void range_read_by_fcn(range_reader_t reader, uint32_t *read_vals, int count){
    int flags = REGISTER_READ_HW_SYNC; // sync with hw
    auto idx = 0;
    uint32_t num_actually_read; // per pipe, should equal count if success
    uint32_t regvals[count*NUM_PIPES]; // for all pipes 
    int value_count;
    p4_pd_status_t pd_status = reader(
        pd_sess_hdl, pd_dev_tgt_tables, idx, 
        count, flags, &num_actually_read, 
        regvals, &value_count);
    if (pd_status != 0) {
        cout << "[FSMMF_CONTROL] [range_read] pd_status error." << endl;
    }
    // assumes only 1 pipe, otherwise the results would be striped
    for (int i = 0; i < count; i+=1) {
        // read just the values for the test pipe
        auto addr = (i * NUM_PIPES) + TEST_PIPE;
        read_vals[i] = regvals[addr];
    }    
    return;
}
void reset_by_fcn(reset_t resetter) {
    p4_pd_status_t pd_status = resetter(
        pd_sess_hdl, pd_dev_tgt_tables);
    if (pd_status != 0) {
        cout << "[FSMMF_CONTROL] [reset_by_fcn] pd_status error." << endl;
    }    
}

void fCount_read(uint32_t *pkt_count) {
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_fCount, pkt_count, NUM_FID);
  reset_by_fcn(p4_pd_fsmmf_register_reset_all_Ingress_t_igr_fCount);
}
void riBottleneckedF_read(uint32_t *bottleneckedflow) {
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_bottleneckF, bottleneckedflow, NUM_FID);
  reset_by_fcn(p4_pd_fsmmf_register_reset_all_Ingress_t_igr_bottleneckF);
}
void riRate_read(uint32_t *rate) {
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_bottlenecked_rate_bottleneckedRate, rate, NUM_FID);
}

void riRC_read(uint32_t *fid_RC) {
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_riRC, fid_RC, NUM_FID);
}


void ridt_read(uint32_t *test_dt) {
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_ridt,test_dt, NUM_FID);
}
void ri_dt_x_rate_read(uint32_t *test_dt_x_rate) {
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_dt_x_rate,test_dt_x_rate, NUM_FID);
}
void rirate_read(uint32_t *test_rate){
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_lograte,test_rate, NUM_FID);
}
void ri_burststage_read(uint32_t *test_burststage, uint32_t *test_burstdrop, uint32_t *test_gapRC) {
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_riburstStage, test_burststage, NUM_FID);
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestburstdrop, test_burstdrop, NUM_FID);
  range_read_by_fcn(p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestgapRC, test_gapRC, NUM_FID);
}



map<uint32_t, p4_pd_entry_hdl_t> tiRate_entries; 
void Rate_update(uint32_t fid, uint32_t fid_rate){

  p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t acnSpec;
  acnSpec.action_Allocate_rate = htonl(fid_rate);

  if(tiRate_entries.find(fid) == tiRate_entries.end()) {
    p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec matchSpec;
    matchSpec.table_key = htonl(fid);
    p4_pd_entry_hdl_t entry_hdl;
    p4_pd_status_t pd_status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate(
      pd_sess_hdl, pd_dev_tgt_tables, &matchSpec, &acnSpec, &entry_hdl);
    if (pd_status != 0) {
            std::cout << "[FSMMF_CONTROL] [tiRate.add] pd_status error." << std::endl;
    }
    tiRate_entries[fid] = entry_hdl;
  }
  else {
    p4_pd_status_t pd_status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate(
      pd_sess_hdl, pd_dev_tgt_tables.device_id, tiRate_entries[fid], &acnSpec);
    if (pd_status != 0) {
      std::cout << "[FSMMF_CONTROL] [tiRate.modify] pd_status error." << std::endl;
    }
  }
  return;
}

using DtRateKey = std::pair<uint16_t, uint32_t>;
std::map<DtRateKey, p4_pd_entry_hdl_t> tiDt_x_rate_entries;
void rate_x_dt_update(uint16_t log_dt, uint32_t rate, uint32_t dt_x_rate, uint32_t dt_x_rate_B)
{
    p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t acnSpec;
    acnSpec.action_Calc_dt_x_rate   = htonl (dt_x_rate);
    acnSpec.action_Calc_dt_x_rate_B = htonl (dt_x_rate_B);

    p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t matchSpec;
    matchSpec.log_dt = htons (log_dt);
    matchSpec.rate   = htonl (rate);

    DtRateKey key{log_dt, rate};

    auto it = tiDt_x_rate_entries.find(key);
    if (it == tiDt_x_rate_entries.end()) {
        p4_pd_entry_hdl_t entry_hdl;

        p4_pd_status_t pd_status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate(
                pd_sess_hdl, pd_dev_tgt_tables, &matchSpec, &acnSpec, &entry_hdl);

        if (pd_status != 0) {
            std::cout << "[FSMMF_CONTROL] [tiCalc_dt_x_rate.add] pd_status error: "
                      << pd_status << std::endl;
            return;
        }
        tiDt_x_rate_entries.emplace(key, entry_hdl);
    } else {
        p4_pd_status_t pd_status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate(
                pd_sess_hdl, pd_dev_tgt_tables.device_id, it->second, &acnSpec);

        if (pd_status != 0) {
            std::cout << "[FSMMF_CONTROL] [tiCalc_dt_x_rate.modify] pd_status error: "
                      << pd_status << std::endl;
        }
    }
    // std::cout << "[update] log_dt=" << (int)log_dt
    //       << " rate=" << rate
    //       << " dt_x_rate=" << dt_x_rate
    //       << " dt_x_rate_B=" << dt_x_rate_B
    //       << std::endl;
}

void set_RC_neg(uint32_t i, uint32_t val) {
  uint32_t v = val;
  p4_pd_status_t pd_status = p4_pd_fsmmf_register_write_Ingress_t_igr_riRC(pd_sess_hdl, pd_dev_tgt_tables,i,&v);
  if (pd_status != 0) {
       cout << "[RC_write] pd_status error." << endl;
  }
  return;
}
void set_Burstfinish(uint32_t i, uint32_t val) {
  uint32_t v = val;
  p4_pd_status_t pd_status = p4_pd_fsmmf_register_write_Ingress_t_igr_riburstStage(pd_sess_hdl, pd_dev_tgt_tables,i,&v);
  if (pd_status != 0) {
       cout << "[Burst_write] pd_status error." << endl;
  }
  return;
}


void fsmmf_loop() {
  
  cout << "[FSMMF_CONTROL] fsmmf main control loop starting..." << endl;
  set <uint32_t> flowSet;

  uint32_t pkt_count[NUM_FID] = {0};
  uint32_t bottleneckedflow[NUM_FID] = {0}; 
  uint32_t rate[NUM_FID] = {0};
  double rate_Gbps[NUM_FID] = {0.0};
  uint32_t ifburstfinish[NUM_FID] = {0};

  int flow_count = 0; 
  double flow_rate = 0.0;
  uint32_t fid_rate[NUM_FID] = {0}; 
  uint32_t fid_RC[NUM_FID] = {0}; 
  uint32_t fid_rate_update[NUM_FID] = {0};
  
  //test
  uint32_t test_dt[NUM_FID] = {0};
  uint32_t test_rate[NUM_FID] = {0}; 
  uint32_t test_dt_x_rate[NUM_FID] = {0}; 
  uint32_t test_burststage[NUM_FID] = {0};
  uint32_t test_burstdrop[NUM_FID] = {0};
  uint32_t test_gapRC[NUM_FID] = {0};

  auto last_poll_time = std::chrono::high_resolution_clock::now();
  auto last_test_time = std::chrono::high_resolution_clock::now();

  
  while(true) {
    auto poll_time = std::chrono::high_resolution_clock::now();
    auto test_time = std::chrono::high_resolution_clock::now();
    
    if (chrono::duration_cast<chrono::milliseconds>(poll_time - last_poll_time).count() >= 5)  {
      last_poll_time = poll_time;

      riRC_read(fid_RC);
      fCount_read(pkt_count);
      riBottleneckedF_read(bottleneckedflow);
      riRate_read(rate);

      flowSet.clear();
      flow_count = 0;   
      flow_rate = 0.0;
      int bottleneckedflow_count = 0;
      double bottleneckedrate_sum = 0.0;

      for (int i = 1; i < NUM_FID; i++) { 
        if (rate[i] > 0  && pkt_count[i] != 0){
          flowSet.insert(i);
          rate_Gbps[i] = rate[i] / 1500.0;
          flow_count += 1;
        }
      }

      if (!flowSet.empty()) {
        for(int i : flowSet) {
            flow_rate += rate_Gbps[i];
        }

        for (int i : flowSet) {
          if (fid_RC[i] & 0x80000000) {
            set_RC_neg(i, 0);
            // cout << "[FSMMF_CONTROL] RC "<< i << " is negative; reset to 0!"<<endl;
          }else if (ifburstfinish[i]==0 && fid_RC[i]>BURSTY) {
            set_Burstfinish(i, 0);
            ifburstfinish[i] = 1;
          }
        }
      }
      
      if(flow_rate > THRESHOLD) { 
        
        for (int i : flowSet) {
          if (bottleneckedflow[i] != 0 && rate_Gbps[i] != 0) {
            bottleneckedflow_count++;
            bottleneckedrate_sum += rate_Gbps[i];
            // cout << "[FSMMF_CONTROL] flow " << i << " is bottlenecked!" << endl;       
          }
        }

        int unbottleneckedflow_count = flow_count - bottleneckedflow_count;
        double unbottleneckedrate = unbottleneckedflow_count > 0 ? (CAPACITY - bottleneckedrate_sum) / (unbottleneckedflow_count*1.0) : 0;
        uint32_t unbottleneckedrate_update_rag = static_cast<uint32_t> (unbottleneckedrate);


        for (int i : flowSet) {
          if(bottleneckedflow[i] != 0 ) {
            if(rate_Gbps[i] == 0) {
              fid_rate_update[i] = unbottleneckedrate_update_rag;
              // cout << "rate update "<< unbottleneckedrate << endl;
            }
            else {   
            }
          } 
          else { //unbottlenecked flow
            fid_rate_update[i] = unbottleneckedrate_update_rag;
            // cout << "rate update "<< unbottleneckedrate << endl;
          }
          Rate_update(i, fid_rate_update[i]);

        }
        for (uint32_t i = 0; i < 16; ++i) {
          double dt_x_rate_f = (static_cast<double>(1u << i) * unbottleneckedrate) / ERROR;
          uint32_t dt_x_rate = static_cast<uint32_t>(std::llround(dt_x_rate_f));
          uint32_t dt_x_rate_B = (dt_x_rate + 32) >> 3;
          rate_x_dt_update(static_cast<uint16_t>(i), unbottleneckedrate_update_rag, dt_x_rate, dt_x_rate_B);
        }
      }    
               
    } 

    // test 
    if (chrono::duration_cast<chrono::milliseconds>(test_time - last_test_time).count() >= 500) {
      cout << "[FSMMF_CONTROL]  flow rate sum = " << flow_rate << endl;
      last_test_time = test_time;
      ridt_read(test_dt);
      rirate_read(test_rate);
      ri_dt_x_rate_read(test_dt_x_rate);
      ri_burststage_read(test_burststage, test_burstdrop, test_gapRC);
      if (!flowSet.empty()) {
        cout << " "<< endl;
        cout << "There are a total of " << flow_count <<"flows"<<endl;
        for(int i : flowSet) {
            cout << "[FSMMF_CONTROL] flow " << i << " RC = " << fid_RC[i] << "," << rate[i] <<",dt = " << test_dt[i] << ",rate= " <<test_rate[i] << ",dt_x_rate_B= " <<test_dt_x_rate[i] << endl;
            // cout << "[FSMMF_CONTROL] flow " << i << " burst control stage is " << test_burststage[i] << "; burst_drop is " << test_burstdrop[i] << "; gapRC is " << test_gapRC[i] <<endl;
        }
      }
      
    }
  }
}

void start_fsmmf_ctl() {
  setup_dev_tgt();
  fsmmf_loop();
  return;    
}
int main(int argc, char **argv) {
  // start bf-switchd in the background
  start_switchd(argc, argv);
  
  start_fsmmf_ctl();

  // when our program is done, join switchd
  return join_switchd();
}
