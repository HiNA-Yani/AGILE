
#include <iostream>

#include "p4_prefix.h"

#include <string.h>

extern "C" {
#include <pd/pd.h>
}

#include <list>
#include <map>
#include <pthread.h>

using namespace  ::p4_pd_rpc;
using namespace  ::res_pd_rpc;


class fsmmfHandler : virtual public fsmmfIf {
private:
  struct PipeMgrSimpleCb {
    // Should I simply use to C++11 mutex / condvars
    pthread_mutex_t cb_mutex;
    pthread_cond_t cb_condvar;
    int cb_status;

    PipeMgrSimpleCb()
      : cb_status(0) {
      pthread_mutex_init(&cb_mutex, NULL);
      pthread_cond_init(&cb_condvar, NULL);
    }

    ~PipeMgrSimpleCb() {
      pthread_mutex_destroy(&cb_mutex);
      pthread_cond_destroy(&cb_condvar);
    }

    int wait() {
      pthread_mutex_lock(&cb_mutex);
      while(cb_status == 0) {
        pthread_cond_wait(&cb_condvar, &cb_mutex);
      }
      pthread_mutex_unlock(&cb_mutex);
      return 0;
    }

    void notify() {
      pthread_mutex_lock(&cb_mutex);
      assert(cb_status == 0);
      cb_status = 1;
      pthread_cond_signal(&cb_condvar);
      pthread_mutex_unlock(&cb_mutex);
    }

    static void cb_fn(int device_id, void *cookie) {
      (void) device_id;
      PipeMgrSimpleCb *inst = (PipeMgrSimpleCb *) cookie;
      inst->notify();
    }

    // C++11
    // PipeMgrSimpleCb(const PipeMgrSimpleCb &other) = delete;
    // PipeMgrSimpleCb &operator=(const PipeMgrSimpleCb &other) = delete;

    // PipeMgrSimpleCb(PipeMgrSimpleCb &&other) = delete;
    // PipeMgrSimpleCb &operator=(PipeMgrSimpleCb &&other) = delete;

  private:
    PipeMgrSimpleCb(const PipeMgrSimpleCb &other);
    PipeMgrSimpleCb &operator=(const PipeMgrSimpleCb &other);
  };

public:
    fsmmfHandler() {
        // Your initialization goes here


    }


    // Idle time config

    typedef struct _update_hit_state_cookie_s {
      fsmmfHandler *handler;
      uint64_t seq_id;
    } _update_hit_state_cookie_t;

    typedef struct _update_idle_tmo_expired_cookie_s {
      fsmmfHandler *handler;
      int32_t cookie;
    } _update_idle_tmo_expired_cookie_t;




    EntryHandle_t IngressParser__PORT_METADATA_match_spec_to_entry_hdl(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_IngressParser__PORT_METADATA_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t pd_match_spec;
        pd_match_spec.ig_intr_md_ingress_port = match_spec.ig_intr_md_ingress_port;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_to_entry_hdl(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }
    EntryHandle_t Ingress_t_igr_tiForward_match_spec_to_entry_hdl(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiForward_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t pd_match_spec;
  memcpy(pd_match_spec.hdr_ethernet_dst_addr, match_spec.hdr_ethernet_dst_addr.c_str(), 6);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_to_entry_hdl(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }
    EntryHandle_t Ingress_t_igr_tiRate_match_spec_to_entry_hdl(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRate_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t pd_match_spec;
        pd_match_spec.table_key = match_spec.table_key;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_to_entry_hdl(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }
    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_match_spec_to_entry_hdl(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t pd_match_spec;
        pd_match_spec.log_dt = match_spec.log_dt;
        pd_match_spec.rate = match_spec.rate;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_to_entry_hdl(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }
    EntryHandle_t Ingress_t_igr_tiRC_nag_match_spec_to_entry_hdl(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_to_entry_hdl(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_match_spec_to_entry_hdl(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_to_entry_hdl(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }


    // Dynamic Key Mask Exm Table API.



    // Table entry add functions

    EntryHandle_t IngressParser__PORT_METADATA_table_add_with_set_port_metadata(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_IngressParser__PORT_METADATA_match_spec_t &match_spec, const fsmmf_set_port_metadata_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t pd_match_spec;
        pd_match_spec.ig_intr_md_ingress_port = match_spec.ig_intr_md_ingress_port;

    p4_pd_fsmmf_set_port_metadata_action_spec_t pd_action_spec;
        memcpy(pd_action_spec.action_ig_intr_md, action_spec.action_ig_intr_md.c_str(), 8);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_add_with_set_port_metadata(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiForward_match_spec_t &match_spec, const fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t pd_match_spec;
        memcpy(pd_match_spec.hdr_ethernet_dst_addr, match_spec.hdr_ethernet_dst_addr.c_str(), 6);

    p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t pd_action_spec;
        pd_action_spec.action_egr_port = action_spec.action_egr_port;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiForward_match_spec_t &match_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t pd_match_spec;
        memcpy(pd_match_spec.hdr_ethernet_dst_addr, match_spec.hdr_ethernet_dst_addr.c_str(), 6);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRate_match_spec_t &match_spec, const fsmmf_Ingress_t_igr_aiRate_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t pd_match_spec;
        pd_match_spec.table_key = match_spec.table_key;

    p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t pd_action_spec;
        pd_action_spec.action_Allocate_rate = action_spec.action_Allocate_rate;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t &match_spec, const fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t pd_match_spec;
        pd_match_spec.log_dt = match_spec.log_dt;
        pd_match_spec.rate = match_spec.rate;

    p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t pd_action_spec;
        pd_action_spec.action_Calc_dt_x_rate = action_spec.action_Calc_dt_x_rate;
        pd_action_spec.action_Calc_dt_x_rate_B = action_spec.action_Calc_dt_x_rate_B;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiRC_nag_table_add_with_NoAction(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_NoAction(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_neg(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_neg(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_pos(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_pos(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_add_with_NoAction(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_NoAction(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_neg(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_neg(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_pos(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_pos(sess_hdl, pd_dev_tgt, &pd_match_spec, priority, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }



    // Table entry modify functions
    void IngressParser__PORT_METADATA_table_modify_with_set_port_metadata(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry, const fsmmf_set_port_metadata_action_spec_t &action_spec) {

        p4_pd_fsmmf_set_port_metadata_action_spec_t pd_action_spec;
        memcpy(pd_action_spec.action_ig_intr_md, action_spec.action_ig_intr_md.c_str(), 8);

        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata(sess_hdl, dev_id, entry, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_IngressParser__PORT_METADATA_match_spec_t &match_spec, const fsmmf_set_port_metadata_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t pd_match_spec;
        pd_match_spec.ig_intr_md_ingress_port = match_spec.ig_intr_md_ingress_port;

        p4_pd_fsmmf_set_port_metadata_action_spec_t pd_action_spec;
        memcpy(pd_action_spec.action_ig_intr_md, action_spec.action_ig_intr_md.c_str(), 8);

        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry, const fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t &action_spec) {

        p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t pd_action_spec;
        pd_action_spec.action_egr_port = action_spec.action_egr_port;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress(sess_hdl, dev_id, entry, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiForward_match_spec_t &match_spec, const fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t pd_match_spec;
        memcpy(pd_match_spec.hdr_ethernet_dst_addr, match_spec.hdr_ethernet_dst_addr.c_str(), 6);

        p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t pd_action_spec;
        pd_action_spec.action_egr_port = action_spec.action_egr_port;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiForward_match_spec_t &match_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t pd_match_spec;
        memcpy(pd_match_spec.hdr_ethernet_dst_addr, match_spec.hdr_ethernet_dst_addr.c_str(), 6);

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry, const fsmmf_Ingress_t_igr_aiRate_action_spec_t &action_spec) {

        p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t pd_action_spec;
        pd_action_spec.action_Allocate_rate = action_spec.action_Allocate_rate;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate(sess_hdl, dev_id, entry, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRate_match_spec_t &match_spec, const fsmmf_Ingress_t_igr_aiRate_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t pd_match_spec;
        pd_match_spec.table_key = match_spec.table_key;

        p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t pd_action_spec;
        pd_action_spec.action_Allocate_rate = action_spec.action_Allocate_rate;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry, const fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t &action_spec) {

        p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t pd_action_spec;
        pd_action_spec.action_Calc_dt_x_rate = action_spec.action_Calc_dt_x_rate;
        pd_action_spec.action_Calc_dt_x_rate_B = action_spec.action_Calc_dt_x_rate_B;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate(sess_hdl, dev_id, entry, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t &match_spec, const fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t pd_match_spec;
        pd_match_spec.log_dt = match_spec.log_dt;
        pd_match_spec.rate = match_spec.rate;

        p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t pd_action_spec;
        pd_action_spec.action_Calc_dt_x_rate = action_spec.action_Calc_dt_x_rate;
        pd_action_spec.action_Calc_dt_x_rate_B = action_spec.action_Calc_dt_x_rate_B;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, &pd_action_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_modify_with_NoAction(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_modify_with_NoAction_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }


    // Table entry delete functions

    void IngressParser__PORT_METADATA_table_delete(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {
        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void IngressParser__PORT_METADATA_table_delete_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_IngressParser__PORT_METADATA_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t pd_match_spec;
        pd_match_spec.ig_intr_md_ingress_port = match_spec.ig_intr_md_ingress_port;

        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiForward_table_delete(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {
        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiForward_table_delete_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiForward_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t pd_match_spec;
  memcpy(pd_match_spec.hdr_ethernet_dst_addr, match_spec.hdr_ethernet_dst_addr.c_str(), 6);

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRate_table_delete(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRate_table_delete_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRate_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t pd_match_spec;
        pd_match_spec.table_key = match_spec.table_key;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_table_delete(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {
        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_table_delete_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t &match_spec) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t pd_match_spec;
        pd_match_spec.log_dt = match_spec.log_dt;
        pd_match_spec.rate = match_spec.rate;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_delete(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_table_delete_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t &match_spec, const int32_t priority) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;
        pd_match_spec.md_RC = match_spec.md_RC;
        pd_match_spec.md_RC_mask = match_spec.md_RC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_delete(const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry) {
        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete(sess_hdl, dev_id, entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_table_delete_by_match_spec(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t &match_spec, const int32_t priority) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;
        pd_match_spec.gapRC = match_spec.gapRC;
        pd_match_spec.gapRC_mask = match_spec.gapRC_mask;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete_by_match_spec(sess_hdl, pd_dev_tgt, &pd_match_spec, priority);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }


    // Table default entry get functions

    EntryHandle_t IngressParser__PORT_METADATA_table_get_default_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_entry_hdl_t entry_hdl = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_get_default_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void IngressParser__PORT_METADATA_table_get_default_entry(fsmmf_IngressParser__PORT_METADATA_entry_desc_t &desc, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const bool from_hw) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_get_default_entry(sess_hdl, pd_dev_tgt, from_hw, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
                /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
                /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
            /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
                /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
                /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
                /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
            /* NoAction has no parameters */
            /* Ingress_t_igr_aiRC_neg has no parameters */
            /* Ingress_t_igr_aiRC_pos has no parameters */
            /* Ingress_t_igr_aiGapRC_neg has no parameters */
            /* Ingress_t_igr_aiGapRC_pos has no parameters */
    }

    EntryHandle_t Ingress_t_igr_tiForward_table_get_default_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_entry_hdl_t entry_hdl = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_get_default_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiForward_table_get_default_entry(fsmmf_Ingress_t_igr_tiForward_entry_desc_t &desc, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const bool from_hw) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_get_default_entry(sess_hdl, pd_dev_tgt, from_hw, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
                /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
                /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
            /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
                /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
                /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
                /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
            /* NoAction has no parameters */
            /* Ingress_t_igr_aiRC_neg has no parameters */
            /* Ingress_t_igr_aiRC_pos has no parameters */
            /* Ingress_t_igr_aiGapRC_neg has no parameters */
            /* Ingress_t_igr_aiGapRC_pos has no parameters */
    }

    EntryHandle_t Ingress_t_igr_tiRate_table_get_default_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_entry_hdl_t entry_hdl = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_get_default_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiRate_table_get_default_entry(fsmmf_Ingress_t_igr_tiRate_entry_desc_t &desc, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const bool from_hw) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_get_default_entry(sess_hdl, pd_dev_tgt, from_hw, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
                /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
                /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
            /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
                /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
                /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
                /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
            /* NoAction has no parameters */
            /* Ingress_t_igr_aiRC_neg has no parameters */
            /* Ingress_t_igr_aiRC_pos has no parameters */
            /* Ingress_t_igr_aiGapRC_neg has no parameters */
            /* Ingress_t_igr_aiGapRC_pos has no parameters */
    }

    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_entry_hdl_t entry_hdl = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry(fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_entry_desc_t &desc, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const bool from_hw) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry(sess_hdl, pd_dev_tgt, from_hw, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
                /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
                /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
            /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
                /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
                /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
                /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
            /* NoAction has no parameters */
            /* Ingress_t_igr_aiRC_neg has no parameters */
            /* Ingress_t_igr_aiRC_pos has no parameters */
            /* Ingress_t_igr_aiGapRC_neg has no parameters */
            /* Ingress_t_igr_aiGapRC_pos has no parameters */
    }

    EntryHandle_t Ingress_t_igr_tiRC_nag_table_get_default_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_entry_hdl_t entry_hdl = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_get_default_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiRC_nag_table_get_default_entry(fsmmf_Ingress_t_igr_tiRC_nag_entry_desc_t &desc, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const bool from_hw) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_get_default_entry(sess_hdl, pd_dev_tgt, from_hw, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
                /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
                /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
            /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
                /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
                /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
                /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
            /* NoAction has no parameters */
            /* Ingress_t_igr_aiRC_neg has no parameters */
            /* Ingress_t_igr_aiRC_pos has no parameters */
            /* Ingress_t_igr_aiGapRC_neg has no parameters */
            /* Ingress_t_igr_aiGapRC_pos has no parameters */
    }

    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_get_default_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_entry_hdl_t entry_hdl = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_get_default_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiGapRC_pos_table_get_default_entry(fsmmf_Ingress_t_igr_tiGapRC_pos_entry_desc_t &desc, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const bool from_hw) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_get_default_entry(sess_hdl, pd_dev_tgt, from_hw, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
                /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
                /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
            /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
                /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
                /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
                /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
            /* NoAction has no parameters */
            /* Ingress_t_igr_aiRC_neg has no parameters */
            /* Ingress_t_igr_aiRC_pos has no parameters */
            /* Ingress_t_igr_aiGapRC_neg has no parameters */
            /* Ingress_t_igr_aiGapRC_pos has no parameters */
    }


    // Table default entry clear functions

    void IngressParser__PORT_METADATA_table_reset_default_entry(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_table_reset_default_entry(sess_hdl, pd_dev_tgt);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }
    void Ingress_t_igr_tiForward_table_reset_default_entry(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_table_reset_default_entry(sess_hdl, pd_dev_tgt);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }
    void Ingress_t_igr_tiRate_table_reset_default_entry(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_table_reset_default_entry(sess_hdl, pd_dev_tgt);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }
    void Ingress_t_igr_tiCalc_dt_x_rate_table_reset_default_entry(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_reset_default_entry(sess_hdl, pd_dev_tgt);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }
    void Ingress_t_igr_tiRC_nag_table_reset_default_entry(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_reset_default_entry(sess_hdl, pd_dev_tgt);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }
    void Ingress_t_igr_tiGapRC_pos_table_reset_default_entry(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_reset_default_entry(sess_hdl, pd_dev_tgt);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }


    int32_t IngressParser__PORT_METADATA_get_entry_count(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        int32_t count = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_get_entry_count(sess_hdl, pd_dev_tgt, (uint32_t *)&count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return count;
    }
    int32_t Ingress_t_igr_tiForward_get_entry_count(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        int32_t count = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_get_entry_count(sess_hdl, pd_dev_tgt, (uint32_t *)&count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return count;
    }
    int32_t Ingress_t_igr_tiRate_get_entry_count(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        int32_t count = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_get_entry_count(sess_hdl, pd_dev_tgt, (uint32_t *)&count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return count;
    }
    int32_t Ingress_t_igr_tiCalc_dt_x_rate_get_entry_count(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        int32_t count = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_entry_count(sess_hdl, pd_dev_tgt, (uint32_t *)&count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return count;
    }
    int32_t Ingress_t_igr_tiRC_nag_get_entry_count(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        int32_t count = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_entry_count(sess_hdl, pd_dev_tgt, (uint32_t *)&count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return count;
    }
    int32_t Ingress_t_igr_tiGapRC_pos_get_entry_count(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
        int32_t count = 0;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_entry_count(sess_hdl, pd_dev_tgt, (uint32_t *)&count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return count;
    }


    EntryHandle_t IngressParser__PORT_METADATA_get_first_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t entry_hdl = 0;

        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_get_first_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void IngressParser__PORT_METADATA_get_next_entry_handles(std::vector<int32_t> &next_entry_handles, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const EntryHandle_t entry_hdl, const int32_t n) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        next_entry_handles = std::vector<EntryHandle_t>(n);
        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_get_next_entry_handles(sess_hdl, pd_dev_tgt, entry_hdl, n, (p4_pd_entry_hdl_t *)next_entry_handles.data());
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void IngressParser__PORT_METADATA_get_entry(fsmmf_IngressParser__PORT_METADATA_entry_desc_t &desc, const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry_hdl, const bool from_hw) {
        bool has_mbr_hdl = false;
        bool has_grp_hdl = false;
        p4_pd_grp_hdl_t grp_hdl = 0;
        p4_pd_mbr_hdl_t mbr_hdl = 0;
        (void) has_mbr_hdl;
        (void) has_grp_hdl;
        (void) grp_hdl;
        (void) mbr_hdl;
        p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t pd_match_spec;

        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_get_entry(sess_hdl, dev_id, entry_hdl, from_hw, &pd_match_spec, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
          /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
          /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
        /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
          /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
          /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
          /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
        /* NoAction has no parameters */
        /* Ingress_t_igr_aiRC_neg has no parameters */
        /* Ingress_t_igr_aiRC_pos has no parameters */
        /* Ingress_t_igr_aiGapRC_neg has no parameters */
        /* Ingress_t_igr_aiGapRC_pos has no parameters */
        desc.match_spec.ig_intr_md_ingress_port = pd_match_spec.ig_intr_md_ingress_port;
       desc.has_grp_hdl = has_grp_hdl;
       desc.has_mbr_hdl = has_mbr_hdl;
       desc.selector_grp_hdl = grp_hdl;
       desc.action_mbr_hdl = mbr_hdl;
    }

    EntryHandle_t Ingress_t_igr_tiForward_get_first_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t entry_hdl = 0;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_get_first_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiForward_get_next_entry_handles(std::vector<int32_t> &next_entry_handles, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const EntryHandle_t entry_hdl, const int32_t n) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        next_entry_handles = std::vector<EntryHandle_t>(n);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_get_next_entry_handles(sess_hdl, pd_dev_tgt, entry_hdl, n, (p4_pd_entry_hdl_t *)next_entry_handles.data());
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiForward_get_entry(fsmmf_Ingress_t_igr_tiForward_entry_desc_t &desc, const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry_hdl, const bool from_hw) {
        bool has_mbr_hdl = false;
        bool has_grp_hdl = false;
        p4_pd_grp_hdl_t grp_hdl = 0;
        p4_pd_mbr_hdl_t mbr_hdl = 0;
        (void) has_mbr_hdl;
        (void) has_grp_hdl;
        (void) grp_hdl;
        (void) mbr_hdl;
        p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t pd_match_spec;

        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_get_entry(sess_hdl, dev_id, entry_hdl, from_hw, &pd_match_spec, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
          /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
          /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
        /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
          /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
          /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
          /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
        /* NoAction has no parameters */
        /* Ingress_t_igr_aiRC_neg has no parameters */
        /* Ingress_t_igr_aiRC_pos has no parameters */
        /* Ingress_t_igr_aiGapRC_neg has no parameters */
        /* Ingress_t_igr_aiGapRC_pos has no parameters */
        desc.match_spec.hdr_ethernet_dst_addr = std::string((char *) pd_match_spec.hdr_ethernet_dst_addr, 6);
       desc.has_grp_hdl = has_grp_hdl;
       desc.has_mbr_hdl = has_mbr_hdl;
       desc.selector_grp_hdl = grp_hdl;
       desc.action_mbr_hdl = mbr_hdl;
    }

    EntryHandle_t Ingress_t_igr_tiRate_get_first_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t entry_hdl = 0;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_get_first_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiRate_get_next_entry_handles(std::vector<int32_t> &next_entry_handles, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const EntryHandle_t entry_hdl, const int32_t n) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        next_entry_handles = std::vector<EntryHandle_t>(n);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_get_next_entry_handles(sess_hdl, pd_dev_tgt, entry_hdl, n, (p4_pd_entry_hdl_t *)next_entry_handles.data());
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRate_get_entry(fsmmf_Ingress_t_igr_tiRate_entry_desc_t &desc, const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry_hdl, const bool from_hw) {
        bool has_mbr_hdl = false;
        bool has_grp_hdl = false;
        p4_pd_grp_hdl_t grp_hdl = 0;
        p4_pd_mbr_hdl_t mbr_hdl = 0;
        (void) has_mbr_hdl;
        (void) has_grp_hdl;
        (void) grp_hdl;
        (void) mbr_hdl;
        p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t pd_match_spec;

        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_get_entry(sess_hdl, dev_id, entry_hdl, from_hw, &pd_match_spec, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
          /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
          /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
        /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
          /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
          /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
          /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
        /* NoAction has no parameters */
        /* Ingress_t_igr_aiRC_neg has no parameters */
        /* Ingress_t_igr_aiRC_pos has no parameters */
        /* Ingress_t_igr_aiGapRC_neg has no parameters */
        /* Ingress_t_igr_aiGapRC_pos has no parameters */
        desc.match_spec.table_key = pd_match_spec.table_key;
       desc.has_grp_hdl = has_grp_hdl;
       desc.has_mbr_hdl = has_mbr_hdl;
       desc.selector_grp_hdl = grp_hdl;
       desc.action_mbr_hdl = mbr_hdl;
    }

    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_get_first_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t entry_hdl = 0;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_first_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_get_next_entry_handles(std::vector<int32_t> &next_entry_handles, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const EntryHandle_t entry_hdl, const int32_t n) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        next_entry_handles = std::vector<EntryHandle_t>(n);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_next_entry_handles(sess_hdl, pd_dev_tgt, entry_hdl, n, (p4_pd_entry_hdl_t *)next_entry_handles.data());
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_get_entry(fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_entry_desc_t &desc, const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry_hdl, const bool from_hw) {
        bool has_mbr_hdl = false;
        bool has_grp_hdl = false;
        p4_pd_grp_hdl_t grp_hdl = 0;
        p4_pd_mbr_hdl_t mbr_hdl = 0;
        (void) has_mbr_hdl;
        (void) has_grp_hdl;
        (void) grp_hdl;
        (void) mbr_hdl;
        p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t pd_match_spec;

        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_entry(sess_hdl, dev_id, entry_hdl, from_hw, &pd_match_spec, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
          /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
          /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
        /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
          /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
          /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
          /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
        /* NoAction has no parameters */
        /* Ingress_t_igr_aiRC_neg has no parameters */
        /* Ingress_t_igr_aiRC_pos has no parameters */
        /* Ingress_t_igr_aiGapRC_neg has no parameters */
        /* Ingress_t_igr_aiGapRC_pos has no parameters */
        desc.match_spec.log_dt = pd_match_spec.log_dt;
        desc.match_spec.rate = pd_match_spec.rate;
       desc.has_grp_hdl = has_grp_hdl;
       desc.has_mbr_hdl = has_mbr_hdl;
       desc.selector_grp_hdl = grp_hdl;
       desc.action_mbr_hdl = mbr_hdl;
    }

    EntryHandle_t Ingress_t_igr_tiRC_nag_get_first_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t entry_hdl = 0;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_first_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiRC_nag_get_next_entry_handles(std::vector<int32_t> &next_entry_handles, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const EntryHandle_t entry_hdl, const int32_t n) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        next_entry_handles = std::vector<EntryHandle_t>(n);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_next_entry_handles(sess_hdl, pd_dev_tgt, entry_hdl, n, (p4_pd_entry_hdl_t *)next_entry_handles.data());
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiRC_nag_get_entry(fsmmf_Ingress_t_igr_tiRC_nag_entry_desc_t &desc, const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry_hdl, const bool from_hw) {
        bool has_mbr_hdl = false;
        bool has_grp_hdl = false;
        p4_pd_grp_hdl_t grp_hdl = 0;
        p4_pd_mbr_hdl_t mbr_hdl = 0;
        (void) has_mbr_hdl;
        (void) has_grp_hdl;
        (void) grp_hdl;
        (void) mbr_hdl;
        p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t pd_match_spec;

        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_entry(sess_hdl, dev_id, entry_hdl, from_hw, &pd_match_spec, &desc.priority, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
          /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
          /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
        /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
          /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
          /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
          /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
        /* NoAction has no parameters */
        /* Ingress_t_igr_aiRC_neg has no parameters */
        /* Ingress_t_igr_aiRC_pos has no parameters */
        /* Ingress_t_igr_aiGapRC_neg has no parameters */
        /* Ingress_t_igr_aiGapRC_pos has no parameters */
        desc.match_spec.md_RC = pd_match_spec.md_RC;
        desc.match_spec.md_RC_mask = pd_match_spec.md_RC_mask;
       desc.has_grp_hdl = has_grp_hdl;
       desc.has_mbr_hdl = has_mbr_hdl;
       desc.selector_grp_hdl = grp_hdl;
       desc.action_mbr_hdl = mbr_hdl;
    }

    EntryHandle_t Ingress_t_igr_tiGapRC_pos_get_first_entry_handle(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t entry_hdl = 0;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_first_entry_handle(sess_hdl, pd_dev_tgt, &entry_hdl);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return (EntryHandle_t)entry_hdl;
    }

    void Ingress_t_igr_tiGapRC_pos_get_next_entry_handles(std::vector<int32_t> &next_entry_handles, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const EntryHandle_t entry_hdl, const int32_t n) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        next_entry_handles = std::vector<EntryHandle_t>(n);
        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_next_entry_handles(sess_hdl, pd_dev_tgt, entry_hdl, n, (p4_pd_entry_hdl_t *)next_entry_handles.data());
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void Ingress_t_igr_tiGapRC_pos_get_entry(fsmmf_Ingress_t_igr_tiGapRC_pos_entry_desc_t &desc, const SessionHandle_t sess_hdl, const int8_t dev_id, const EntryHandle_t entry_hdl, const bool from_hw) {
        bool has_mbr_hdl = false;
        bool has_grp_hdl = false;
        p4_pd_grp_hdl_t grp_hdl = 0;
        p4_pd_mbr_hdl_t mbr_hdl = 0;
        (void) has_mbr_hdl;
        (void) has_grp_hdl;
        (void) grp_hdl;
        (void) mbr_hdl;
        p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t pd_match_spec;

        p4_pd_fsmmf_action_specs_t pd_action_specs = {};
        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_entry(sess_hdl, dev_id, entry_hdl, from_hw, &pd_match_spec, &desc.priority, &pd_action_specs);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }

        switch(pd_action_specs.name) {
          case p4_pd_fsmmf_set_port_metadata:
            desc.action_desc.name = std::string("set_port_metadata");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiSetEgress:
            desc.action_desc.name = std::string("Ingress_t_igr_aiSetEgress");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiNoop:
            desc.action_desc.name = std::string("Ingress_t_igr_aiNoop");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRate");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate:
            desc.action_desc.name = std::string("Ingress_t_igr_aiCalc_dt_x_rate");
            break;
          case p4_pd_fsmmf_NoAction:
            desc.action_desc.name = std::string("NoAction");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiRC_pos");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_neg");
            break;
          case p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos:
            desc.action_desc.name = std::string("Ingress_t_igr_aiGapRC_pos");
            break;
        }
        if (desc.action_desc.name == "set_port_metadata") {
          fsmmf_set_port_metadata_action_spec_t a_spec;
          /* action_ig_intr_md has byte width 8 */
          a_spec.__set_action_ig_intr_md(std::string((char*)pd_action_specs.u.p4_pd_fsmmf_set_port_metadata.action_ig_intr_md, 8));
          desc.action_desc.data.__set_fsmmf_set_port_metadata(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiSetEgress") {
          fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t a_spec;
          /* action_egr_port has byte width 2 */
          a_spec.__set_action_egr_port(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress.action_egr_port);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiSetEgress(a_spec);
        }
        /* Ingress_t_igr_aiNoop has no parameters */
        else if (desc.action_desc.name == "Ingress_t_igr_aiRate") {
          fsmmf_Ingress_t_igr_aiRate_action_spec_t a_spec;
          /* action_Allocate_rate has byte width 4 */
          a_spec.__set_action_Allocate_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiRate.action_Allocate_rate);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiRate(a_spec);
        }
        else if (desc.action_desc.name == "Ingress_t_igr_aiCalc_dt_x_rate") {
          fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t a_spec;
          /* action_Calc_dt_x_rate has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate);
          /* action_Calc_dt_x_rate_B has byte width 4 */
          a_spec.__set_action_Calc_dt_x_rate_B(pd_action_specs.u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate.action_Calc_dt_x_rate_B);
          desc.action_desc.data.__set_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate(a_spec);
        }
        /* NoAction has no parameters */
        /* Ingress_t_igr_aiRC_neg has no parameters */
        /* Ingress_t_igr_aiRC_pos has no parameters */
        /* Ingress_t_igr_aiGapRC_neg has no parameters */
        /* Ingress_t_igr_aiGapRC_pos has no parameters */
        desc.match_spec.gapRC = pd_match_spec.gapRC;
        desc.match_spec.gapRC_mask = pd_match_spec.gapRC_mask;
       desc.has_grp_hdl = has_grp_hdl;
       desc.has_mbr_hdl = has_mbr_hdl;
       desc.selector_grp_hdl = grp_hdl;
       desc.action_mbr_hdl = mbr_hdl;
    }



    // set default action

    int32_t Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop(sess_hdl, pd_dev_tgt, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiRate_set_default_action_Ingress_t_igr_aiRate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_aiRate_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t pd_action_spec;
        pd_action_spec.action_Allocate_rate = action_spec.action_Allocate_rate;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_set_default_action_Ingress_t_igr_aiRate(sess_hdl, pd_dev_tgt, &pd_action_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiCalc_dt_x_rate_set_default_action_Ingress_t_igr_aiCalc_dt_x_rate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t &action_spec) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t pd_action_spec;
        pd_action_spec.action_Calc_dt_x_rate = action_spec.action_Calc_dt_x_rate;
        pd_action_spec.action_Calc_dt_x_rate_B = action_spec.action_Calc_dt_x_rate_B;

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_set_default_action_Ingress_t_igr_aiCalc_dt_x_rate(sess_hdl, pd_dev_tgt, &pd_action_spec, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiRC_nag_set_default_action_NoAction(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_NoAction(sess_hdl, pd_dev_tgt, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_neg(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_neg(sess_hdl, pd_dev_tgt, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_pos(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_pos(sess_hdl, pd_dev_tgt, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiGapRC_pos_set_default_action_NoAction(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_NoAction(sess_hdl, pd_dev_tgt, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_neg(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_neg(sess_hdl, pd_dev_tgt, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }

    int32_t Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_pos(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_entry_hdl_t pd_entry;

        int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_pos(sess_hdl, pd_dev_tgt, &pd_entry);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return pd_entry;
    }


    // INDIRECT ACTION DATA AND MATCH SELECT



    typedef struct _sel_update_cookie_s {
      fsmmfHandler *handler;
      int32_t cookie;
    } _sel_update_cookie_t;






     // Table set/get property

    void IngressParser__PORT_METADATA_set_property(const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property, const tbl_property_value_t::type value, const int32_t prop_args) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;
      property_value.value = (uint32_t)value;
      property_args.value = (uint32_t)prop_args;
      int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_set_property(sess_hdl, dev_id, pipe_property, property_value, property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }
    }

    void IngressParser__PORT_METADATA_get_property(tbl_property_value_args_t& _return, const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;

      int status = p4_pd_fsmmf_IngressParser__PORT_METADATA_get_property(sess_hdl, dev_id, pipe_property, &property_value, &property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }

      switch (pipe_property)
      {
        case PD_TABLE_ENTRY_SCOPE:
        {
          if (property_value.value == 0) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_ALL_PIPELINES;
          } else if (property_value.value == 1) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_SINGLE_PIPELINE;
          } else {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_USER_DEFINED;
          }
          break;
        }
        case PD_TERN_TABLE_ENTRY_PLACEMENT:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_APP_MANAGED;
          } else {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_DRV_MANAGED;
          }
          break;
        }
        case PD_DUPLICATE_ENTRY_CHECK:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_ENABLE;
          } else {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_DISABLE;
          }
          break;
        }
        case PD_IDLETIME_REPEATED_NOTIFICATION:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_ENABLE;
          } else {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_DISABLE;
          }
          break;
        }
      }
      _return.scope_args = property_args.value;
    }

    void Ingress_t_igr_tiForward_set_property(const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property, const tbl_property_value_t::type value, const int32_t prop_args) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;
      property_value.value = (uint32_t)value;
      property_args.value = (uint32_t)prop_args;
      int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_set_property(sess_hdl, dev_id, pipe_property, property_value, property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }
    }

    void Ingress_t_igr_tiForward_get_property(tbl_property_value_args_t& _return, const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;

      int status = p4_pd_fsmmf_Ingress_t_igr_tiForward_get_property(sess_hdl, dev_id, pipe_property, &property_value, &property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }

      switch (pipe_property)
      {
        case PD_TABLE_ENTRY_SCOPE:
        {
          if (property_value.value == 0) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_ALL_PIPELINES;
          } else if (property_value.value == 1) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_SINGLE_PIPELINE;
          } else {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_USER_DEFINED;
          }
          break;
        }
        case PD_TERN_TABLE_ENTRY_PLACEMENT:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_APP_MANAGED;
          } else {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_DRV_MANAGED;
          }
          break;
        }
        case PD_DUPLICATE_ENTRY_CHECK:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_ENABLE;
          } else {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_DISABLE;
          }
          break;
        }
        case PD_IDLETIME_REPEATED_NOTIFICATION:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_ENABLE;
          } else {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_DISABLE;
          }
          break;
        }
      }
      _return.scope_args = property_args.value;
    }

    void Ingress_t_igr_tiRate_set_property(const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property, const tbl_property_value_t::type value, const int32_t prop_args) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;
      property_value.value = (uint32_t)value;
      property_args.value = (uint32_t)prop_args;
      int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_set_property(sess_hdl, dev_id, pipe_property, property_value, property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }
    }

    void Ingress_t_igr_tiRate_get_property(tbl_property_value_args_t& _return, const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;

      int status = p4_pd_fsmmf_Ingress_t_igr_tiRate_get_property(sess_hdl, dev_id, pipe_property, &property_value, &property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }

      switch (pipe_property)
      {
        case PD_TABLE_ENTRY_SCOPE:
        {
          if (property_value.value == 0) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_ALL_PIPELINES;
          } else if (property_value.value == 1) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_SINGLE_PIPELINE;
          } else {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_USER_DEFINED;
          }
          break;
        }
        case PD_TERN_TABLE_ENTRY_PLACEMENT:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_APP_MANAGED;
          } else {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_DRV_MANAGED;
          }
          break;
        }
        case PD_DUPLICATE_ENTRY_CHECK:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_ENABLE;
          } else {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_DISABLE;
          }
          break;
        }
        case PD_IDLETIME_REPEATED_NOTIFICATION:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_ENABLE;
          } else {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_DISABLE;
          }
          break;
        }
      }
      _return.scope_args = property_args.value;
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_set_property(const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property, const tbl_property_value_t::type value, const int32_t prop_args) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;
      property_value.value = (uint32_t)value;
      property_args.value = (uint32_t)prop_args;
      int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_set_property(sess_hdl, dev_id, pipe_property, property_value, property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }
    }

    void Ingress_t_igr_tiCalc_dt_x_rate_get_property(tbl_property_value_args_t& _return, const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;

      int status = p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_property(sess_hdl, dev_id, pipe_property, &property_value, &property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }

      switch (pipe_property)
      {
        case PD_TABLE_ENTRY_SCOPE:
        {
          if (property_value.value == 0) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_ALL_PIPELINES;
          } else if (property_value.value == 1) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_SINGLE_PIPELINE;
          } else {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_USER_DEFINED;
          }
          break;
        }
        case PD_TERN_TABLE_ENTRY_PLACEMENT:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_APP_MANAGED;
          } else {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_DRV_MANAGED;
          }
          break;
        }
        case PD_DUPLICATE_ENTRY_CHECK:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_ENABLE;
          } else {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_DISABLE;
          }
          break;
        }
        case PD_IDLETIME_REPEATED_NOTIFICATION:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_ENABLE;
          } else {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_DISABLE;
          }
          break;
        }
      }
      _return.scope_args = property_args.value;
    }

    void Ingress_t_igr_tiRC_nag_set_property(const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property, const tbl_property_value_t::type value, const int32_t prop_args) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;
      property_value.value = (uint32_t)value;
      property_args.value = (uint32_t)prop_args;
      int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_property(sess_hdl, dev_id, pipe_property, property_value, property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }
    }

    void Ingress_t_igr_tiRC_nag_get_property(tbl_property_value_args_t& _return, const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;

      int status = p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_property(sess_hdl, dev_id, pipe_property, &property_value, &property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }

      switch (pipe_property)
      {
        case PD_TABLE_ENTRY_SCOPE:
        {
          if (property_value.value == 0) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_ALL_PIPELINES;
          } else if (property_value.value == 1) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_SINGLE_PIPELINE;
          } else {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_USER_DEFINED;
          }
          break;
        }
        case PD_TERN_TABLE_ENTRY_PLACEMENT:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_APP_MANAGED;
          } else {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_DRV_MANAGED;
          }
          break;
        }
        case PD_DUPLICATE_ENTRY_CHECK:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_ENABLE;
          } else {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_DISABLE;
          }
          break;
        }
        case PD_IDLETIME_REPEATED_NOTIFICATION:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_ENABLE;
          } else {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_DISABLE;
          }
          break;
        }
      }
      _return.scope_args = property_args.value;
    }

    void Ingress_t_igr_tiGapRC_pos_set_property(const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property, const tbl_property_value_t::type value, const int32_t prop_args) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;
      property_value.value = (uint32_t)value;
      property_args.value = (uint32_t)prop_args;
      int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_property(sess_hdl, dev_id, pipe_property, property_value, property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }
    }

    void Ingress_t_igr_tiGapRC_pos_get_property(tbl_property_value_args_t& _return, const SessionHandle_t sess_hdl, const int8_t dev_id, const tbl_property_t::type property) {
      p4_pd_tbl_prop_type_t pipe_property = (p4_pd_tbl_prop_type_t)property;
      p4_pd_tbl_prop_value_t property_value;
      p4_pd_tbl_prop_args_t property_args;

      int status = p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_property(sess_hdl, dev_id, pipe_property, &property_value, &property_args);
      if(status != 0) {
        InvalidTableOperation iop;
        iop.code = status;
        throw iop;
      }

      switch (pipe_property)
      {
        case PD_TABLE_ENTRY_SCOPE:
        {
          if (property_value.value == 0) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_ALL_PIPELINES;
          } else if (property_value.value == 1) {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_SINGLE_PIPELINE;
          } else {
            _return.value = tbl_property_value_t::ENTRY_SCOPE_USER_DEFINED;
          }
          break;
        }
        case PD_TERN_TABLE_ENTRY_PLACEMENT:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_APP_MANAGED;
          } else {
            _return.value = tbl_property_value_t::TERN_ENTRY_PLACEMENT_DRV_MANAGED;
          }
          break;
        }
        case PD_DUPLICATE_ENTRY_CHECK:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_ENABLE;
          } else {
            _return.value = tbl_property_value_t::DUPLICATE_ENTRY_CHECK_DISABLE;
          }
          break;
        }
        case PD_IDLETIME_REPEATED_NOTIFICATION:
        {
          if (property_value.value) {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_ENABLE;
          } else {
            _return.value = tbl_property_value_t::IDLETIME_REPEATED_NOTIFICATION_DISABLE;
          }
          break;
        }
      }
      _return.scope_args = property_args.value;
    }




    void set_learning_timeout(const SessionHandle_t sess_hdl,
                 const int8_t device_id,
                 const int32_t usecs){
        int status = p4_pd_fsmmf_set_learning_timeout(sess_hdl, device_id, usecs);
        if(status != 0) {
          InvalidLearnOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void tbl_dbg_counter_type_set(const DevTarget_t &dev_tgt,
                  const std::string& tbl_name,
                  const tbl_dbg_counter_type_t::type t_type) {

        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_tbl_dbg_counter_type_set(pd_dev_tgt, (char*)tbl_name.c_str(),
                (p4_pd_tbl_dbg_counter_type_t)t_type);
        if (status != 0) {
          InvalidDbgOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void tbl_dbg_counter_get(TblCntrInfo_t &info,
                 const DevTarget_t &dev_tgt,
                 const std::string& tbl_name) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        p4_pd_tbl_dbg_counter_type_t pd_type;
        uint32_t value;

        int status = p4_pd_tbl_dbg_counter_get(pd_dev_tgt, (char*)tbl_name.c_str(),
                   &pd_type, &value);
        if (status != 0) {
          InvalidDbgOperation iop;
          iop.code = status;
          throw iop;
        }
        info.type = (tbl_dbg_counter_type_t::type)pd_type;
        info.value = value;
    }

    void tbl_dbg_counter_clear(const DevTarget_t &dev_tgt,
                    const std::string& tbl_name) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_tbl_dbg_counter_clear(pd_dev_tgt, (char*)tbl_name.c_str());
        if (status != 0) {
          InvalidDbgOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void tbl_dbg_counter_type_stage_set(const DevTarget_t &dev_tgt,
                    const int8_t stage,
                    const tbl_dbg_counter_type_t::type t_type) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_tbl_dbg_counter_type_stage_set(pd_dev_tgt, stage,
                (p4_pd_tbl_dbg_counter_type_t)t_type);
        if (status != 0) {
          InvalidDbgOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void tbl_dbg_counter_stage_get(TblDbgStageInfo_t &info,
                 const DevTarget_t &dev_tgt,
                 const int8_t stage) {
        p4_pd_stage_tbl_dbg_counters_t pd_cntrs;
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
        memset(&pd_cntrs, 0, sizeof(pd_cntrs));

        int status = p4_pd_tbl_dbg_counter_stage_get(pd_dev_tgt, stage, &pd_cntrs);
        if (status != 0) {
          InvalidDbgOperation iop;
          iop.code = status;
          throw iop;
        }

        info.num_counters = pd_cntrs.num_counters;
        if (pd_cntrs.num_counters != 0) {
          info.tbl_name.resize(pd_cntrs.num_counters);
          info.type.resize(pd_cntrs.num_counters);
          info.value.resize(pd_cntrs.num_counters);

          for (int i = 0; i < pd_cntrs.num_counters; i++) {
            info.tbl_name[i] = std::string((char *)pd_cntrs.counter[i].tbl_name);
            info.type[i] =
                (tbl_dbg_counter_type_t::type)pd_cntrs.counter[i].cntr_type;
            info.value[i] = pd_cntrs.counter[i].value;
          }
        }

    }

    void tbl_dbg_counter_stage_clear(const DevTarget_t &dev_tgt,
                    const int8_t stage) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int status = p4_pd_tbl_dbg_counter_stage_clear(pd_dev_tgt, stage);
        if (status != 0) {
          InvalidDbgOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    SnapshotHandle_t snapshot_create(const DevTarget_t &dev_tgt,
                             const int8_t start_stage, const int8_t end_stage,
                             const int8_t direction) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        int32_t handle = 0;

	int status = p4_pd_fsmmf_snapshot_create(pd_dev_tgt, start_stage, end_stage,
                   (bf_snapshot_dir_t)direction,
                   (pipe_snapshot_hdl_t*)&handle);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
        return handle;
    }
    void snapshot_delete(const SnapshotHandle_t handle) {
	int status = p4_pd_fsmmf_snapshot_delete((bf_snapshot_state_t)handle);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void snapshot_state_set(const SnapshotHandle_t handle, const int32_t state,
               const int32_t usecs) {
	int status = p4_pd_snapshot_state_set((pipe_snapshot_hdl_t)handle,
                          (bf_snapshot_state_t)state, usecs);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t snapshot_state_get(const SnapshotHandle_t handle, const int16_t pipe) {
        bf_snapshot_state_t state;

	int status = p4_pd_snapshot_state_get((pipe_snapshot_hdl_t)handle,
                   pipe, &state);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
        return state;
    }

    void snapshot_timer_enable(const SnapshotHandle_t handle, const int8_t disable) {
	int status = p4_pd_snapshot_timer_enable((pipe_snapshot_hdl_t)handle, disable);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    void snapshot_capture_trigger_set(const SnapshotHandle_t handle,
                    const fsmmf_snapshot_trig_spec_t& trig_spec,
                    const fsmmf_snapshot_trig_spec_t& trig_spec2) {
        p4_pd_fsmmf_snapshot_trig_spec_t pd_trig_spec;
        p4_pd_fsmmf_snapshot_trig_spec_t pd_trig_mask;
        int dir = (handle >> 1) & 0x1;  // dir is bit 1 of hdl

        memset(&pd_trig_spec, 0, sizeof(pd_trig_spec));
        memset(&pd_trig_mask, 0, sizeof(pd_trig_mask));

        int idx = 0;
        (void)idx;
        switch (dir)
        {
           case 0:
           {
            if (strcmp("_hash_field_argument0", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig._hash_field_argument0),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig._hash_field_argument0),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("_hash_field_argument0", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig._hash_field_argument0),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig._hash_field_argument0),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("_tmp2", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig._tmp2),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig._tmp2),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("_tmp2", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig._tmp2),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig._tmp2),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("bottlenecked_rate_cms_output_1", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_1),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_1),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("bottlenecked_rate_cms_output_1", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_1),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_1),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("bottlenecked_rate_cms_output_2", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_2),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_2),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("bottlenecked_rate_cms_output_2", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_2),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_2),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("bottlenecked_rate_cms_output_3", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_3),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_3),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("bottlenecked_rate_cms_output_3", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_3),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_3),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("const_to_phv_32w20000", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.const_to_phv_32w20000),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.const_to_phv_32w20000),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("const_to_phv_32w20000", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.const_to_phv_32w20000),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.const_to_phv_32w20000),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("const_to_phv_32w5000000", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.const_to_phv_32w5000000),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.const_to_phv_32w5000000),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("const_to_phv_32w5000000", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.const_to_phv_32w5000000),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.const_to_phv_32w5000000),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_ethernet_dst_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.ig.hdr_ethernet_dst_addr[idx] = (trig_spec.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.ig.hdr_ethernet_dst_addr[idx] = (trig_spec.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ethernet_dst_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.ig.hdr_ethernet_dst_addr[idx] = (trig_spec2.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.ig.hdr_ethernet_dst_addr[idx] = (trig_spec2.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ethernet_ether_type", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ethernet_ether_type),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ethernet_ether_type),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ethernet_ether_type", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ethernet_ether_type),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ethernet_ether_type),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ethernet_src_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.ig.hdr_ethernet_src_addr[idx] = (trig_spec.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.ig.hdr_ethernet_src_addr[idx] = (trig_spec.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ethernet_src_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.ig.hdr_ethernet_src_addr[idx] = (trig_spec2.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.ig.hdr_ethernet_src_addr[idx] = (trig_spec2.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ip_dscp", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_dscp),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_dscp),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_dscp", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_dscp),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_dscp),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_dst_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_dst_addr),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_dst_addr),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_ip_dst_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_dst_addr),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_dst_addr),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_ip_ecn", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_ecn),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_ecn),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_ecn", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_ecn),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_ecn),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_flags", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_flags),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_flags),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_flags", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_flags),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_flags),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_frag_offset", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_frag_offset),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_frag_offset),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_frag_offset", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_frag_offset),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_frag_offset),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_hdr_checksum", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_hdr_checksum),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_hdr_checksum),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_hdr_checksum", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_hdr_checksum),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_hdr_checksum),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_identification", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_identification),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_identification),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_identification", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_identification),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_identification),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_ihl", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_ihl),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_ihl),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_ihl", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_ihl),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_ihl),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_protocol", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_protocol),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_protocol),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_protocol", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_protocol),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_protocol),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_src_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_src_addr),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_src_addr),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_ip_src_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_src_addr),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_src_addr),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_ip_total_len", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_total_len),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_total_len),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_total_len", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_total_len),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_total_len),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_ttl", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_ttl),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_ttl),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_ttl", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_ttl),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_ttl),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_version", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_version),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_version),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_version", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_ip_version),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_ip_version),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_ack_no", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_ack_no),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_ack_no),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_tcp_ack_no", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_ack_no),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_ack_no),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_tcp_checksum", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_checksum),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_checksum),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_checksum", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_checksum),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_checksum),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_data_offset", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_data_offset),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_data_offset),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_tcp_data_offset", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_data_offset),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_data_offset),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_dst_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_dst_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_dst_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_dst_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_dst_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_dst_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_flags", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_flags),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_flags),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_tcp_flags", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_flags),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_flags),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_res", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_res),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_res),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_tcp_res", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_res),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_res),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_seq_no", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_seq_no),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_seq_no),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_tcp_seq_no", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_seq_no),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_seq_no),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_tcp_src_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_src_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_src_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_src_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_src_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_src_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_urgent_ptr", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_urgent_ptr),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_urgent_ptr),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_urgent_ptr", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_urgent_ptr),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_urgent_ptr),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_window", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_window),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_window),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_window", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_tcp_window),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_tcp_window),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_checksum", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_checksum),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_checksum),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_checksum", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_checksum),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_checksum),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_dst_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_dst_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_dst_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_dst_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_dst_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_dst_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_hdr_lenght", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_hdr_lenght),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_hdr_lenght),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_hdr_lenght", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_hdr_lenght),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_hdr_lenght),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_src_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_src_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_src_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_src_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.hdr_udp_src_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.hdr_udp_src_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("ig_intr_md_ingress_mac_tstamp", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.ig.ig_intr_md_ingress_mac_tstamp[idx] = (trig_spec.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.ig.ig_intr_md_ingress_mac_tstamp[idx] = (trig_spec.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("ig_intr_md_ingress_mac_tstamp", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.ig.ig_intr_md_ingress_mac_tstamp[idx] = (trig_spec2.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.ig.ig_intr_md_ingress_mac_tstamp[idx] = (trig_spec2.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("ig_intr_md_for_dprsr_drop_ctl", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.ig_intr_md_for_dprsr_drop_ctl),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.ig_intr_md_for_dprsr_drop_ctl),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("ig_intr_md_for_dprsr_drop_ctl", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.ig_intr_md_for_dprsr_drop_ctl),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.ig_intr_md_for_dprsr_drop_ctl),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("ig_intr_md_for_dprsr_mirror_type", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.ig_intr_md_for_dprsr_mirror_type),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.ig_intr_md_for_dprsr_mirror_type),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("ig_intr_md_for_dprsr_mirror_type", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.ig_intr_md_for_dprsr_mirror_type),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.ig_intr_md_for_dprsr_mirror_type),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("ig_intr_md_for_tm_ucast_egress_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.ig_intr_md_for_tm_ucast_egress_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.ig_intr_md_for_tm_ucast_egress_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("ig_intr_md_for_tm_ucast_egress_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.ig_intr_md_for_tm_ucast_egress_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.ig_intr_md_for_tm_ucast_egress_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("md_RC", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_RC),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.md_RC),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("md_RC", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_RC),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.md_RC),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("md_dport", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_dport),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.md_dport),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("md_dport", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_dport),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.md_dport),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("md_fid", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_fid),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.md_fid),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("md_fid", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_fid),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.md_fid),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("md_measured_rate", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_measured_rate),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.md_measured_rate),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("md_measured_rate", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_measured_rate),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.md_measured_rate),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("md_pktlen", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_pktlen),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.md_pktlen),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("md_pktlen", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_pktlen),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.md_pktlen),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("md_sport", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_sport),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.md_sport),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("md_sport", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.md_sport),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.md_sport),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("t_igr_RC_minus_threshold", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_RC_minus_threshold),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_RC_minus_threshold),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_RC_minus_threshold", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_RC_minus_threshold),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_RC_minus_threshold),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_RC_nag", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_RC_nag),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_RC_nag),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("t_igr_RC_nag", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_RC_nag),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_RC_nag),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("t_igr_burst", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_burst),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_burst),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_burst", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_burst),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_burst),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_drop_flag", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_drop_flag),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_drop_flag),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("t_igr_drop_flag", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_drop_flag),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_drop_flag),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("t_igr_dt", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_dt),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_dt),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_dt", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_dt),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_dt),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_dt_ms", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_dt_ms),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_dt_ms),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_dt_ms", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_dt_ms),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_dt_ms),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_dt_x_rate_B", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_dt_x_rate_B),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_dt_x_rate_B),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_dt_x_rate_B", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_dt_x_rate_B),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_dt_x_rate_B),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_ecn_flag", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ecn_flag),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ecn_flag),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("t_igr_ecn_flag", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ecn_flag),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ecn_flag),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("t_igr_gapRC", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_gapRC),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_gapRC),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_gapRC", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_gapRC),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_gapRC),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_ifburstStage", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ifburstStage),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ifburstStage),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("t_igr_ifburstStage", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ifburstStage),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ifburstStage),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("t_igr_log_dt", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_log_dt),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.t_igr_log_dt),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("t_igr_log_dt", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_log_dt),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.ig.t_igr_log_dt),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("t_igr_pktlen_minus_dt_x_rate", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_pktlen_minus_dt_x_rate),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_pktlen_minus_dt_x_rate),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_pktlen_minus_dt_x_rate", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_pktlen_minus_dt_x_rate),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_pktlen_minus_dt_x_rate),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_rate", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_rate),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_rate),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_rate", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_rate),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_rate),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_table_key", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_table_key),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_table_key),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_table_key", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_table_key),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_table_key),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_tcp_drop_flag", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_tcp_drop_flag),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_tcp_drop_flag),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("t_igr_tcp_drop_flag", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_tcp_drop_flag),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.ig.t_igr_tcp_drop_flag),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("t_igr_ts", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ts),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ts),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_ts", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ts),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ts),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("t_igr_ts_ms", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ts_ms),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ts_ms),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("t_igr_ts_ms", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.ig.t_igr_ts_ms),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.ig.t_igr_ts_ms),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_ethernet_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_ethernet_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.ig.hdr_ethernet_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_ethernet_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_ethernet_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.ig.hdr_ethernet_valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_ip_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_ip_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.ig.hdr_ip_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_ip_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_ip_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.ig.hdr_ip_valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_tcp_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_tcp_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.ig.hdr_tcp_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_tcp_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_tcp_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.ig.hdr_tcp_valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_udp_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_udp_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.ig.hdr_udp_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_udp_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.ig.hdr_udp_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.ig.hdr_udp_valid =
                        trig_spec2.field_mask;
            }
            break;
           }
           case 1:
           {
            if (strcmp("eg_intr_md_egress_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.eg_intr_md_egress_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.eg_intr_md_egress_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("eg_intr_md_egress_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.eg_intr_md_egress_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.eg_intr_md_egress_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ethernet_dst_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.eg.hdr_ethernet_dst_addr[idx] = (trig_spec.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_ethernet_dst_addr[idx] = (trig_spec.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ethernet_dst_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.eg.hdr_ethernet_dst_addr[idx] = (trig_spec2.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_ethernet_dst_addr[idx] = (trig_spec2.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ethernet_ether_type", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ethernet_ether_type),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ethernet_ether_type),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ethernet_ether_type", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ethernet_ether_type),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ethernet_ether_type),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ethernet_src_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.eg.hdr_ethernet_src_addr[idx] = (trig_spec.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_ethernet_src_addr[idx] = (trig_spec.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ethernet_src_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    pd_trig_spec.u.eg.hdr_ethernet_src_addr[idx] = (trig_spec2.field_value >> (8*(6 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_ethernet_src_addr[idx] = (trig_spec2.field_mask >> (8*(6 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_ip_dscp", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_dscp),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_dscp),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_dscp", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_dscp),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_dscp),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_dst_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_dst_addr),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_dst_addr),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_ip_dst_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_dst_addr),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_dst_addr),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_ip_ecn", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_ecn),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_ecn),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_ecn", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_ecn),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_ecn),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_flags", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_flags),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_flags),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_flags", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_flags),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_flags),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_frag_offset", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_frag_offset),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_frag_offset),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_frag_offset", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_frag_offset),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_frag_offset),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_hdr_checksum", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_hdr_checksum),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_hdr_checksum),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_hdr_checksum", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_hdr_checksum),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_hdr_checksum),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_identification", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_identification),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_identification),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_identification", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_identification),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_identification),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_ihl", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_ihl),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_ihl),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_ihl", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_ihl),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_ihl),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_protocol", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_protocol),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_protocol),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_protocol", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_protocol),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_protocol),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_src_addr", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_src_addr),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_src_addr),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_ip_src_addr", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_src_addr),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_src_addr),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_ip_total_len", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_total_len),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_total_len),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_ip_total_len", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_total_len),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_total_len),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ip_ttl", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_ttl),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_ttl),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_ttl", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_ttl),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_ttl),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_ip_version", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_version),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_version),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_ip_version", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_ip_version),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_ip_version),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_min_parse_depth_padding_0_0__packet_payload", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_0__packet_payload[idx] = (trig_spec.field_value >> (8*(11 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_0__packet_payload[idx] = (trig_spec.field_mask >> (8*(11 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0_0__packet_payload", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_0__packet_payload[idx] = (trig_spec2.field_value >> (8*(11 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_0__packet_payload[idx] = (trig_spec2.field_mask >> (8*(11 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0_1__packet_payload", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_1__packet_payload[idx] = (trig_spec.field_value >> (8*(11 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_1__packet_payload[idx] = (trig_spec.field_mask >> (8*(11 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0_1__packet_payload", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_1__packet_payload[idx] = (trig_spec2.field_value >> (8*(11 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_1__packet_payload[idx] = (trig_spec2.field_mask >> (8*(11 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0_2__packet_payload", (char*)trig_spec.field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_2__packet_payload[idx] = (trig_spec.field_value >> (8*(11 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_2__packet_payload[idx] = (trig_spec.field_mask >> (8*(11 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0_2__packet_payload", (char*)trig_spec2.field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_2__packet_payload[idx] = (trig_spec2.field_value >> (8*(11 -idx -1))) & 0xff;
                    pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_2__packet_payload[idx] = (trig_spec2.field_mask >> (8*(11 -idx -1))) & 0xff;
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0__stkvalid", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0__stkvalid),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0__stkvalid),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_min_parse_depth_padding_0__stkvalid", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0__stkvalid),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0__stkvalid),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_ack_no", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_ack_no),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_ack_no),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_tcp_ack_no", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_ack_no),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_ack_no),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_tcp_checksum", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_checksum),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_checksum),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_checksum", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_checksum),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_checksum),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_data_offset", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_data_offset),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_data_offset),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_tcp_data_offset", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_data_offset),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_data_offset),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_dst_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_dst_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_dst_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_dst_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_dst_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_dst_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_flags", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_flags),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_flags),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_tcp_flags", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_flags),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_flags),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_res", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_res),
                            &(trig_spec.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_res),
                            &(trig_spec.field_mask), 1);
            }
            if (strcmp("hdr_tcp_res", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_res),
                            &(trig_spec2.field_value), 1);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_res),
                            &(trig_spec2.field_mask), 1);
            }
            if (strcmp("hdr_tcp_seq_no", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_seq_no),
                            &(trig_spec.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_seq_no),
                            &(trig_spec.field_mask), 4);
            }
            if (strcmp("hdr_tcp_seq_no", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_seq_no),
                            &(trig_spec2.field_value), 4);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_seq_no),
                            &(trig_spec2.field_mask), 4);
            }
            if (strcmp("hdr_tcp_src_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_src_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_src_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_src_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_src_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_src_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_urgent_ptr", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_urgent_ptr),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_urgent_ptr),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_urgent_ptr", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_urgent_ptr),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_urgent_ptr),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_tcp_window", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_window),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_window),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_tcp_window", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_tcp_window),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_tcp_window),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_checksum", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_checksum),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_checksum),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_checksum", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_checksum),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_checksum),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_dst_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_dst_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_dst_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_dst_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_dst_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_dst_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_hdr_lenght", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_hdr_lenght),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_hdr_lenght),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_hdr_lenght", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_hdr_lenght),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_hdr_lenght),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_udp_src_port", (char*)trig_spec.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_src_port),
                            &(trig_spec.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_src_port),
                            &(trig_spec.field_mask), 2);
            }
            if (strcmp("hdr_udp_src_port", (char*)trig_spec2.field_name.c_str()) == 0) {
                memcpy(&(pd_trig_spec.u.eg.hdr_udp_src_port),
                            &(trig_spec2.field_value), 2);
                memcpy(&(pd_trig_mask.u.eg.hdr_udp_src_port),
                            &(trig_spec2.field_mask), 2);
            }
            if (strcmp("hdr_ethernet_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_ethernet_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.eg.hdr_ethernet_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_ethernet_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_ethernet_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.eg.hdr_ethernet_valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_ip_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_ip_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.eg.hdr_ip_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_ip_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_ip_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.eg.hdr_ip_valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_0__valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_0__valid =
                        trig_spec.field_value;
                pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_0__valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_0__valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_0__valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_0__valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_1__valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_1__valid =
                        trig_spec.field_value;
                pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_1__valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_1__valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_1__valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_1__valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_2__valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_2__valid =
                        trig_spec.field_value;
                pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_2__valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_2__valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_min_parse_depth_padding_0_2__valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.eg.hdr_min_parse_depth_padding_0_2__valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_tcp_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_tcp_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.eg.hdr_tcp_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_tcp_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_tcp_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.eg.hdr_tcp_valid =
                        trig_spec2.field_mask;
            }
            if (strcmp("hdr_udp_valid", (char*)trig_spec.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_udp_valid =
                        trig_spec.field_value;
                pd_trig_mask.u.eg.hdr_udp_valid =
                        trig_spec.field_mask;
            }
            if (strcmp("hdr_udp_valid", (char*)trig_spec2.field_name.c_str()) == 0) {
                pd_trig_spec.u.eg.hdr_udp_valid =
                        trig_spec2.field_value;
                pd_trig_mask.u.eg.hdr_udp_valid =
                        trig_spec2.field_mask;
            }
            break;
           }
           default:
           {
              break;
           }
        }

        int status = p4_pd_fsmmf_snapshot_capture_trigger_set((bf_snapshot_state_t)handle,
                &pd_trig_spec, &pd_trig_mask);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t snapshot_capture_data_get(const SnapshotHandle_t handle, const int16_t pipe,
                    const int16_t stage_id, const std::string& field_name) {
        int64_t field_value = 0;
        p4_pd_fsmmf_snapshot_capture_arr_t capture_arr;
        p4_pd_fsmmf_snapshot_capture_t *capture;
        bf_snapshot_capture_ctrl_info_arr_t capture_ctrl_arr;
        int32_t num_captures;
        int dir = (handle >> 1) & 0x1;  // dir is bit 1 of hdl
        int idx = 0;
        uint8_t *data_ptr;

        (void)idx;
        (void)data_ptr;

        memset(&capture_arr, 0, sizeof(capture_arr));
        memset(&capture_ctrl_arr, 0, sizeof(capture_ctrl_arr));

        int status = p4_pd_fsmmf_snapshot_capture_data_get((bf_snapshot_state_t)handle, pipe,
                &capture_arr, &capture_ctrl_arr, &num_captures);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
        capture = &(capture_arr.captures[0]);
        /* Go to the right stage */
        for (idx = 0; idx<BF_MAX_SNAPSHOT_CAPTURES; idx++) {
            if ((capture_ctrl_arr.ctrl[idx].valid) &&
                (capture_ctrl_arr.ctrl[idx].stage_id == stage_id)) {
                capture = &(capture_arr.captures[idx]);
                break;
            }
        }

        switch (dir)
        {
           case 0:
           {
            if (strcmp("_hash_field_argument0", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig._hash_field_argument0),
                              (2<=8)?2:8);
            }
            if (strcmp("_tmp2", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig._tmp2),
                              (2<=8)?2:8);
            }
            if (strcmp("bottlenecked_rate_cms_output_1", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.bottlenecked_rate_cms_output_1),
                              (4<=8)?4:8);
            }
            if (strcmp("bottlenecked_rate_cms_output_2", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.bottlenecked_rate_cms_output_2),
                              (4<=8)?4:8);
            }
            if (strcmp("bottlenecked_rate_cms_output_3", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.bottlenecked_rate_cms_output_3),
                              (4<=8)?4:8);
            }
            if (strcmp("const_to_phv_32w20000", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.const_to_phv_32w20000),
                              (4<=8)?4:8);
            }
            if (strcmp("const_to_phv_32w5000000", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.const_to_phv_32w5000000),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_ethernet_dst_addr", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    field_value |= ((int64_t)capture->u.ig.hdr_ethernet_dst_addr[idx]) << (8*(6 -idx -1));
                }
            }
            if (strcmp("hdr_ethernet_ether_type", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ethernet_ether_type),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ethernet_src_addr", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    field_value |= ((int64_t)capture->u.ig.hdr_ethernet_src_addr[idx]) << (8*(6 -idx -1));
                }
            }
            if (strcmp("hdr_ip_dscp", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_dscp),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_dst_addr", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_dst_addr),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_ip_ecn", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_ecn),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_flags", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_flags),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_frag_offset", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_frag_offset),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_hdr_checksum", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_hdr_checksum),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_identification", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_identification),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_ihl", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_ihl),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_protocol", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_protocol),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_src_addr", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_src_addr),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_ip_total_len", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_total_len),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_ttl", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_ttl),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_version", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_ip_version),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_ack_no", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_ack_no),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_tcp_checksum", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_checksum),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_data_offset", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_data_offset),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_dst_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_dst_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_flags", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_flags),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_res", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_res),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_seq_no", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_seq_no),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_tcp_src_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_src_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_urgent_ptr", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_urgent_ptr),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_window", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_tcp_window),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_checksum", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_udp_checksum),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_dst_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_udp_dst_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_hdr_lenght", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_udp_hdr_lenght),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_src_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.hdr_udp_src_port),
                              (2<=8)?2:8);
            }
            if (strcmp("ig_intr_md_ingress_mac_tstamp", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    field_value |= ((int64_t)capture->u.ig.ig_intr_md_ingress_mac_tstamp[idx]) << (8*(6 -idx -1));
                }
            }
            if (strcmp("ig_intr_md_for_dprsr_drop_ctl", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.ig_intr_md_for_dprsr_drop_ctl),
                              (1<=8)?1:8);
            }
            if (strcmp("ig_intr_md_for_dprsr_mirror_type", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.ig_intr_md_for_dprsr_mirror_type),
                              (1<=8)?1:8);
            }
            if (strcmp("ig_intr_md_for_tm_ucast_egress_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.ig_intr_md_for_tm_ucast_egress_port),
                              (2<=8)?2:8);
            }
            if (strcmp("md_RC", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.md_RC),
                              (4<=8)?4:8);
            }
            if (strcmp("md_dport", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.md_dport),
                              (2<=8)?2:8);
            }
            if (strcmp("md_fid", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.md_fid),
                              (2<=8)?2:8);
            }
            if (strcmp("md_measured_rate", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.md_measured_rate),
                              (4<=8)?4:8);
            }
            if (strcmp("md_pktlen", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.md_pktlen),
                              (4<=8)?4:8);
            }
            if (strcmp("md_sport", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.md_sport),
                              (2<=8)?2:8);
            }
            if (strcmp("t_igr_RC_minus_threshold", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_RC_minus_threshold),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_RC_nag", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_RC_nag),
                              (1<=8)?1:8);
            }
            if (strcmp("t_igr_burst", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_burst),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_drop_flag", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_drop_flag),
                              (1<=8)?1:8);
            }
            if (strcmp("t_igr_dt", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_dt),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_dt_ms", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_dt_ms),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_dt_x_rate_B", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_dt_x_rate_B),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_ecn_flag", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_ecn_flag),
                              (1<=8)?1:8);
            }
            if (strcmp("t_igr_gapRC", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_gapRC),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_ifburstStage", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_ifburstStage),
                              (1<=8)?1:8);
            }
            if (strcmp("t_igr_log_dt", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_log_dt),
                              (2<=8)?2:8);
            }
            if (strcmp("t_igr_pktlen_minus_dt_x_rate", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_pktlen_minus_dt_x_rate),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_rate", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_rate),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_table_key", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_table_key),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_tcp_drop_flag", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_tcp_drop_flag),
                              (1<=8)?1:8);
            }
            if (strcmp("t_igr_ts", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_ts),
                              (4<=8)?4:8);
            }
            if (strcmp("t_igr_ts_ms", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.ig.t_igr_ts_ms),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_ethernet_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.ig.hdr_ethernet_valid;
            }
            if (strcmp("hdr_ip_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.ig.hdr_ip_valid;
            }
            if (strcmp("hdr_tcp_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.ig.hdr_tcp_valid;
            }
            if (strcmp("hdr_udp_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.ig.hdr_udp_valid;
            }
              break;
           }
           case 1:
           {
            if (strcmp("eg_intr_md_egress_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.eg_intr_md_egress_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ethernet_dst_addr", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    field_value |= ((int64_t)capture->u.eg.hdr_ethernet_dst_addr[idx]) << (8*(6 -idx -1));
                }
            }
            if (strcmp("hdr_ethernet_ether_type", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ethernet_ether_type),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ethernet_src_addr", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 6; idx++) {
                    field_value |= ((int64_t)capture->u.eg.hdr_ethernet_src_addr[idx]) << (8*(6 -idx -1));
                }
            }
            if (strcmp("hdr_ip_dscp", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_dscp),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_dst_addr", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_dst_addr),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_ip_ecn", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_ecn),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_flags", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_flags),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_frag_offset", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_frag_offset),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_hdr_checksum", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_hdr_checksum),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_identification", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_identification),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_ihl", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_ihl),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_protocol", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_protocol),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_src_addr", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_src_addr),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_ip_total_len", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_total_len),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ip_ttl", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_ttl),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_ip_version", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_ip_version),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_min_parse_depth_padding_0_0__packet_payload", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    field_value |= ((int64_t)capture->u.eg.hdr_min_parse_depth_padding_0_0__packet_payload[idx]) << (8*(11 -idx -1));
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0_1__packet_payload", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    field_value |= ((int64_t)capture->u.eg.hdr_min_parse_depth_padding_0_1__packet_payload[idx]) << (8*(11 -idx -1));
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0_2__packet_payload", (char*)field_name.c_str()) == 0) {
                for (idx = 0; idx < 11; idx++) {
                    field_value |= ((int64_t)capture->u.eg.hdr_min_parse_depth_padding_0_2__packet_payload[idx]) << (8*(11 -idx -1));
                }
            }
            if (strcmp("hdr_min_parse_depth_padding_0__stkvalid", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_min_parse_depth_padding_0__stkvalid),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_ack_no", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_ack_no),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_tcp_checksum", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_checksum),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_data_offset", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_data_offset),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_dst_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_dst_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_flags", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_flags),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_res", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_res),
                              (1<=8)?1:8);
            }
            if (strcmp("hdr_tcp_seq_no", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_seq_no),
                              (4<=8)?4:8);
            }
            if (strcmp("hdr_tcp_src_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_src_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_urgent_ptr", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_urgent_ptr),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_tcp_window", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_tcp_window),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_checksum", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_udp_checksum),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_dst_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_udp_dst_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_hdr_lenght", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_udp_hdr_lenght),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_udp_src_port", (char*)field_name.c_str()) == 0) {
                memcpy(&field_value, &(capture->u.eg.hdr_udp_src_port),
                              (2<=8)?2:8);
            }
            if (strcmp("hdr_ethernet_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.eg.hdr_ethernet_valid;
            }
            if (strcmp("hdr_ip_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.eg.hdr_ip_valid;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_0__valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.eg.hdr_min_parse_depth_padding_0_0__valid;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_1__valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.eg.hdr_min_parse_depth_padding_0_1__valid;
            }
            if (strcmp("hdr_min_parse_depth_padding_0_2__valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.eg.hdr_min_parse_depth_padding_0_2__valid;
            }
            if (strcmp("hdr_tcp_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.eg.hdr_tcp_valid;
            }
            if (strcmp("hdr_udp_valid", (char*)field_name.c_str()) == 0) {
                field_value = capture->u.eg.hdr_udp_valid;
            }
              break;
           }
           default:
           {
              break;
           }
        }

        return field_value;
    }

    void snapshot_capture_tbl_data_get(fsmmf_snapshot_tbl_data_t& _return, const SnapshotHandle_t handle, const int16_t pipe, const std::string& table_name) {
      p4_pd_fsmmf_snapshot_capture_arr_t capture_arr;
      bf_snapshot_capture_ctrl_info_arr_t capture_ctrl_arr;
      int32_t num_captures = 0;

      memset(&capture_arr, 0, sizeof(capture_arr));
      memset(&capture_ctrl_arr, 0, sizeof(capture_ctrl_arr));

      int status = p4_pd_fsmmf_snapshot_capture_data_get((bf_snapshot_state_t)handle, pipe,
              &capture_arr, &capture_ctrl_arr, &num_captures);
      if (status != 0) {
        InvalidSnapshotOperation iop;
        iop.code = status;
        throw iop;
      }
      /* Check all stages. */
      for (int idx = 0; idx<BF_MAX_SNAPSHOT_CAPTURES; idx++) {
        bf_snapshot_capture_ctrl_info_t *ctrl = &capture_ctrl_arr.ctrl[idx];
        if (!ctrl->valid) continue;
        for (int lt=0; lt<BF_MAX_LOG_TBLS; ++lt) {
          bf_snapshot_tables_info_t *tbl = &ctrl->tables_info[lt];
          if (!strcmp((char*)table_name.c_str(), tbl->table_name)) {
            _return.hit = tbl->table_hit;
            _return.inhibited = tbl->table_inhibited;
            _return.executed = tbl->table_executed;
            _return.hit_entry_handle = tbl->hit_entry_handle;
            if (_return.hit || _return.inhibited) return;
          }
        }
      }
    }

    void snapshot_capture_trigger_fields_clr(const SnapshotHandle_t handle) {

	int status = p4_pd_snapshot_capture_trigger_fields_clr((pipe_snapshot_hdl_t)handle);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    bool snapshot_field_in_scope(const DevTarget_t &dev_tgt,
                 const int8_t stage, const int8_t direction,
                 const std::string& field_name) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        bool exists = false;

	int status = p4_pd_snapshot_field_in_scope(pd_dev_tgt, stage,
                   (bf_snapshot_dir_t)direction,
                   (char*)field_name.c_str(), &exists);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
        return exists;
    }

    bool snapshot_trigger_field_in_scope(const DevTarget_t &dev_tgt,
                 const int8_t stage, const int8_t direction,
                 const std::string& field_name) {
        p4_pd_dev_target_t pd_dev_tgt;
        pd_dev_tgt.device_id = dev_tgt.dev_id;
        pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

        bool exists = false;

	int status = p4_pd_snapshot_trigger_field_in_scope(pd_dev_tgt, stage,
                   (bf_snapshot_dir_t)direction,
                   (char*)field_name.c_str(), &exists);
        if (status != 0) {
          InvalidSnapshotOperation iop;
          iop.code = status;
          throw iop;
        }
        return exists;
    }

  // COUNTERS


  // REGISTERS
  void register_hw_sync_Ingress_t_igr_riTs(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riTs(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_riTs(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_riTs(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_riTs_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_riTs(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_riTs_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_riTs(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_riTs(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riTs(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_riTs(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riTs(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_riTs(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_riTs_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_riTs(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_riTs(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_riTs(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_riTs_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_ridt(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ridt(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_ridt(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_ridt(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ridt_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_ridt(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_ridt_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_ridt(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_ridt(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ridt(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_ridt(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ridt(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_ridt(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_ridt_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_ridt(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_ridt(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_ridt(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ridt_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_count_til_drop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_count_til_drop(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_count_til_drop(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_count_til_drop(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_count_til_drop_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_count_til_drop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_count_til_drop_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_count_til_drop(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_count_til_drop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_count_til_drop(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_count_til_drop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_count_til_drop(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_count_til_drop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_count_til_drop_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_count_til_drop(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_count_til_drop(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_count_til_drop(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_count_til_drop_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_riRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riRC(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_riRC(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_riRC(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_riRC_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_riRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_riRC_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_riRC(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_riRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riRC(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_riRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riRC(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_riRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_riRC_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_riRC(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_riRC(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_riRC(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_riRC_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_ri_dt_x_rate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_dt_x_rate(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_ri_dt_x_rate(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_ri_dt_x_rate(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_dt_x_rate_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_ri_dt_x_rate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_ri_dt_x_rate_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_ri_dt_x_rate(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_ri_dt_x_rate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_dt_x_rate(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_ri_dt_x_rate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_dt_x_rate(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_ri_dt_x_rate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_ri_dt_x_rate_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_dt_x_rate(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_ri_dt_x_rate(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_dt_x_rate(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_dt_x_rate_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_bottleneckF(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_bottleneckF(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_bottleneckF(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_bottleneckF(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_bottleneckF_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_bottleneckF(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_bottleneckF_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_bottleneckF(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_bottleneckF(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_bottleneckF(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_bottleneckF(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_bottleneckF(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_bottleneckF(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_bottleneckF_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_bottleneckF(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_bottleneckF(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_bottleneckF(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_bottleneckF_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_ritestgapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ritestgapRC(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_ritestgapRC(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_ritestgapRC(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ritestgapRC_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_ritestgapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_ritestgapRC_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_ritestgapRC(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_ritestgapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestgapRC(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_ritestgapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ritestgapRC(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_ritestgapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_ritestgapRC_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_ritestgapRC(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_ritestgapRC(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestgapRC(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ritestgapRC_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_ritestburstdrop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ritestburstdrop(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_ritestburstdrop(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_ritestburstdrop(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ritestburstdrop_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_ritestburstdrop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_ritestburstdrop_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_ritestburstdrop(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_ritestburstdrop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestburstdrop(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_ritestburstdrop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ritestburstdrop(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_ritestburstdrop(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_ritestburstdrop_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_ritestburstdrop(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_ritestburstdrop(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestburstdrop(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ritestburstdrop_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_ri_gapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_gapRC(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_ri_gapRC(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_ri_gapRC(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_gapRC_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_ri_gapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_ri_gapRC_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_ri_gapRC(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_ri_gapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_gapRC(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_ri_gapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_gapRC(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_ri_gapRC(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_ri_gapRC_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_gapRC(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_ri_gapRC(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_gapRC(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_gapRC_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_bottlenecked_rate_bottleneckedRate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_bottlenecked_rate_bottleneckedRate(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_bottlenecked_rate_bottleneckedRate(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_bottlenecked_rate_bottleneckedRate(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_bottlenecked_rate_bottleneckedRate_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_bottlenecked_rate_bottleneckedRate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_bottlenecked_rate_bottleneckedRate_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_bottlenecked_rate_bottleneckedRate(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_bottlenecked_rate_bottleneckedRate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_bottlenecked_rate_bottleneckedRate(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_bottlenecked_rate_bottleneckedRate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_bottlenecked_rate_bottleneckedRate(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_bottlenecked_rate_bottleneckedRate(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_bottlenecked_rate_bottleneckedRate_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_bottlenecked_rate_bottleneckedRate(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_bottlenecked_rate_bottleneckedRate(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_bottlenecked_rate_bottleneckedRate(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_bottlenecked_rate_bottleneckedRate_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_ri_ts_ms(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_ts_ms(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_ri_ts_ms(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_ri_ts_ms(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_ts_ms_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_ri_ts_ms(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_ri_ts_ms_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_ri_ts_ms(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_ri_ts_ms(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_ts_ms(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_ri_ts_ms(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_ts_ms(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_ri_ts_ms(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_ri_ts_ms_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_ts_ms(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_ri_ts_ms(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_ts_ms(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_ts_ms_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_riburstStage(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riburstStage(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_riburstStage(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_riburstStage(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_riburstStage_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_riburstStage(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_riburstStage_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_riburstStage(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_riburstStage(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riburstStage(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_riburstStage(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riburstStage(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_riburstStage(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_riburstStage_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_riburstStage(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_riburstStage(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_riburstStage(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_riburstStage_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_fCount(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_fCount(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_fCount(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_fCount(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_fCount_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_fCount(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_fCount_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_fCount(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_fCount(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_fCount(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_fCount(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_fCount(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_fCount(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_fCount_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_fCount(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_fCount(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_fCount(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_fCount_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_count_til_ecn(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_count_til_ecn(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_count_til_ecn(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_count_til_ecn(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_count_til_ecn_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_count_til_ecn(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_count_til_ecn_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_count_til_ecn(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_count_til_ecn(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_count_til_ecn(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_count_til_ecn(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_count_til_ecn(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_count_til_ecn(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_count_til_ecn_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_count_til_ecn(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_count_til_ecn(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_count_til_ecn(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_count_til_ecn_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }

  void register_hw_sync_Ingress_t_igr_ri_lograte(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    PipeMgrSimpleCb cb_data;
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    int status = p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_lograte(sess_hdl, pd_dev_tgt, PipeMgrSimpleCb::cb_fn, (void *) &cb_data);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
    cb_data.wait(); // blocking, until callback happens
  }

  void register_read_Ingress_t_igr_ri_lograte(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t values[4];
      int value_count = 0;
      int status = p4_pd_fsmmf_register_read_Ingress_t_igr_ri_lograte(sess_hdl, pd_dev_tgt, index, pd_flags, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_lograte_spec_pd_to_thrift(values[i]));
      }
  }

  void register_write_Ingress_t_igr_ri_lograte(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t register_value) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      auto value = register_Ingress_t_igr_ri_lograte_spec_thrift_to_pd(register_value);

      int status = p4_pd_fsmmf_register_write_Ingress_t_igr_ri_lograte(sess_hdl, pd_dev_tgt, index, &value);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
  }

  void register_reset_all_Ingress_t_igr_ri_lograte(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_lograte(sess_hdl, pd_dev_tgt);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_reset_Ingress_t_igr_ri_lograte(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    int status = p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_lograte(sess_hdl, pd_dev_tgt, index, count);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_write_all_Ingress_t_igr_ri_lograte(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t register_value) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    auto value = register_Ingress_t_igr_ri_lograte_spec_thrift_to_pd(register_value);

    int status = p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_lograte(sess_hdl, pd_dev_tgt, &value);
    if(status != 0) {
      InvalidRegisterOperation iop;
      iop.code = status;
      throw iop;
    }
  }

  void register_range_read_Ingress_t_igr_ri_lograte(std::vector<int32_t> &register_values, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const int32_t count, const fsmmf_register_flags_t &flags) {

      p4_pd_dev_target_t pd_dev_tgt;
      pd_dev_tgt.device_id = dev_tgt.dev_id;
      pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

      int pd_flags = 0;
      if(flags.read_hw_sync) pd_flags |= REGISTER_READ_HW_SYNC;

      uint32_t *values = new uint32_t[4*count];
      int value_count = 0;
      int num_actually_read = 0;
      int status = p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_lograte(sess_hdl, pd_dev_tgt, index, count, pd_flags, &num_actually_read, values, &value_count);
      if(status != 0) {
        InvalidRegisterOperation iop;
        iop.code = status;
        throw iop;
      }
      int i;
      register_values.reserve(value_count);
      for(i = 0; i < value_count; i++) {
        register_values.push_back(register_Ingress_t_igr_ri_lograte_spec_pd_to_thrift(values[i]));
      }
      delete[] values;
  }


  void bytes_meter_spec_thrift_to_pd(const fsmmf_bytes_meter_spec_t &meter_spec,
                                     p4_pd_bytes_meter_spec_t *pd_meter_spec) {
    pd_meter_spec->cir_kbps = meter_spec.cir_kbps;
    pd_meter_spec->cburst_kbits = meter_spec.cburst_kbits;
    pd_meter_spec->pir_kbps = meter_spec.pir_kbps;
    pd_meter_spec->pburst_kbits = meter_spec.pburst_kbits;
    pd_meter_spec->meter_type = meter_spec.color_aware ?
      PD_METER_TYPE_COLOR_AWARE : PD_METER_TYPE_COLOR_UNAWARE;
  }

  void packets_meter_spec_thrift_to_pd(const fsmmf_packets_meter_spec_t &meter_spec,
                                       p4_pd_packets_meter_spec_t *pd_meter_spec) {
    pd_meter_spec->cir_pps = meter_spec.cir_pps;
    pd_meter_spec->cburst_pkts = meter_spec.cburst_pkts;
    pd_meter_spec->pir_pps = meter_spec.pir_pps;
    pd_meter_spec->pburst_pkts = meter_spec.pburst_pkts;
    pd_meter_spec->meter_type = meter_spec.color_aware ?
      PD_METER_TYPE_COLOR_AWARE : PD_METER_TYPE_COLOR_UNAWARE;
  }

  void bytes_meter_spec_pd_to_thrift(fsmmf_bytes_meter_spec_t &meter_spec,
                                     const p4_pd_bytes_meter_spec_t *pd_meter_spec) {
    meter_spec.cir_kbps = pd_meter_spec->cir_kbps;
    meter_spec.cburst_kbits = pd_meter_spec->cburst_kbits;
    meter_spec.pir_kbps = pd_meter_spec->pir_kbps;
    meter_spec.pburst_kbits = pd_meter_spec->pburst_kbits;
    meter_spec.color_aware = pd_meter_spec->meter_type == PD_METER_TYPE_COLOR_AWARE ? true : false;
  }

  void packets_meter_spec_pd_to_thrift(fsmmf_packets_meter_spec_t &meter_spec,
                                       const p4_pd_packets_meter_spec_t *pd_meter_spec) {
    meter_spec.cir_pps = pd_meter_spec->cir_pps;
    meter_spec.cburst_pkts = pd_meter_spec->cburst_pkts;
    meter_spec.pir_pps = pd_meter_spec->pir_pps;
    meter_spec.pburst_pkts = pd_meter_spec->pburst_pkts;
    meter_spec.color_aware = pd_meter_spec->meter_type == PD_METER_TYPE_COLOR_AWARE ? true : false;
  }

  void lpf_spec_thrift_to_pd(const fsmmf_lpf_spec_t &lpf_spec,
                             p4_pd_lpf_spec *pd_lpf_spec) {
    pd_lpf_spec->gain_decay_separate_time_constant =
      lpf_spec.gain_decay_separate_time_constant;
    pd_lpf_spec->gain_time_constant = lpf_spec.gain_time_constant;
    pd_lpf_spec->decay_time_constant = lpf_spec.decay_time_constant;
    pd_lpf_spec->time_constant = lpf_spec.time_constant;
    pd_lpf_spec->output_scale_down_factor = lpf_spec.output_scale_down_factor;
    pd_lpf_spec->lpf_type = (p4_pd_lpf_type_t) lpf_spec.lpf_type;
  }

  void lpf_spec_pd_to_thrift(fsmmf_lpf_spec_t &lpf_spec,
                             const p4_pd_lpf_spec *pd_lpf_spec) {
    lpf_spec.gain_decay_separate_time_constant =
      pd_lpf_spec->gain_decay_separate_time_constant;
    lpf_spec.gain_time_constant = pd_lpf_spec->gain_time_constant;
    lpf_spec.decay_time_constant = pd_lpf_spec->decay_time_constant;
    lpf_spec.time_constant = pd_lpf_spec->time_constant;
    lpf_spec.output_scale_down_factor = pd_lpf_spec->output_scale_down_factor;
    lpf_spec.lpf_type = pd_lpf_spec->lpf_type == PD_LPF_TYPE_RATE ? fsmmf_lpf_type::TYPE_RATE : fsmmf_lpf_type::TYPE_SAMPLE;
  }

  void wred_spec_thrift_to_pd(const fsmmf_wred_spec_t &wred_spec,
                              p4_pd_wred_spec_t *pd_wred_spec) {
    pd_wred_spec->time_constant = wred_spec.time_constant;
    pd_wred_spec->red_min_threshold = wred_spec.red_min_threshold;
    pd_wred_spec->red_max_threshold = wred_spec.red_max_threshold;
    pd_wred_spec->max_probability = wred_spec.max_probability;
  }

  void wred_spec_pd_to_thrift(fsmmf_wred_spec_t &wred_spec,
                              p4_pd_wred_spec_t *pd_wred_spec) {
    wred_spec.time_constant = pd_wred_spec->time_constant;
    wred_spec.red_min_threshold = pd_wred_spec->red_min_threshold;
    wred_spec.red_max_threshold = pd_wred_spec->red_max_threshold;
    wred_spec.max_probability = pd_wred_spec->max_probability;
  }

  uint32_t register_Ingress_t_igr_riTs_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_riTs_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_ridt_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_ridt_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_count_til_drop_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_count_til_drop_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_riRC_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_riRC_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_ri_dt_x_rate_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_ri_dt_x_rate_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_bottleneckF_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_bottleneckF_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_ritestgapRC_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_ritestgapRC_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_ritestburstdrop_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_ritestburstdrop_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_ri_gapRC_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_ri_gapRC_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_bottlenecked_rate_bottleneckedRate_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_bottlenecked_rate_bottleneckedRate_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_ri_ts_ms_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_ri_ts_ms_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_riburstStage_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_riburstStage_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_fCount_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_fCount_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_count_til_ecn_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_count_til_ecn_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }

  uint32_t register_Ingress_t_igr_ri_lograte_spec_thrift_to_pd(const int32_t &thrift_spec) {
    uint32_t pd_spec;
    pd_spec = static_cast<decltype(pd_spec)>(thrift_spec);
    return pd_spec;
  }

  int32_t register_Ingress_t_igr_ri_lograte_spec_pd_to_thrift(const uint32_t &pd_spec) {
    int32_t thrift_spec;
    thrift_spec = static_cast<decltype(thrift_spec)>(pd_spec);
    return thrift_spec;
  }





  void lpf_read_Ingress_bottlenecked_rate_lpf_3(fsmmf_lpf_spec_t &lpf_spec, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    p4_pd_lpf_spec pd_lpf_spec = {0};
    int status = p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_3(sess_hdl, pd_dev_tgt, index, &pd_lpf_spec);
    if(status != 0) {
        InvalidLPFOperation iop;
        iop.code = status;
        throw iop;
    }
    lpf_spec_pd_to_thrift(lpf_spec, &pd_lpf_spec);
  }

  void lpf_set_Ingress_bottlenecked_rate_lpf_3(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_lpf_spec_t &lpf_spec) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    p4_pd_lpf_spec pd_lpf_spec;

    lpf_spec_thrift_to_pd(lpf_spec, &pd_lpf_spec);
    int status = p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_3(sess_hdl, pd_dev_tgt, index, &pd_lpf_spec);
    if(status != 0) {
      InvalidLPFOperation iop;
      iop.code = status;
      throw iop;
    }
  }
  void lpf_read_Ingress_bottlenecked_rate_lpf_2(fsmmf_lpf_spec_t &lpf_spec, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    p4_pd_lpf_spec pd_lpf_spec = {0};
    int status = p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_2(sess_hdl, pd_dev_tgt, index, &pd_lpf_spec);
    if(status != 0) {
        InvalidLPFOperation iop;
        iop.code = status;
        throw iop;
    }
    lpf_spec_pd_to_thrift(lpf_spec, &pd_lpf_spec);
  }

  void lpf_set_Ingress_bottlenecked_rate_lpf_2(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_lpf_spec_t &lpf_spec) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    p4_pd_lpf_spec pd_lpf_spec;

    lpf_spec_thrift_to_pd(lpf_spec, &pd_lpf_spec);
    int status = p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_2(sess_hdl, pd_dev_tgt, index, &pd_lpf_spec);
    if(status != 0) {
      InvalidLPFOperation iop;
      iop.code = status;
      throw iop;
    }
  }
  void lpf_read_Ingress_bottlenecked_rate_lpf_1(fsmmf_lpf_spec_t &lpf_spec, const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);

    p4_pd_lpf_spec pd_lpf_spec = {0};
    int status = p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_1(sess_hdl, pd_dev_tgt, index, &pd_lpf_spec);
    if(status != 0) {
        InvalidLPFOperation iop;
        iop.code = status;
        throw iop;
    }
    lpf_spec_pd_to_thrift(lpf_spec, &pd_lpf_spec);
  }

  void lpf_set_Ingress_bottlenecked_rate_lpf_1(const SessionHandle_t sess_hdl, const DevTarget_t &dev_tgt, const int32_t index, const fsmmf_lpf_spec_t &lpf_spec) {
    p4_pd_dev_target_t pd_dev_tgt;
    pd_dev_tgt.device_id = dev_tgt.dev_id;
    pd_dev_tgt.dev_pipe_id = i16_to_bf_pipe(dev_tgt.dev_pipe_id);
    p4_pd_lpf_spec pd_lpf_spec;

    lpf_spec_thrift_to_pd(lpf_spec, &pd_lpf_spec);
    int status = p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_1(sess_hdl, pd_dev_tgt, index, &pd_lpf_spec);
    if(status != 0) {
      InvalidLPFOperation iop;
      iop.code = status;
      throw iop;
    }
  }





    void hash_calc_Ingress_t_igr_identity_hasher0_configure_input_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t)input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_set(sess_hdl, dev_id, pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher0_configure_input_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t pd_input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_get(sess_hdl, dev_id, &pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t::type)pd_input);
    }

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t::type algo) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t pd_algo = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t)algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_set(sess_hdl, dev_id, pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t pd_algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_get(sess_hdl, dev_id, &pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t::type)pd_algo);
    }

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const int64_t seed) {
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_set(sess_hdl, dev_id, seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        uint64_t seed = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_get(sess_hdl, dev_id, &seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((int64_t)seed);
    }

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t::type input, const std::vector<fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> &array_of_attrs) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t)input;
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t[array_of_attrs.size()]();
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          pd_attr[i].type = (p4_pd_fsmmf_input_field_attr_type_t)item.type;
          pd_attr[i].value.val = item.value;
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_set(sess_hdl, dev_id, pd_input, i, pd_attr);
        delete[] pd_attr;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t)input;
        uint32_t attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return attr_count;
    }

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_get(std::vector<fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> &array_of_attrs, const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t)input;
        uint32_t attr_count = 0, filled_attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *pd_array_of_attrs = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t[attr_count]();
        status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_get(sess_hdl, dev_id, pd_input, attr_count,
                pd_array_of_attrs, &filled_attr_count);
        if(status != 0) {
          delete[] pd_array_of_attrs;
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        /* Copy over the info from the PD struct to the thrift struct */
        array_of_attrs = std::vector<fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t>(filled_attr_count);
        for (int i=0; i < filled_attr_count; i++) {
          array_of_attrs[i].input_field = pd_array_of_attrs[i].input_field.id;
          array_of_attrs[i].type = (fsmmf_input_field_attr_type_t::type)pd_array_of_attrs[i].type;
          array_of_attrs[i].value = pd_array_of_attrs[i].value.val;
        }
        delete[] pd_array_of_attrs;
    }

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_calculate_hash_value(std::vector<int8_t> &hash_val, const SessionHandle_t sess_hdl, const int8_t dev_id, const int32_t attr_count, const std::vector<fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> &array_of_attrs, const std::vector<int32_t> &attr_sizes) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t[attr_count]();
        uint32_t *pd_attr_sizes = new uint32_t[attr_count]();
        hash_val = std::vector<int8_t>(4);
        int64_t result = 0;
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          if (attr_sizes[i] > 32) {
            pd_attr[i].value.stream = (uint8_t *)malloc((attr_sizes[i] + 7) / 8);
            memcpy(pd_attr[i].value.stream, item.stream.c_str(), (attr_sizes[i] + 7) / 8);
          } else {
            pd_attr[i].value.val = item.value;
          }
          pd_attr_sizes[i] = (uint32_t)attr_sizes[i];
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_calculate_hash_value(sess_hdl, dev_id, attr_count, pd_attr, pd_attr_sizes, (uint8_t *)hash_val.data(), 4);
        delete[] pd_attr;
        delete[] pd_attr_sizes;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return;
    }


    void hash_calc_Ingress_t_igr_identity_hasher1_configure_input_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t)input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_set(sess_hdl, dev_id, pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher1_configure_input_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t pd_input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_get(sess_hdl, dev_id, &pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t::type)pd_input);
    }

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t::type algo) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t pd_algo = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t)algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_set(sess_hdl, dev_id, pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t pd_algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_get(sess_hdl, dev_id, &pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t::type)pd_algo);
    }

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const int64_t seed) {
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_set(sess_hdl, dev_id, seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        uint64_t seed = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_get(sess_hdl, dev_id, &seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((int64_t)seed);
    }

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t::type input, const std::vector<fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t> &array_of_attrs) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t)input;
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t[array_of_attrs.size()]();
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          pd_attr[i].type = (p4_pd_fsmmf_input_field_attr_type_t)item.type;
          pd_attr[i].value.val = item.value;
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_set(sess_hdl, dev_id, pd_input, i, pd_attr);
        delete[] pd_attr;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_count_get(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t)input;
        uint32_t attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return attr_count;
    }

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_get(std::vector<fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t> &array_of_attrs, const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t)input;
        uint32_t attr_count = 0, filled_attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *pd_array_of_attrs = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t[attr_count]();
        status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_get(sess_hdl, dev_id, pd_input, attr_count,
                pd_array_of_attrs, &filled_attr_count);
        if(status != 0) {
          delete[] pd_array_of_attrs;
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        /* Copy over the info from the PD struct to the thrift struct */
        array_of_attrs = std::vector<fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t>(filled_attr_count);
        for (int i=0; i < filled_attr_count; i++) {
          array_of_attrs[i].input_field = pd_array_of_attrs[i].input_field.id;
          array_of_attrs[i].type = (fsmmf_input_field_attr_type_t::type)pd_array_of_attrs[i].type;
          array_of_attrs[i].value = pd_array_of_attrs[i].value.val;
        }
        delete[] pd_array_of_attrs;
    }

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_calculate_hash_value(std::vector<int8_t> &hash_val, const SessionHandle_t sess_hdl, const int8_t dev_id, const int32_t attr_count, const std::vector<fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t> &array_of_attrs, const std::vector<int32_t> &attr_sizes) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t[attr_count]();
        uint32_t *pd_attr_sizes = new uint32_t[attr_count]();
        hash_val = std::vector<int8_t>(4);
        int64_t result = 0;
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          if (attr_sizes[i] > 32) {
            pd_attr[i].value.stream = (uint8_t *)malloc((attr_sizes[i] + 7) / 8);
            memcpy(pd_attr[i].value.stream, item.stream.c_str(), (attr_sizes[i] + 7) / 8);
          } else {
            pd_attr[i].value.val = item.value;
          }
          pd_attr_sizes[i] = (uint32_t)attr_sizes[i];
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_calculate_hash_value(sess_hdl, dev_id, attr_count, pd_attr, pd_attr_sizes, (uint8_t *)hash_val.data(), 4);
        delete[] pd_attr;
        delete[] pd_attr_sizes;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return;
    }


    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t)input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_set(sess_hdl, dev_id, pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t pd_input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_get(sess_hdl, dev_id, &pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t::type)pd_input);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t::type algo) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t pd_algo = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t)algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_set(sess_hdl, dev_id, pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t pd_algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_get(sess_hdl, dev_id, &pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t::type)pd_algo);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const int64_t seed) {
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_set(sess_hdl, dev_id, seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        uint64_t seed = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_get(sess_hdl, dev_id, &seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((int64_t)seed);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t::type input, const std::vector<fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t> &array_of_attrs) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t)input;
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t[array_of_attrs.size()]();
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          pd_attr[i].type = (p4_pd_fsmmf_input_field_attr_type_t)item.type;
          pd_attr[i].value.val = item.value;
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_set(sess_hdl, dev_id, pd_input, i, pd_attr);
        delete[] pd_attr;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_count_get(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t)input;
        uint32_t attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return attr_count;
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_get(std::vector<fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t> &array_of_attrs, const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t)input;
        uint32_t attr_count = 0, filled_attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *pd_array_of_attrs = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t[attr_count]();
        status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_get(sess_hdl, dev_id, pd_input, attr_count,
                pd_array_of_attrs, &filled_attr_count);
        if(status != 0) {
          delete[] pd_array_of_attrs;
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        /* Copy over the info from the PD struct to the thrift struct */
        array_of_attrs = std::vector<fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t>(filled_attr_count);
        for (int i=0; i < filled_attr_count; i++) {
          array_of_attrs[i].input_field = pd_array_of_attrs[i].input_field.id;
          array_of_attrs[i].type = (fsmmf_input_field_attr_type_t::type)pd_array_of_attrs[i].type;
          array_of_attrs[i].value = pd_array_of_attrs[i].value.val;
        }
        delete[] pd_array_of_attrs;
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_calculate_hash_value(std::vector<int8_t> &hash_val, const SessionHandle_t sess_hdl, const int8_t dev_id, const int32_t attr_count, const std::vector<fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t> &array_of_attrs, const std::vector<int32_t> &attr_sizes) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t[attr_count]();
        uint32_t *pd_attr_sizes = new uint32_t[attr_count]();
        hash_val = std::vector<int8_t>(2);
        int64_t result = 0;
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          if (attr_sizes[i] > 32) {
            pd_attr[i].value.stream = (uint8_t *)malloc((attr_sizes[i] + 7) / 8);
            memcpy(pd_attr[i].value.stream, item.stream.c_str(), (attr_sizes[i] + 7) / 8);
          } else {
            pd_attr[i].value.val = item.value;
          }
          pd_attr_sizes[i] = (uint32_t)attr_sizes[i];
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_calculate_hash_value(sess_hdl, dev_id, attr_count, pd_attr, pd_attr_sizes, (uint8_t *)hash_val.data(), 2);
        delete[] pd_attr;
        delete[] pd_attr_sizes;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return;
    }


    void hash_calc_Ingress_t_igr_hash_index_configure_input_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_hash_index_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t)input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_set(sess_hdl, dev_id, pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_hash_index_configure_input_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t pd_input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_get(sess_hdl, dev_id, &pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_hash_index_configure_input_t::type)pd_input);
    }

    void hash_calc_Ingress_t_igr_hash_index_configure_algorithm_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_hash_index_configure_algo_t::type algo) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t pd_algo = (p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t)algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_algorithm_set(sess_hdl, dev_id, pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_hash_index_configure_algorithm_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t pd_algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_algorithm_get(sess_hdl, dev_id, &pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_hash_index_configure_algo_t::type)pd_algo);
    }

    void hash_calc_Ingress_t_igr_hash_index_configure_seed_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const int64_t seed) {
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_seed_set(sess_hdl, dev_id, seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t hash_calc_Ingress_t_igr_hash_index_configure_seed_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        uint64_t seed = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_seed_get(sess_hdl, dev_id, &seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((int64_t)seed);
    }

    void hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_hash_index_configure_input_t::type input, const std::vector<fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t> &array_of_attrs) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t)input;
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t[array_of_attrs.size()]();
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          pd_attr[i].type = (p4_pd_fsmmf_input_field_attr_type_t)item.type;
          pd_attr[i].value.val = item.value;
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_set(sess_hdl, dev_id, pd_input, i, pd_attr);
        delete[] pd_attr;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_count_get(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_hash_index_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t)input;
        uint32_t attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return attr_count;
    }

    void hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_get(std::vector<fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t> &array_of_attrs, const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_hash_index_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t)input;
        uint32_t attr_count = 0, filled_attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *pd_array_of_attrs = new p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t[attr_count]();
        status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_get(sess_hdl, dev_id, pd_input, attr_count,
                pd_array_of_attrs, &filled_attr_count);
        if(status != 0) {
          delete[] pd_array_of_attrs;
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        /* Copy over the info from the PD struct to the thrift struct */
        array_of_attrs = std::vector<fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t>(filled_attr_count);
        for (int i=0; i < filled_attr_count; i++) {
          array_of_attrs[i].input_field = pd_array_of_attrs[i].input_field.id;
          array_of_attrs[i].type = (fsmmf_input_field_attr_type_t::type)pd_array_of_attrs[i].type;
          array_of_attrs[i].value = pd_array_of_attrs[i].value.val;
        }
        delete[] pd_array_of_attrs;
    }

    void hash_calc_Ingress_t_igr_hash_index_configure_calculate_hash_value(std::vector<int8_t> &hash_val, const SessionHandle_t sess_hdl, const int8_t dev_id, const int32_t attr_count, const std::vector<fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t> &array_of_attrs, const std::vector<int32_t> &attr_sizes) {
        p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t[attr_count]();
        uint32_t *pd_attr_sizes = new uint32_t[attr_count]();
        hash_val = std::vector<int8_t>(2);
        int64_t result = 0;
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          if (attr_sizes[i] > 32) {
            pd_attr[i].value.stream = (uint8_t *)malloc((attr_sizes[i] + 7) / 8);
            memcpy(pd_attr[i].value.stream, item.stream.c_str(), (attr_sizes[i] + 7) / 8);
          } else {
            pd_attr[i].value.val = item.value;
          }
          pd_attr_sizes[i] = (uint32_t)attr_sizes[i];
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_calculate_hash_value(sess_hdl, dev_id, attr_count, pd_attr, pd_attr_sizes, (uint8_t *)hash_val.data(), 2);
        delete[] pd_attr;
        delete[] pd_attr_sizes;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return;
    }


    void hash_calc_Ingress_t_igr_identity_hasher2_configure_input_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t)input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_set(sess_hdl, dev_id, pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher2_configure_input_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t pd_input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_get(sess_hdl, dev_id, &pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t::type)pd_input);
    }

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t::type algo) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t pd_algo = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t)algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_set(sess_hdl, dev_id, pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t pd_algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_get(sess_hdl, dev_id, &pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t::type)pd_algo);
    }

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const int64_t seed) {
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_set(sess_hdl, dev_id, seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        uint64_t seed = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_get(sess_hdl, dev_id, &seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((int64_t)seed);
    }

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t::type input, const std::vector<fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> &array_of_attrs) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t)input;
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t[array_of_attrs.size()]();
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          pd_attr[i].type = (p4_pd_fsmmf_input_field_attr_type_t)item.type;
          pd_attr[i].value.val = item.value;
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_set(sess_hdl, dev_id, pd_input, i, pd_attr);
        delete[] pd_attr;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t)input;
        uint32_t attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return attr_count;
    }

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_get(std::vector<fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> &array_of_attrs, const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t)input;
        uint32_t attr_count = 0, filled_attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *pd_array_of_attrs = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t[attr_count]();
        status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_get(sess_hdl, dev_id, pd_input, attr_count,
                pd_array_of_attrs, &filled_attr_count);
        if(status != 0) {
          delete[] pd_array_of_attrs;
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        /* Copy over the info from the PD struct to the thrift struct */
        array_of_attrs = std::vector<fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t>(filled_attr_count);
        for (int i=0; i < filled_attr_count; i++) {
          array_of_attrs[i].input_field = pd_array_of_attrs[i].input_field.id;
          array_of_attrs[i].type = (fsmmf_input_field_attr_type_t::type)pd_array_of_attrs[i].type;
          array_of_attrs[i].value = pd_array_of_attrs[i].value.val;
        }
        delete[] pd_array_of_attrs;
    }

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_calculate_hash_value(std::vector<int8_t> &hash_val, const SessionHandle_t sess_hdl, const int8_t dev_id, const int32_t attr_count, const std::vector<fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> &array_of_attrs, const std::vector<int32_t> &attr_sizes) {
        p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t[attr_count]();
        uint32_t *pd_attr_sizes = new uint32_t[attr_count]();
        hash_val = std::vector<int8_t>(4);
        int64_t result = 0;
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          if (attr_sizes[i] > 32) {
            pd_attr[i].value.stream = (uint8_t *)malloc((attr_sizes[i] + 7) / 8);
            memcpy(pd_attr[i].value.stream, item.stream.c_str(), (attr_sizes[i] + 7) / 8);
          } else {
            pd_attr[i].value.val = item.value;
          }
          pd_attr_sizes[i] = (uint32_t)attr_sizes[i];
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_calculate_hash_value(sess_hdl, dev_id, attr_count, pd_attr, pd_attr_sizes, (uint8_t *)hash_val.data(), 4);
        delete[] pd_attr;
        delete[] pd_attr_sizes;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return;
    }


    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t)input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_set(sess_hdl, dev_id, pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t pd_input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_get(sess_hdl, dev_id, &pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t::type)pd_input);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t::type algo) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t pd_algo = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t)algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_set(sess_hdl, dev_id, pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t pd_algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_get(sess_hdl, dev_id, &pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t::type)pd_algo);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const int64_t seed) {
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_set(sess_hdl, dev_id, seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        uint64_t seed = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_get(sess_hdl, dev_id, &seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((int64_t)seed);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t::type input, const std::vector<fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t> &array_of_attrs) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t)input;
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t[array_of_attrs.size()]();
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          pd_attr[i].type = (p4_pd_fsmmf_input_field_attr_type_t)item.type;
          pd_attr[i].value.val = item.value;
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_set(sess_hdl, dev_id, pd_input, i, pd_attr);
        delete[] pd_attr;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_count_get(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t)input;
        uint32_t attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return attr_count;
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_get(std::vector<fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t> &array_of_attrs, const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t)input;
        uint32_t attr_count = 0, filled_attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *pd_array_of_attrs = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t[attr_count]();
        status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_get(sess_hdl, dev_id, pd_input, attr_count,
                pd_array_of_attrs, &filled_attr_count);
        if(status != 0) {
          delete[] pd_array_of_attrs;
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        /* Copy over the info from the PD struct to the thrift struct */
        array_of_attrs = std::vector<fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t>(filled_attr_count);
        for (int i=0; i < filled_attr_count; i++) {
          array_of_attrs[i].input_field = pd_array_of_attrs[i].input_field.id;
          array_of_attrs[i].type = (fsmmf_input_field_attr_type_t::type)pd_array_of_attrs[i].type;
          array_of_attrs[i].value = pd_array_of_attrs[i].value.val;
        }
        delete[] pd_array_of_attrs;
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_calculate_hash_value(std::vector<int8_t> &hash_val, const SessionHandle_t sess_hdl, const int8_t dev_id, const int32_t attr_count, const std::vector<fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t> &array_of_attrs, const std::vector<int32_t> &attr_sizes) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t[attr_count]();
        uint32_t *pd_attr_sizes = new uint32_t[attr_count]();
        hash_val = std::vector<int8_t>(2);
        int64_t result = 0;
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          if (attr_sizes[i] > 32) {
            pd_attr[i].value.stream = (uint8_t *)malloc((attr_sizes[i] + 7) / 8);
            memcpy(pd_attr[i].value.stream, item.stream.c_str(), (attr_sizes[i] + 7) / 8);
          } else {
            pd_attr[i].value.val = item.value;
          }
          pd_attr_sizes[i] = (uint32_t)attr_sizes[i];
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_calculate_hash_value(sess_hdl, dev_id, attr_count, pd_attr, pd_attr_sizes, (uint8_t *)hash_val.data(), 2);
        delete[] pd_attr;
        delete[] pd_attr_sizes;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return;
    }


    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t)input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_set(sess_hdl, dev_id, pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t pd_input;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_get(sess_hdl, dev_id, &pd_input);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t::type)pd_input);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t::type algo) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t pd_algo = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t)algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_set(sess_hdl, dev_id, pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t pd_algo;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_get(sess_hdl, dev_id, &pd_algo);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t::type)pd_algo);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const int64_t seed) {
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_set(sess_hdl, dev_id, seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int64_t hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_get(const SessionHandle_t sess_hdl, const int8_t dev_id) {
        uint64_t seed = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_get(sess_hdl, dev_id, &seed);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return ((int64_t)seed);
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_set(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t::type input, const std::vector<fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t> &array_of_attrs) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t)input;
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t[array_of_attrs.size()]();
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          pd_attr[i].type = (p4_pd_fsmmf_input_field_attr_type_t)item.type;
          pd_attr[i].value.val = item.value;
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_set(sess_hdl, dev_id, pd_input, i, pd_attr);
        delete[] pd_attr;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
    }

    int32_t hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_count_get(const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t)input;
        uint32_t attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return attr_count;
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_get(std::vector<fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t> &array_of_attrs, const SessionHandle_t sess_hdl, const int8_t dev_id, const fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t::type input) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t pd_input = (p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t)input;
        uint32_t attr_count = 0, filled_attr_count = 0;
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_count_get(sess_hdl, dev_id, pd_input, &attr_count);
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *pd_array_of_attrs = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t[attr_count]();
        status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_get(sess_hdl, dev_id, pd_input, attr_count,
                pd_array_of_attrs, &filled_attr_count);
        if(status != 0) {
          delete[] pd_array_of_attrs;
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        /* Copy over the info from the PD struct to the thrift struct */
        array_of_attrs = std::vector<fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t>(filled_attr_count);
        for (int i=0; i < filled_attr_count; i++) {
          array_of_attrs[i].input_field = pd_array_of_attrs[i].input_field.id;
          array_of_attrs[i].type = (fsmmf_input_field_attr_type_t::type)pd_array_of_attrs[i].type;
          array_of_attrs[i].value = pd_array_of_attrs[i].value.val;
        }
        delete[] pd_array_of_attrs;
    }

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_calculate_hash_value(std::vector<int8_t> &hash_val, const SessionHandle_t sess_hdl, const int8_t dev_id, const int32_t attr_count, const std::vector<fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t> &array_of_attrs, const std::vector<int32_t> &attr_sizes) {
        p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *pd_attr = new p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t[attr_count]();
        uint32_t *pd_attr_sizes = new uint32_t[attr_count]();
        hash_val = std::vector<int8_t>(2);
        int64_t result = 0;
        int i = 0;
        /* Copy over the info from the thrift struct to the PD struct */
        for (auto & item : array_of_attrs) {
          pd_attr[i].input_field.id = item.input_field;
          if (attr_sizes[i] > 32) {
            pd_attr[i].value.stream = (uint8_t *)malloc((attr_sizes[i] + 7) / 8);
            memcpy(pd_attr[i].value.stream, item.stream.c_str(), (attr_sizes[i] + 7) / 8);
          } else {
            pd_attr[i].value.val = item.value;
          }
          pd_attr_sizes[i] = (uint32_t)attr_sizes[i];
          i++;
        }
        int status = p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_calculate_hash_value(sess_hdl, dev_id, attr_count, pd_attr, pd_attr_sizes, (uint8_t *)hash_val.data(), 2);
        delete[] pd_attr;
        delete[] pd_attr_sizes;
        if(status != 0) {
          InvalidTableOperation iop;
          iop.code = status;
          throw iop;
        }
        return;
    }


private:
    static inline bf_dev_pipe_t i16_to_bf_pipe(int16_t pipe) {
      return (pipe == -1) ? BF_DEV_PIPE_ALL : (bf_dev_pipe_t)pipe;
    }
};
