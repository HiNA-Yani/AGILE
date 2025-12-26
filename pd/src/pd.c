#include <pd/pd.h>
#include <pipe_mgr/pipe_mgr_intf.h>
#include <pipe_mgr/pipe_mgr_mirror_intf.h>
#include <dvm/bf_drv_intf.h>

#include <tofino/pdfixed/pd_ms.h>

#include <time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <target-sys/bf_sal/bf_sys_assert.h>
#include <target-sys/bf_sal/bf_sys_sem.h>
#include <target-sys/bf_sal/bf_sys_mem.h>

#define PD_DEBUG 1

#define PIPE_MGR_SUCCESS 0
#define PIPE_MATCH_ACTION_MAX_SIZE 128

#define BYTE_ROUND_UP(x) ((x + 7) >> 3)

bf_drv_client_handle_t bf_drv_hdl;

static void build_pd_res_spec(const pipe_action_spec_t *action_spec,
                              pd_res_spec_t **res_spec,
                              int *resource_cnt) {
  if (action_spec->resource_count) {
    *res_spec = bf_sys_calloc(action_spec->resource_count,
                              sizeof(pd_res_spec_t));
    unsigned i = 0;
    int idx = 0;
    for (i = 0; i < action_spec->resource_count; i++) {
      if (action_spec->resources[i].tag == PIPE_RES_ACTION_TAG_ATTACHED) {
        (*res_spec)[idx].tbl_hdl = action_spec->resources[i].tbl_hdl;
        (*res_spec)[idx].tbl_idx = action_spec->resources[i].tbl_idx;
        idx++;
      }
    }
    *resource_cnt = idx;
  } else {
    *resource_cnt = 0;
  }
  return;
}



static p4_pd_ms_table_state_t *ms__state;

static bf_status_t p4_pd_fsmmf_dev_remove(bf_dev_id_t dev_id) {

  p4_pd_ms_destroy_state_for_dev(ms__state, dev_id); 
  p4_pd_ms_destroy_txn_state_for_dev(dev_id);
  return BF_SUCCESS;
}

static bf_status_t p4_pd_fsmmf_dev_log(bf_dev_id_t dev_id, cJSON *pd_node) {
  cJSON *profs, *prof;
  cJSON_AddStringToObject(pd_node, "name", "fsmmf");
  cJSON_AddItemToObject(pd_node, "act_profs", profs = cJSON_CreateArray());

  cJSON_AddItemToArray(profs, prof = cJSON_CreateObject());
  cJSON_AddStringToObject(prof, "name", "");
  p4_pd_ms_log_state(dev_id, ms__state, prof);

  return BF_SUCCESS;
}

static bf_status_t p4_pd_fsmmf_dev_restore(bf_dev_id_t dev_id, cJSON *pd_node) {
  cJSON *profs, *prof;

  profs = cJSON_GetObjectItem(pd_node, "act_profs");
  for (prof = profs->child; prof; prof = prof->next) {

    if (strcmp(cJSON_GetObjectItem(prof, "name")->valuestring, "") == 0) {
      p4_pd_ms_restore_state(dev_id, ms__state, prof);
    }
  }

  return BF_SUCCESS;
}

void p4_pd_fsmmf_init(void) {
  p4_pd_ms_init();

  ms__state = p4_pd_ms_init_state();
  bf_status_t r = bf_drv_register("p4_pd_fsmmf_pd", &bf_drv_hdl);
  assert(r == BF_SUCCESS);
  bf_drv_client_callbacks_t callbacks = {0};
  callbacks.device_del = p4_pd_fsmmf_dev_remove;
  callbacks.device_log = p4_pd_fsmmf_dev_log;
  callbacks.device_restore = p4_pd_fsmmf_dev_restore;
  bf_drv_client_register_callbacks(bf_drv_hdl, &callbacks, BF_CLIENT_PRIO_2);
}

void p4_pd_fsmmf_device_state_cleanup(uint8_t device_id) {
  p4_pd_ms_destroy_state_for_dev(ms__state, device_id);
}

void p4_pd_fsmmf_cleanup(void) {

  p4_pd_ms_cleanup();

  bf_drv_deregister(bf_drv_hdl);
}

static inline void build_key_IngressParser__PORT_METADATA
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp16 = htons(match_spec->ig_intr_md_ingress_port);
  memcpy(match_bits, &tmp16, 2);
#else
  memcpy(match_bits, ((char *) &match_spec->ig_intr_md_ingress_port) + 0, 2);
#endif
  match_bits += 2;

}

static inline void build_key_Ingress_t_igr_tiForward
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  memcpy(match_bits, &match_spec->hdr_ethernet_dst_addr, 6);
#else
  memcpy(match_bits, ((char *) &match_spec->hdr_ethernet_dst_addr) + 0, 6);
#endif
  match_bits += 6;

}

static inline void build_key_Ingress_t_igr_tiRate
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->table_key);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->table_key) + 0, 4);
#endif
  match_bits += 4;

}

static inline void build_key_Ingress_t_igr_tiCalc_dt_x_rate
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp16 = htons(match_spec->log_dt);
  memcpy(match_bits, &tmp16, 2);
#else
  memcpy(match_bits, ((char *) &match_spec->log_dt) + 0, 2);
#endif
  match_bits += 2;


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->rate);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->rate) + 0, 4);
#endif
  match_bits += 4;

}

static inline void build_key_Ingress_t_igr_tiRC_nag
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->md_RC);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->md_RC) + 0, 4);
#endif
  match_bits += 4;

}

static inline void build_key_Ingress_t_igr_tiGapRC_pos
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->gapRC);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->gapRC) + 0, 4);
#endif
  match_bits += 4;

}

static inline void build_mask_Ingress_t_igr_tiRC_nag
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec
)
{
  uint8_t *value_bits = pipe_match_spec->match_value_bits;
  uint8_t *mask_bits = pipe_match_spec->match_mask_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
  uint32_t i; /* for value masking */
  int bits_to_reset; /* for lpm mask */
  (void) bits_to_reset; /* compiler */


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->md_RC_mask);
  memcpy(mask_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(mask_bits, ((char *) &match_spec->md_RC_mask) + 0, 4);
#endif
  for (i = 0; i < 4; i++) {
    value_bits[i] &= mask_bits[i];
  }
  mask_bits += 4;
  value_bits += 4;

}

static inline void build_mask_Ingress_t_igr_tiGapRC_pos
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec
)
{
  uint8_t *value_bits = pipe_match_spec->match_value_bits;
  uint8_t *mask_bits = pipe_match_spec->match_mask_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
  uint32_t i; /* for value masking */
  int bits_to_reset; /* for lpm mask */
  (void) bits_to_reset; /* compiler */


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->gapRC_mask);
  memcpy(mask_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(mask_bits, ((char *) &match_spec->gapRC_mask) + 0, 4);
#endif
  for (i = 0; i < 4; i++) {
    value_bits[i] &= mask_bits[i];
  }
  mask_bits += 4;
  value_bits += 4;

}



/* Dynamic Exm Table Key Mask */



static inline void build_match_spec_IngressParser__PORT_METADATA
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;

  build_key_IngressParser__PORT_METADATA(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

static inline void build_match_spec_Ingress_t_igr_tiForward
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;

  build_key_Ingress_t_igr_tiForward(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

static inline void build_match_spec_Ingress_t_igr_tiRate
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;

  build_key_Ingress_t_igr_tiRate(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

static inline void build_match_spec_Ingress_t_igr_tiCalc_dt_x_rate
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;

  build_key_Ingress_t_igr_tiCalc_dt_x_rate(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

static inline void build_match_spec_Ingress_t_igr_tiRC_nag
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;

  build_key_Ingress_t_igr_tiRC_nag(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  build_mask_Ingress_t_igr_tiRC_nag(pipe_match_spec, match_spec);
}

static inline void build_match_spec_Ingress_t_igr_tiGapRC_pos
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;

  build_key_Ingress_t_igr_tiGapRC_pos(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  build_mask_Ingress_t_igr_tiGapRC_pos(pipe_match_spec, match_spec);
}




static inline void build_action_spec_set_port_metadata
(
 pipe_action_data_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  (void) data_bits;

#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
#ifdef LITTLE_ENDIAN_CALLER
  memcpy(data_bits, &action_spec->action_ig_intr_md, 8);
#else
  memcpy(data_bits, ((char *) &action_spec->action_ig_intr_md) + 0, 8);
#endif

  data_bits += 8;

}

static inline void build_indirect_resources_set_port_metadata
(
 pipe_action_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec
)
{

}

static inline void build_action_spec_Ingress_t_igr_aiSetEgress
(
 pipe_action_data_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  (void) data_bits;

#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
#ifdef LITTLE_ENDIAN_CALLER
  tmp16 = htons(action_spec->action_egr_port);
  memcpy(data_bits, &tmp16, 2);
#else
  memcpy(data_bits, ((char *) &action_spec->action_egr_port) + 0, 2);
#endif

  data_bits += 2;

}

static inline void build_indirect_resources_Ingress_t_igr_aiSetEgress
(
 pipe_action_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
)
{

}

static inline void build_action_spec_Ingress_t_igr_aiRate
(
 pipe_action_data_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  (void) data_bits;

#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_Allocate_rate);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_Allocate_rate) + 0, 4);
#endif

  data_bits += 4;

}

static inline void build_indirect_resources_Ingress_t_igr_aiRate
(
 pipe_action_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec
)
{

}

static inline void build_action_spec_Ingress_t_igr_aiCalc_dt_x_rate
(
 pipe_action_data_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  (void) data_bits;

#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_Calc_dt_x_rate);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_Calc_dt_x_rate) + 0, 4);
#endif

  data_bits += 4;
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_Calc_dt_x_rate_B);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_Calc_dt_x_rate_B) + 0, 4);
#endif

  data_bits += 4;

}

static inline void build_indirect_resources_Ingress_t_igr_aiCalc_dt_x_rate
(
 pipe_action_spec_t *pipe_action_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec
)
{

}



static inline void unbuild_key_IngressParser__PORT_METADATA
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  memcpy(&tmp16, match_bits, 2);
  match_spec->ig_intr_md_ingress_port = ntohs(tmp16);
#else
  memcpy(((char *) &match_spec->ig_intr_md_ingress_port) + 0, match_bits, 2);
#endif
  match_bits += 2;

}

static inline void unbuild_key_Ingress_t_igr_tiForward
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  memcpy(&match_spec->hdr_ethernet_dst_addr, match_bits, 6);
#else
  memcpy(((char *) &match_spec->hdr_ethernet_dst_addr) + 0, match_bits, 6);
#endif
  match_bits += 6;

}

static inline void unbuild_key_Ingress_t_igr_tiRate
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, match_bits, 4);
  match_spec->table_key = ntohl(tmp32);
#else
  memcpy(((char *) &match_spec->table_key) + 0, match_bits, 4);
#endif
  match_bits += 4;

}

static inline void unbuild_key_Ingress_t_igr_tiCalc_dt_x_rate
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  memcpy(&tmp16, match_bits, 2);
  match_spec->log_dt = ntohs(tmp16);
#else
  memcpy(((char *) &match_spec->log_dt) + 0, match_bits, 2);
#endif
  match_bits += 2;


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, match_bits, 4);
  match_spec->rate = ntohl(tmp32);
#else
  memcpy(((char *) &match_spec->rate) + 0, match_bits, 4);
#endif
  match_bits += 4;

}

static inline void unbuild_key_Ingress_t_igr_tiRC_nag
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, match_bits, 4);
  match_spec->md_RC = ntohl(tmp32);
#else
  memcpy(((char *) &match_spec->md_RC) + 0, match_bits, 4);
#endif
  match_bits += 4;

}

static inline void unbuild_key_Ingress_t_igr_tiGapRC_pos
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, match_bits, 4);
  match_spec->gapRC = ntohl(tmp32);
#else
  memcpy(((char *) &match_spec->gapRC) + 0, match_bits, 4);
#endif
  match_bits += 4;

}

static inline void unbuild_mask_Ingress_t_igr_tiRC_nag
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * match_spec
)
{
  uint8_t *mask_bits = pipe_match_spec->match_mask_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
  int pref_len;
  int i;
  (void) pref_len;
  (void) i;


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, mask_bits, 4);
  match_spec->md_RC_mask = ntohl(tmp32);
#else
  memcpy(((char *) &match_spec->md_RC_mask) + 0, mask_bits, 4);
#endif
  mask_bits += 4;

}

static inline void unbuild_mask_Ingress_t_igr_tiGapRC_pos
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * match_spec
)
{
  uint8_t *mask_bits = pipe_match_spec->match_mask_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
  int pref_len;
  int i;
  (void) pref_len;
  (void) i;


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, mask_bits, 4);
  match_spec->gapRC_mask = ntohl(tmp32);
#else
  memcpy(((char *) &match_spec->gapRC_mask) + 0, mask_bits, 4);
#endif
  mask_bits += 4;

}


static inline void unbuild_action_spec_set_port_metadata
(
 pipe_action_data_spec_t *pipe_action_spec,
 pd_res_spec_t *res_spec,
 int num_res,
 p4_pd_fsmmf_set_port_metadata_action_spec_t * action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  unsigned i = 0;
  (void)i;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif

#ifdef LITTLE_ENDIAN_CALLER
  memcpy(&action_spec->action_ig_intr_md, data_bits, 8);
#else
  memcpy(((char *) &action_spec->action_ig_intr_md) + 0, data_bits, 8);
#endif
  data_bits += 8;
}

static inline void unbuild_action_spec_Ingress_t_igr_aiSetEgress
(
 pipe_action_data_spec_t *pipe_action_spec,
 pd_res_spec_t *res_spec,
 int num_res,
 p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  unsigned i = 0;
  (void)i;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif

#ifdef LITTLE_ENDIAN_CALLER
  memcpy(&tmp16, data_bits, 2);
  action_spec->action_egr_port = ntohs(tmp16);

#else
  memcpy(((char *) &action_spec->action_egr_port) + 0, data_bits, 2);
#endif
  data_bits += 2;
}

static inline void unbuild_action_spec_Ingress_t_igr_aiRate
(
 pipe_action_data_spec_t *pipe_action_spec,
 pd_res_spec_t *res_spec,
 int num_res,
 p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  unsigned i = 0;
  (void)i;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif

#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, data_bits, 4);
  action_spec->action_Allocate_rate = ntohl(tmp32);

#else
  memcpy(((char *) &action_spec->action_Allocate_rate) + 0, data_bits, 4);
#endif
  data_bits += 4;
}

static inline void unbuild_action_spec_Ingress_t_igr_aiCalc_dt_x_rate
(
 pipe_action_data_spec_t *pipe_action_spec,
 pd_res_spec_t *res_spec,
 int num_res,
 p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  unsigned i = 0;
  (void)i;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif

#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, data_bits, 4);
  action_spec->action_Calc_dt_x_rate = ntohl(tmp32);

#else
  memcpy(((char *) &action_spec->action_Calc_dt_x_rate) + 0, data_bits, 4);
#endif
  data_bits += 4;

#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = 0;
  memcpy(((char *) &tmp32) + 0, data_bits, 4);
  action_spec->action_Calc_dt_x_rate_B = ntohl(tmp32);

#else
  memcpy(((char *) &action_spec->action_Calc_dt_x_rate_B) + 0, data_bits, 4);
#endif
  data_bits += 4;
}



/* IDLE TIME CONFIG */



/* ADD ENTRIES */






static void register_Ingress_t_igr_riTs_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_riTs_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ridt_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ridt_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_count_til_drop_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_count_til_drop_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_riRC_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_riRC_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ri_dt_x_rate_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ri_dt_x_rate_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_bottleneckF_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_bottleneckF_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ritestgapRC_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ritestgapRC_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ritestburstdrop_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ritestburstdrop_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ri_gapRC_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ri_gapRC_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_bottlenecked_rate_bottleneckedRate_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_bottlenecked_rate_bottleneckedRate_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ri_ts_ms_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ri_ts_ms_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_riburstStage_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_riburstStage_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_fCount_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_fCount_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_count_til_ecn_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_count_til_ecn_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ri_lograte_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ri_lograte_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void lpf_spec_pd_to_pipe(p4_pd_lpf_spec_t *pd_spec,
                                pipe_lpf_spec_t *pipe_spec) {
  pipe_spec->lpf_type = pd_spec->lpf_type;
  pipe_spec->gain_decay_separate_time_constant =
    pd_spec->gain_decay_separate_time_constant;
  pipe_spec->gain_time_constant = pd_spec->gain_time_constant;
  pipe_spec->decay_time_constant = pd_spec->decay_time_constant;
  pipe_spec->time_constant = pd_spec->time_constant;
  pipe_spec->output_scale_down_factor = pd_spec->output_scale_down_factor;
}

static void lpf_spec_pipe_to_pd(p4_pd_lpf_spec_t *pd_spec,
                                pipe_lpf_spec_t *pipe_spec) {
  pd_spec->lpf_type = pipe_spec->lpf_type;
  pd_spec->gain_decay_separate_time_constant =
    pipe_spec->gain_decay_separate_time_constant;
  pd_spec->gain_time_constant = pipe_spec->gain_time_constant;
  pd_spec->decay_time_constant = pipe_spec->decay_time_constant;
  pd_spec->time_constant = pipe_spec->time_constant;
  pd_spec->output_scale_down_factor = pipe_spec->output_scale_down_factor;
}


p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_IngressParser__PORT_METADATA(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_match_spec_to_ent_hdl(sess_hdl,
            pipe_mgr_dev_tgt,
            16777217,
            &pipe_match_spec,
            entry_hdl,
            false /* light_pipe_validation */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiForward(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_match_spec_to_ent_hdl(sess_hdl,
            pipe_mgr_dev_tgt,
            16777223,
            &pipe_match_spec,
            entry_hdl,
            false /* light_pipe_validation */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  build_match_spec_Ingress_t_igr_tiRate(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_match_spec_to_ent_hdl(sess_hdl,
            pipe_mgr_dev_tgt,
            16777232,
            &pipe_match_spec,
            entry_hdl,
            false /* light_pipe_validation */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiCalc_dt_x_rate(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_match_spec_to_ent_hdl(sess_hdl,
            pipe_mgr_dev_tgt,
            16777239,
            &pipe_match_spec,
            entry_hdl,
            false /* light_pipe_validation */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_match_spec_to_ent_hdl(sess_hdl,
            pipe_mgr_dev_tgt,
            16777247,
            &pipe_match_spec,
            entry_hdl,
            false /* light_pipe_validation */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_match_spec_to_ent_hdl(sess_hdl,
            pipe_mgr_dev_tgt,
            16777252,
            &pipe_match_spec,
            entry_hdl,
            false /* light_pipe_validation */);
}



/* Dynamic Exm Table Key Mask */



p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_add_with_set_port_metadata
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_IngressParser__PORT_METADATA(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;

  build_action_spec_set_port_metadata(pipe_action_data_spec, action_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777217, &pipe_match_spec,
					       536870912, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiForward(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[2];
  memset(pipe_action_data_bits, 0, 2);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 9;
  pipe_action_data_spec->num_action_data_bytes = 2;
  pipe_action_spec.resource_count = 0;

  build_action_spec_Ingress_t_igr_aiSetEgress(pipe_action_data_spec, action_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777223, &pipe_match_spec,
					       536870916, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiForward(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777223, &pipe_match_spec,
					       536870917, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  build_match_spec_Ingress_t_igr_tiRate(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[4];
  memset(pipe_action_data_bits, 0, 4);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 32;
  pipe_action_data_spec->num_action_data_bytes = 4;
  pipe_action_spec.resource_count = 0;

  build_action_spec_Ingress_t_igr_aiRate(pipe_action_data_spec, action_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777232, &pipe_match_spec,
					       536870926, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiCalc_dt_x_rate(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;

  build_action_spec_Ingress_t_igr_aiCalc_dt_x_rate(pipe_action_data_spec, action_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777239, &pipe_match_spec,
					       536870928, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777247, &pipe_match_spec,
					       536870936, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777247, &pipe_match_spec,
					       536870934, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777247, &pipe_match_spec,
					       536870935, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777252, &pipe_match_spec,
					       536870944, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777252, &pipe_match_spec,
					       536870942, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777252, &pipe_match_spec,
					       536870943, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}


/* DELETE ENTRIES */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{
  return pipe_mgr_mat_ent_del(sess_hdl,
            dev_id,
            16777217,
            entry_hdl,
            0 /* TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_IngressParser__PORT_METADATA(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777217,
            &pipe_match_spec,
            0);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{
  return pipe_mgr_mat_ent_del(sess_hdl,
            dev_id,
            16777223,
            entry_hdl,
            0 /* TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiForward(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777223,
            &pipe_match_spec,
            0);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{
  return pipe_mgr_mat_ent_del(sess_hdl,
            dev_id,
            16777232,
            entry_hdl,
            0 /* TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  build_match_spec_Ingress_t_igr_tiRate(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777232,
            &pipe_match_spec,
            0);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{
  return pipe_mgr_mat_ent_del(sess_hdl,
            dev_id,
            16777239,
            entry_hdl,
            0 /* TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiCalc_dt_x_rate(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777239,
            &pipe_match_spec,
            0);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{
  return pipe_mgr_mat_ent_del(sess_hdl,
            dev_id,
            16777247,
            entry_hdl,
            0 /* TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777247,
            &pipe_match_spec,
            0);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{
  return pipe_mgr_mat_ent_del(sess_hdl,
            dev_id,
            16777252,
            entry_hdl,
            0 /* TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777252,
            &pipe_match_spec,
            0);
}


/* Get default entry handle */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_table_get_default_entry_handle(sess_hdl, pipe_mgr_dev_tgt,
			                              16777217, entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  p4_pd_status_t status = BF_SUCCESS;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  pipe_action_spec_t pipe_action_spec = {0};
  p4_pd_act_hdl_t act_fn_hdl;

  (void)action_spec;

  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  status = pipe_mgr_table_get_default_entry(sess_hdl, pipe_mgr_dev_tgt, 16777217,
      &pipe_action_spec, &act_fn_hdl, read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    return BF_UNEXPECTED;
  }
  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
    case 536870912:
      action_spec->name = p4_pd_fsmmf_set_port_metadata;
      unbuild_action_spec_set_port_metadata(pipe_action_data_spec,
                                    res_spec,
                                    resource_cnt,
                                    &action_spec->u.p4_pd_fsmmf_set_port_metadata);
      break;
  default:
    return BF_UNEXPECTED;
  }
  if (res_spec) {
    bf_sys_free(res_spec);
  }


  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_table_get_default_entry_handle(sess_hdl, pipe_mgr_dev_tgt,
			                              16777223, entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  p4_pd_status_t status = BF_SUCCESS;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  pipe_action_spec_t pipe_action_spec = {0};
  p4_pd_act_hdl_t act_fn_hdl;

  (void)action_spec;

  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  status = pipe_mgr_table_get_default_entry(sess_hdl, pipe_mgr_dev_tgt, 16777223,
      &pipe_action_spec, &act_fn_hdl, read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    return BF_UNEXPECTED;
  }
  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
    case 536870916:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiSetEgress;
      unbuild_action_spec_Ingress_t_igr_aiSetEgress(pipe_action_data_spec,
                                    res_spec,
                                    resource_cnt,
                                    &action_spec->u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress);
      break;
    case 536870917:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiNoop;
      break;
  default:
    return BF_UNEXPECTED;
  }
  if (res_spec) {
    bf_sys_free(res_spec);
  }


  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_table_get_default_entry_handle(sess_hdl, pipe_mgr_dev_tgt,
			                              16777232, entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  p4_pd_status_t status = BF_SUCCESS;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  pipe_action_spec_t pipe_action_spec = {0};
  p4_pd_act_hdl_t act_fn_hdl;

  (void)action_spec;

  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  status = pipe_mgr_table_get_default_entry(sess_hdl, pipe_mgr_dev_tgt, 16777232,
      &pipe_action_spec, &act_fn_hdl, read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    return BF_UNEXPECTED;
  }
  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
    case 536870926:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiRate;
      unbuild_action_spec_Ingress_t_igr_aiRate(pipe_action_data_spec,
                                    res_spec,
                                    resource_cnt,
                                    &action_spec->u.p4_pd_fsmmf_Ingress_t_igr_aiRate);
      break;
  default:
    return BF_UNEXPECTED;
  }
  if (res_spec) {
    bf_sys_free(res_spec);
  }


  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_table_get_default_entry_handle(sess_hdl, pipe_mgr_dev_tgt,
			                              16777239, entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  p4_pd_status_t status = BF_SUCCESS;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  pipe_action_spec_t pipe_action_spec = {0};
  p4_pd_act_hdl_t act_fn_hdl;

  (void)action_spec;

  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  status = pipe_mgr_table_get_default_entry(sess_hdl, pipe_mgr_dev_tgt, 16777239,
      &pipe_action_spec, &act_fn_hdl, read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    return BF_UNEXPECTED;
  }
  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
    case 536870928:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate;
      unbuild_action_spec_Ingress_t_igr_aiCalc_dt_x_rate(pipe_action_data_spec,
                                    res_spec,
                                    resource_cnt,
                                    &action_spec->u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate);
      break;
  default:
    return BF_UNEXPECTED;
  }
  if (res_spec) {
    bf_sys_free(res_spec);
  }


  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_table_get_default_entry_handle(sess_hdl, pipe_mgr_dev_tgt,
			                              16777247, entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  p4_pd_status_t status = BF_SUCCESS;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  pipe_action_spec_t pipe_action_spec = {0};
  p4_pd_act_hdl_t act_fn_hdl;

  (void)action_spec;

  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  status = pipe_mgr_table_get_default_entry(sess_hdl, pipe_mgr_dev_tgt, 16777247,
      &pipe_action_spec, &act_fn_hdl, read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    return BF_UNEXPECTED;
  }
  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
    case 536870936:
      action_spec->name = p4_pd_fsmmf_NoAction;
      break;
    case 536870934:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiRC_neg;
      break;
    case 536870935:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiRC_pos;
      break;
  default:
    return BF_UNEXPECTED;
  }
  if (res_spec) {
    bf_sys_free(res_spec);
  }


  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_table_get_default_entry_handle(sess_hdl, pipe_mgr_dev_tgt,
			                              16777252, entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  p4_pd_status_t status = BF_SUCCESS;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  pipe_action_spec_t pipe_action_spec = {0};
  p4_pd_act_hdl_t act_fn_hdl;

  (void)action_spec;

  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  status = pipe_mgr_table_get_default_entry(sess_hdl, pipe_mgr_dev_tgt, 16777252,
      &pipe_action_spec, &act_fn_hdl, read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    return BF_UNEXPECTED;
  }
  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
    case 536870944:
      action_spec->name = p4_pd_fsmmf_NoAction;
      break;
    case 536870942:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg;
      break;
    case 536870943:
      action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos;
      break;
  default:
    return BF_UNEXPECTED;
  }
  if (res_spec) {
    bf_sys_free(res_spec);
  }


  return status;
}




/* Clear default entry */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_mat_tbl_default_entry_reset(sess_hdl, pipe_mgr_dev_tgt,
			                                  16777217, 0);
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_mat_tbl_default_entry_reset(sess_hdl, pipe_mgr_dev_tgt,
			                                  16777223, 0);
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_mat_tbl_default_entry_reset(sess_hdl, pipe_mgr_dev_tgt,
			                                  16777232, 0);
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_mat_tbl_default_entry_reset(sess_hdl, pipe_mgr_dev_tgt,
			                                  16777239, 0);
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_mat_tbl_default_entry_reset(sess_hdl, pipe_mgr_dev_tgt,
			                                  16777247, 0);
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = pd_dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = pd_dev_tgt.dev_pipe_id;
  return pipe_mgr_mat_tbl_default_entry_reset(sess_hdl, pipe_mgr_dev_tgt,
			                                  16777252, 0);
}



/* MODIFY TABLE PROPERTIES */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;
  prop_val.value = value.value;
  args_val.value = args.value;
  return pipe_mgr_tbl_set_property(
      sess_hdl, dev_id, 16777217, prop_type, prop_val, args_val);
}

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;

  p4_pd_status_t status = pipe_mgr_tbl_get_property(
      sess_hdl, dev_id, 16777217, prop_type, &prop_val, &args_val);

  if (status != PIPE_MGR_SUCCESS) {
    value->value = -1;
    args->value = -1;
  } else {
    value->value = prop_val.value;
    args->value = args_val.value;
  }

  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;
  prop_val.value = value.value;
  args_val.value = args.value;
  return pipe_mgr_tbl_set_property(
      sess_hdl, dev_id, 16777223, prop_type, prop_val, args_val);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;

  p4_pd_status_t status = pipe_mgr_tbl_get_property(
      sess_hdl, dev_id, 16777223, prop_type, &prop_val, &args_val);

  if (status != PIPE_MGR_SUCCESS) {
    value->value = -1;
    args->value = -1;
  } else {
    value->value = prop_val.value;
    args->value = args_val.value;
  }

  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;
  prop_val.value = value.value;
  args_val.value = args.value;
  return pipe_mgr_tbl_set_property(
      sess_hdl, dev_id, 16777232, prop_type, prop_val, args_val);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;

  p4_pd_status_t status = pipe_mgr_tbl_get_property(
      sess_hdl, dev_id, 16777232, prop_type, &prop_val, &args_val);

  if (status != PIPE_MGR_SUCCESS) {
    value->value = -1;
    args->value = -1;
  } else {
    value->value = prop_val.value;
    args->value = args_val.value;
  }

  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;
  prop_val.value = value.value;
  args_val.value = args.value;
  return pipe_mgr_tbl_set_property(
      sess_hdl, dev_id, 16777239, prop_type, prop_val, args_val);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;

  p4_pd_status_t status = pipe_mgr_tbl_get_property(
      sess_hdl, dev_id, 16777239, prop_type, &prop_val, &args_val);

  if (status != PIPE_MGR_SUCCESS) {
    value->value = -1;
    args->value = -1;
  } else {
    value->value = prop_val.value;
    args->value = args_val.value;
  }

  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;
  prop_val.value = value.value;
  args_val.value = args.value;
  return pipe_mgr_tbl_set_property(
      sess_hdl, dev_id, 16777247, prop_type, prop_val, args_val);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;

  p4_pd_status_t status = pipe_mgr_tbl_get_property(
      sess_hdl, dev_id, 16777247, prop_type, &prop_val, &args_val);

  if (status != PIPE_MGR_SUCCESS) {
    value->value = -1;
    args->value = -1;
  } else {
    value->value = prop_val.value;
    args->value = args_val.value;
  }

  return status;
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;
  prop_val.value = value.value;
  args_val.value = args.value;
  return pipe_mgr_tbl_set_property(
      sess_hdl, dev_id, 16777252, prop_type, prop_val, args_val);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
)
{
  pipe_mgr_tbl_prop_type_t prop_type = property;
  pipe_mgr_tbl_prop_value_t prop_val;
  pipe_mgr_tbl_prop_args_t args_val;

  p4_pd_status_t status = pipe_mgr_tbl_get_property(
      sess_hdl, dev_id, 16777252, prop_type, &prop_val, &args_val);

  if (status != PIPE_MGR_SUCCESS) {
    value->value = -1;
    args->value = -1;
  } else {
    value->value = prop_val.value;
    args->value = args_val.value;
  }

  return status;
}


/* MODIFY ENTRIES */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec
)
{

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_set_port_metadata(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777217,
             entry_hdl,
             536870912,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_IngressParser__PORT_METADATA(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_set_port_metadata(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777217,
             &pipe_match_spec,
             536870912,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
)
{

  uint8_t pipe_action_data_bits[2];
  memset(pipe_action_data_bits, 0, 2);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 9;
  pipe_action_data_spec->num_action_data_bytes = 2;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiSetEgress(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777223,
             entry_hdl,
             536870916,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiForward(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[2];
  memset(pipe_action_data_bits, 0, 2);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 9;
  pipe_action_data_spec->num_action_data_bytes = 2;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiSetEgress(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777223,
             &pipe_match_spec,
             536870916,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777223,
             entry_hdl,
             536870917,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiForward(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777223,
             &pipe_match_spec,
             536870917,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec
)
{

  uint8_t pipe_action_data_bits[4];
  memset(pipe_action_data_bits, 0, 4);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 32;
  pipe_action_data_spec->num_action_data_bytes = 4;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiRate(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777232,
             entry_hdl,
             536870926,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  build_match_spec_Ingress_t_igr_tiRate(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[4];
  memset(pipe_action_data_bits, 0, 4);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 32;
  pipe_action_data_spec->num_action_data_bytes = 4;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiRate(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777232,
             &pipe_match_spec,
             536870926,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec
)
{

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiCalc_dt_x_rate(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777239,
             entry_hdl,
             536870928,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiCalc_dt_x_rate(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiCalc_dt_x_rate(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777239,
             &pipe_match_spec,
             536870928,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777247,
             entry_hdl,
             536870936,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777247,
             &pipe_match_spec,
             536870936,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777247,
             entry_hdl,
             536870934,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777247,
             &pipe_match_spec,
             536870934,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777247,
             entry_hdl,
             536870935,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777247,
             &pipe_match_spec,
             536870935,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777252,
             entry_hdl,
             536870944,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777252,
             &pipe_match_spec,
             536870944,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777252,
             entry_hdl,
             536870942,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777252,
             &pipe_match_spec,
             536870942,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777252,
             entry_hdl,
             536870943,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[4];
  if (4) {
    memset(pipe_match_value_bits, 0, 4);
    memset(pipe_match_mask_bits, 0, 4);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.priority = priority;
  build_match_spec_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777252,
             &pipe_match_spec,
             536870943,
             &pipe_action_spec,
             0 /* flags, TODO */);
}



/* SET DEFAULT_ACTION */

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777223,
				      536870917,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_set_default_action_Ingress_t_igr_aiRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[4];
  memset(pipe_action_data_bits, 0, 4);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 32;
  pipe_action_data_spec->num_action_data_bytes = 4;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiRate(pipe_action_data_spec, action_spec);



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777232,
				      536870926,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_set_default_action_Ingress_t_igr_aiCalc_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiCalc_dt_x_rate(pipe_action_data_spec, action_spec);



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777239,
				      536870928,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777247,
				      536870936,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777247,
				      536870934,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777247,
				      536870935,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777252,
				      536870944,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777252,
				      536870942,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;



  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_default_entry_set(sess_hdl,
				      pipe_mgr_dev_tgt,
				      16777252,
				      536870943,
				      &pipe_action_spec,
				      0 /* flags TODO */,
				      entry_hdl);
}




/* INDIRECT ACTION DATA AND MATCH SELECT */





p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  bool read_from_hw = false;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_entry_count(sess_hdl, pipe_mgr_dev_tgt, 16777217, read_from_hw, count);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  bool read_from_hw = false;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_entry_count(sess_hdl, pipe_mgr_dev_tgt, 16777223, read_from_hw, count);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  bool read_from_hw = false;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_entry_count(sess_hdl, pipe_mgr_dev_tgt, 16777232, read_from_hw, count);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  bool read_from_hw = false;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_entry_count(sess_hdl, pipe_mgr_dev_tgt, 16777239, read_from_hw, count);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  bool read_from_hw = false;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_entry_count(sess_hdl, pipe_mgr_dev_tgt, 16777247, read_from_hw, count);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  bool read_from_hw = false;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_entry_count(sess_hdl, pipe_mgr_dev_tgt, 16777252, read_from_hw, count);
}



p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_first_entry_handle
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t *entry_handle
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_first_entry_handle(sess_hdl, 16777217, pipe_mgr_dev_tgt,
					 entry_handle);  
}

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_next_entry_handles
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t entry_handle,
  int n, p4_pd_entry_hdl_t *next_entry_handles
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_next_entry_handles(sess_hdl, 16777217, pipe_mgr_dev_tgt, entry_handle,
					 n, next_entry_handles);
}

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  (void)sess_hdl;

  p4_pd_act_hdl_t act_fn_hdl;

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_id;
  pipe_mgr_dev_tgt.dev_pipe_id = BF_DEV_PIPE_ALL;

  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2] = {0};
  uint8_t pipe_match_mask_bits[2] = {0};
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  pipe_match_spec.num_match_bytes = 2;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;

  pipe_action_spec_t pipe_action_spec = {0};
  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  p4_pd_status_t status = pipe_mgr_get_entry(sess_hdl, 16777217, pipe_mgr_dev_tgt,
                                             entry_hdl, &pipe_match_spec,
                                             &pipe_action_spec, &act_fn_hdl,
                                             read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  // some sanity checking on the returned spec
  // assert(pipe_match_spec.num_valid_match_bits == 9);
  // assert(pipe_match_spec.num_match_bytes == 2);

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    bf_sys_dbgchk(0);
    return BF_UNEXPECTED;
  }

  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
  case 536870912:
    action_spec->name = p4_pd_fsmmf_set_port_metadata;
    unbuild_action_spec_set_port_metadata(pipe_action_data_spec,
                                  res_spec,
                                  resource_cnt,
                                  &action_spec->u.p4_pd_fsmmf_set_port_metadata);
    break;
  default:
    bf_sys_dbgchk(NULL);
    status = BF_UNEXPECTED;
    break;
  }

  bool is_default_entry = (pipe_match_spec.match_value_bits == NULL && 2 > 0);
  if(!is_default_entry)
    unbuild_key_IngressParser__PORT_METADATA(&pipe_match_spec, match_spec);


  (void)action_spec;
  if (res_spec) {
    bf_sys_free(res_spec);
  }
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_first_entry_handle
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t *entry_handle
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_first_entry_handle(sess_hdl, 16777223, pipe_mgr_dev_tgt,
					 entry_handle);  
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_next_entry_handles
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t entry_handle,
  int n, p4_pd_entry_hdl_t *next_entry_handles
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_next_entry_handles(sess_hdl, 16777223, pipe_mgr_dev_tgt, entry_handle,
					 n, next_entry_handles);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  (void)sess_hdl;

  p4_pd_act_hdl_t act_fn_hdl;

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_id;
  pipe_mgr_dev_tgt.dev_pipe_id = BF_DEV_PIPE_ALL;

  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6] = {0};
  uint8_t pipe_match_mask_bits[6] = {0};
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  pipe_match_spec.num_match_bytes = 6;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;

  pipe_action_spec_t pipe_action_spec = {0};
  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  p4_pd_status_t status = pipe_mgr_get_entry(sess_hdl, 16777223, pipe_mgr_dev_tgt,
                                             entry_hdl, &pipe_match_spec,
                                             &pipe_action_spec, &act_fn_hdl,
                                             read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  // some sanity checking on the returned spec
  // assert(pipe_match_spec.num_valid_match_bits == 48);
  // assert(pipe_match_spec.num_match_bytes == 6);

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    bf_sys_dbgchk(0);
    return BF_UNEXPECTED;
  }

  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
  case 536870916:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiSetEgress;
    unbuild_action_spec_Ingress_t_igr_aiSetEgress(pipe_action_data_spec,
                                  res_spec,
                                  resource_cnt,
                                  &action_spec->u.p4_pd_fsmmf_Ingress_t_igr_aiSetEgress);
    break;
  case 536870917:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiNoop;
    break;
  default:
    bf_sys_dbgchk(NULL);
    status = BF_UNEXPECTED;
    break;
  }

  bool is_default_entry = (pipe_match_spec.match_value_bits == NULL && 6 > 0);
  if(!is_default_entry)
    unbuild_key_Ingress_t_igr_tiForward(&pipe_match_spec, match_spec);


  (void)action_spec;
  if (res_spec) {
    bf_sys_free(res_spec);
  }
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_first_entry_handle
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t *entry_handle
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_first_entry_handle(sess_hdl, 16777232, pipe_mgr_dev_tgt,
					 entry_handle);  
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_next_entry_handles
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t entry_handle,
  int n, p4_pd_entry_hdl_t *next_entry_handles
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_next_entry_handles(sess_hdl, 16777232, pipe_mgr_dev_tgt, entry_handle,
					 n, next_entry_handles);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  (void)sess_hdl;

  p4_pd_act_hdl_t act_fn_hdl;

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_id;
  pipe_mgr_dev_tgt.dev_pipe_id = BF_DEV_PIPE_ALL;

  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4] = {0};
  uint8_t pipe_match_mask_bits[4] = {0};
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;

  pipe_action_spec_t pipe_action_spec = {0};
  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  p4_pd_status_t status = pipe_mgr_get_entry(sess_hdl, 16777232, pipe_mgr_dev_tgt,
                                             entry_hdl, &pipe_match_spec,
                                             &pipe_action_spec, &act_fn_hdl,
                                             read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  // some sanity checking on the returned spec
  // assert(pipe_match_spec.num_valid_match_bits == 32);
  // assert(pipe_match_spec.num_match_bytes == 4);

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    bf_sys_dbgchk(0);
    return BF_UNEXPECTED;
  }

  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
  case 536870926:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiRate;
    unbuild_action_spec_Ingress_t_igr_aiRate(pipe_action_data_spec,
                                  res_spec,
                                  resource_cnt,
                                  &action_spec->u.p4_pd_fsmmf_Ingress_t_igr_aiRate);
    break;
  default:
    bf_sys_dbgchk(NULL);
    status = BF_UNEXPECTED;
    break;
  }

  bool is_default_entry = (pipe_match_spec.match_value_bits == NULL && 4 > 0);
  if(!is_default_entry)
    unbuild_key_Ingress_t_igr_tiRate(&pipe_match_spec, match_spec);


  (void)action_spec;
  if (res_spec) {
    bf_sys_free(res_spec);
  }
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_first_entry_handle
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t *entry_handle
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_first_entry_handle(sess_hdl, 16777239, pipe_mgr_dev_tgt,
					 entry_handle);  
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_next_entry_handles
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t entry_handle,
  int n, p4_pd_entry_hdl_t *next_entry_handles
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_next_entry_handles(sess_hdl, 16777239, pipe_mgr_dev_tgt, entry_handle,
					 n, next_entry_handles);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  (void)sess_hdl;

  p4_pd_act_hdl_t act_fn_hdl;

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_id;
  pipe_mgr_dev_tgt.dev_pipe_id = BF_DEV_PIPE_ALL;

  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6] = {0};
  uint8_t pipe_match_mask_bits[6] = {0};
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  pipe_match_spec.num_match_bytes = 6;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;

  pipe_action_spec_t pipe_action_spec = {0};
  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  p4_pd_status_t status = pipe_mgr_get_entry(sess_hdl, 16777239, pipe_mgr_dev_tgt,
                                             entry_hdl, &pipe_match_spec,
                                             &pipe_action_spec, &act_fn_hdl,
                                             read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  // some sanity checking on the returned spec
  // assert(pipe_match_spec.num_valid_match_bits == 48);
  // assert(pipe_match_spec.num_match_bytes == 6);

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    bf_sys_dbgchk(0);
    return BF_UNEXPECTED;
  }

  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
  case 536870928:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate;
    unbuild_action_spec_Ingress_t_igr_aiCalc_dt_x_rate(pipe_action_data_spec,
                                  res_spec,
                                  resource_cnt,
                                  &action_spec->u.p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate);
    break;
  default:
    bf_sys_dbgchk(NULL);
    status = BF_UNEXPECTED;
    break;
  }

  bool is_default_entry = (pipe_match_spec.match_value_bits == NULL && 6 > 0);
  if(!is_default_entry)
    unbuild_key_Ingress_t_igr_tiCalc_dt_x_rate(&pipe_match_spec, match_spec);


  (void)action_spec;
  if (res_spec) {
    bf_sys_free(res_spec);
  }
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_first_entry_handle
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t *entry_handle
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_first_entry_handle(sess_hdl, 16777247, pipe_mgr_dev_tgt,
					 entry_handle);  
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_next_entry_handles
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t entry_handle,
  int n, p4_pd_entry_hdl_t *next_entry_handles
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_next_entry_handles(sess_hdl, 16777247, pipe_mgr_dev_tgt, entry_handle,
					 n, next_entry_handles);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * match_spec,
 int *priority,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  (void)sess_hdl;

  p4_pd_act_hdl_t act_fn_hdl;

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_id;
  pipe_mgr_dev_tgt.dev_pipe_id = BF_DEV_PIPE_ALL;

  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4] = {0};
  uint8_t pipe_match_mask_bits[4] = {0};
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;

  pipe_action_spec_t pipe_action_spec = {0};
  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  p4_pd_status_t status = pipe_mgr_get_entry(sess_hdl, 16777247, pipe_mgr_dev_tgt,
                                             entry_hdl, &pipe_match_spec,
                                             &pipe_action_spec, &act_fn_hdl,
                                             read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  // some sanity checking on the returned spec
  // assert(pipe_match_spec.num_valid_match_bits == 32);
  // assert(pipe_match_spec.num_match_bytes == 4);

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    bf_sys_dbgchk(0);
    return BF_UNEXPECTED;
  }

  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
  case 536870936:
    action_spec->name = p4_pd_fsmmf_NoAction;
    break;
  case 536870934:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiRC_neg;
    break;
  case 536870935:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiRC_pos;
    break;
  default:
    bf_sys_dbgchk(NULL);
    status = BF_UNEXPECTED;
    break;
  }

  bool is_default_entry = (pipe_match_spec.match_value_bits == NULL && 4 > 0);
  if(!is_default_entry)
    unbuild_key_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  *priority = pipe_match_spec.priority;
  if(!is_default_entry)
    unbuild_mask_Ingress_t_igr_tiRC_nag(&pipe_match_spec, match_spec);

  (void)action_spec;
  if (res_spec) {
    bf_sys_free(res_spec);
  }
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_first_entry_handle
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t *entry_handle
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_first_entry_handle(sess_hdl, 16777252, pipe_mgr_dev_tgt,
					 entry_handle);  
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_next_entry_handles
(
  p4_pd_sess_hdl_t sess_hdl, p4_pd_dev_target_t dev_tgt, p4_pd_entry_hdl_t entry_handle,
  int n, p4_pd_entry_hdl_t *next_entry_handles
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_get_next_entry_handles(sess_hdl, 16777252, pipe_mgr_dev_tgt, entry_handle,
					 n, next_entry_handles);
}

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * match_spec,
 int *priority,
 p4_pd_fsmmf_action_specs_t * const action_spec
)
{
  (void)sess_hdl;

  p4_pd_act_hdl_t act_fn_hdl;

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_id;
  pipe_mgr_dev_tgt.dev_pipe_id = BF_DEV_PIPE_ALL;

  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[4] = {0};
  uint8_t pipe_match_mask_bits[4] = {0};
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  pipe_match_spec.num_match_bytes = 4;
  pipe_match_spec.num_valid_match_bits = 32;
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;

  pipe_action_spec_t pipe_action_spec = {0};
  uint8_t pipe_action_data_bits[sizeof(p4_pd_fsmmf_action_specs_t)];
  if (sizeof(p4_pd_fsmmf_action_specs_t)) {
      memset(pipe_action_data_bits, 0, sizeof(p4_pd_fsmmf_action_specs_t));
  }
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->num_action_data_bytes = sizeof(p4_pd_fsmmf_action_specs_t);
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;

  p4_pd_status_t status = pipe_mgr_get_entry(sess_hdl, 16777252, pipe_mgr_dev_tgt,
                                             entry_hdl, &pipe_match_spec,
                                             &pipe_action_spec, &act_fn_hdl,
                                             read_from_hw, PIPE_RES_GET_FLAG_ENTRY, NULL);
  if (status) return status;

  // some sanity checking on the returned spec
  // assert(pipe_match_spec.num_valid_match_bits == 32);
  // assert(pipe_match_spec.num_match_bytes == 4);

  if (pipe_action_spec.pipe_action_datatype_bmap != PIPE_ACTION_DATA_TYPE) {
    bf_sys_dbgchk(0);
    return BF_UNEXPECTED;
  }

  pd_res_spec_t *res_spec = NULL;
  int resource_cnt = 0;
  build_pd_res_spec(&pipe_action_spec, &res_spec, &resource_cnt);

  switch(act_fn_hdl) {
  case 536870944:
    action_spec->name = p4_pd_fsmmf_NoAction;
    break;
  case 536870942:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg;
    break;
  case 536870943:
    action_spec->name = p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos;
    break;
  default:
    bf_sys_dbgchk(NULL);
    status = BF_UNEXPECTED;
    break;
  }

  bool is_default_entry = (pipe_match_spec.match_value_bits == NULL && 4 > 0);
  if(!is_default_entry)
    unbuild_key_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  *priority = pipe_match_spec.priority;
  if(!is_default_entry)
    unbuild_mask_Ingress_t_igr_tiGapRC_pos(&pipe_match_spec, match_spec);

  (void)action_spec;
  if (res_spec) {
    bf_sys_free(res_spec);
  }
  return status;
}



/* Action name strings; can be indexed by the action name enum. */
const char * p4_pd_fsmmf_action_name_strings[] = {
  "p4_pd_fsmmf_set_port_metadata",
  "p4_pd_fsmmf_Ingress_t_igr_aiSetEgress",
  "p4_pd_fsmmf_Ingress_t_igr_aiNoop",
  "p4_pd_fsmmf_Ingress_t_igr_aiRate",
  "p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate",
  "p4_pd_fsmmf_NoAction",
  "p4_pd_fsmmf_Ingress_t_igr_aiRC_neg",
  "p4_pd_fsmmf_Ingress_t_igr_aiRC_pos",
  "p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg",
  "p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos",
};
const char* p4_pd_fsmmf_action_enum_to_string(p4_pd_fsmmf_action_names_t e) {
  if (e >= p4_pd_fsmmf_action_names_t_invalid) return NULL;
  return p4_pd_fsmmf_action_name_strings[e];
}
p4_pd_fsmmf_action_names_t p4_pd_fsmmf_action_string_to_enum(const char* s) {
  if (!s) return p4_pd_fsmmf_action_names_t_invalid;
  if (0 == strcmp(s, "p4_pd_fsmmf_set_port_metadata")) return p4_pd_fsmmf_set_port_metadata;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiSetEgress")) return p4_pd_fsmmf_Ingress_t_igr_aiSetEgress;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiNoop")) return p4_pd_fsmmf_Ingress_t_igr_aiNoop;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiRate")) return p4_pd_fsmmf_Ingress_t_igr_aiRate;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate")) return p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate;
  if (0 == strcmp(s, "p4_pd_fsmmf_NoAction")) return p4_pd_fsmmf_NoAction;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiRC_neg")) return p4_pd_fsmmf_Ingress_t_igr_aiRC_neg;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiRC_pos")) return p4_pd_fsmmf_Ingress_t_igr_aiRC_pos;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg")) return p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg;
  if (0 == strcmp(s, "p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos")) return p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos;
  return p4_pd_fsmmf_action_names_t_invalid;
}




p4_pd_status_t
p4_pd_fsmmf_set_learning_timeout(p4_pd_sess_hdl_t shdl,
                                    uint8_t          device_id,
                                    uint32_t         usecs) 
{
  return pipe_mgr_flow_lrn_set_timeout(shdl, device_id, usecs);
}

/* COUNTERS */



/* METERS */


/* LPF */
p4_pd_status_t
p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
)
{
  pipe_lpf_spec_t *pipe_lpf_spec;
  pipe_lpf_spec_t pipe_lpf_spec_;
  pipe_lpf_spec = &pipe_lpf_spec_;
  lpf_spec_pd_to_pipe(lpf_spec, pipe_lpf_spec);
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_lpf_ent_set(sess_hdl,
                              pipe_mgr_dev_tgt,
                              83886083,
                              index,
                              pipe_lpf_spec,
                              0);
}

p4_pd_status_t
p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
)
{
    pipe_lpf_spec_t pipe_lpf_spec = {0};
    pipe_status_t ret = PIPE_SUCCESS;
    dev_target_t pipe_mgr_dev_tgt;
    pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
    pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
    ret = pipe_mgr_lpf_read_entry_idx(sess_hdl, pipe_mgr_dev_tgt,
                                      83886083, index,
                                      &pipe_lpf_spec,
                                      false);
    if (ret != PIPE_SUCCESS) {
        return ret;
    }
    lpf_spec_pipe_to_pd(lpf_spec, &pipe_lpf_spec);

    return PIPE_SUCCESS;
}
p4_pd_status_t
p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
)
{
  pipe_lpf_spec_t *pipe_lpf_spec;
  pipe_lpf_spec_t pipe_lpf_spec_;
  pipe_lpf_spec = &pipe_lpf_spec_;
  lpf_spec_pd_to_pipe(lpf_spec, pipe_lpf_spec);
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_lpf_ent_set(sess_hdl,
                              pipe_mgr_dev_tgt,
                              83886081,
                              index,
                              pipe_lpf_spec,
                              0);
}

p4_pd_status_t
p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
)
{
    pipe_lpf_spec_t pipe_lpf_spec = {0};
    pipe_status_t ret = PIPE_SUCCESS;
    dev_target_t pipe_mgr_dev_tgt;
    pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
    pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
    ret = pipe_mgr_lpf_read_entry_idx(sess_hdl, pipe_mgr_dev_tgt,
                                      83886081, index,
                                      &pipe_lpf_spec,
                                      false);
    if (ret != PIPE_SUCCESS) {
        return ret;
    }
    lpf_spec_pipe_to_pd(lpf_spec, &pipe_lpf_spec);

    return PIPE_SUCCESS;
}
p4_pd_status_t
p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
)
{
  pipe_lpf_spec_t *pipe_lpf_spec;
  pipe_lpf_spec_t pipe_lpf_spec_;
  pipe_lpf_spec = &pipe_lpf_spec_;
  lpf_spec_pd_to_pipe(lpf_spec, pipe_lpf_spec);
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_mgr_lpf_ent_set(sess_hdl,
                              pipe_mgr_dev_tgt,
                              83886082,
                              index,
                              pipe_lpf_spec,
                              0);
}

p4_pd_status_t
p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
)
{
    pipe_lpf_spec_t pipe_lpf_spec = {0};
    pipe_status_t ret = PIPE_SUCCESS;
    dev_target_t pipe_mgr_dev_tgt;
    pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
    pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
    ret = pipe_mgr_lpf_read_entry_idx(sess_hdl, pipe_mgr_dev_tgt,
                                      83886082, index,
                                      &pipe_lpf_spec,
                                      false);
    if (ret != PIPE_SUCCESS) {
        return ret;
    }
    lpf_spec_pipe_to_pd(lpf_spec, &pipe_lpf_spec);

    return PIPE_SUCCESS;
}
//
/* WRED */

// REGISTERS

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663297,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663297,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663297, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_riTs_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_riTs_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663297, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663297,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_riTs_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663297,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663297,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663297,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663297, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_riTs_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663300,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663300,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663300, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ridt_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ridt_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663300, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663300,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_ridt_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663300,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663300,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663300,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663300, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_ridt_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663309,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663309,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663309, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_count_til_drop_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_count_til_drop_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663309, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663309,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_count_til_drop_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663309,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663309,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663309,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663309, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_count_til_drop_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663304,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663304,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663304, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_riRC_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_riRC_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663304, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663304,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_riRC_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663304,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663304,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663304,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663304, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_riRC_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663303,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663303,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663303, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ri_dt_x_rate_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ri_dt_x_rate_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663303, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663303,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_ri_dt_x_rate_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663303,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663303,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663303,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663303, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_ri_dt_x_rate_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663307,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663307,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663307, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_bottleneckF_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_bottleneckF_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663307, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663307,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_bottleneckF_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663307,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663307,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663307,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663307, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_bottleneckF_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663310,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663310,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663310, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ritestgapRC_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ritestgapRC_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663310, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663310,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_ritestgapRC_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663310,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663310,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663310,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663310, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_ritestgapRC_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663311,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663311,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663311, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ritestburstdrop_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ritestburstdrop_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663311, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663311,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_ritestburstdrop_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663311,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663311,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663311,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663311, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_ritestburstdrop_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663306,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663306,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663306, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ri_gapRC_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ri_gapRC_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663306, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663306,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_ri_gapRC_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663306,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663306,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663306,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663306, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_ri_gapRC_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663305,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663305,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663305, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_bottlenecked_rate_bottleneckedRate_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_bottlenecked_rate_bottleneckedRate_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663305, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663305,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_bottlenecked_rate_bottleneckedRate_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663305,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663305,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663305,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663305, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_bottlenecked_rate_bottleneckedRate_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663301,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663301,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663301, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ri_ts_ms_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ri_ts_ms_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663301, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663301,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_ri_ts_ms_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663301,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663301,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663301,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663301, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_ri_ts_ms_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663298,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663298,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663298, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_riburstStage_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_riburstStage_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663298, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663298,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_riburstStage_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663298,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663298,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663298,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663298, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_riburstStage_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663299,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663299,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663299, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_fCount_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_fCount_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663299, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663299,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_fCount_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663299,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663299,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663299,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663299, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_fCount_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663308,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663308,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663308, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_count_til_ecn_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_count_til_ecn_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663308, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663308,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_count_til_ecn_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663308,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663308,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663308,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663308, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_count_til_ecn_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}
p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  return pipe_stful_database_sync(sess_hdl, pipe_mgr_dev_tgt,
				  100663302,
				  cb_fn, // legit cast
				  cb_cookie);
}
p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663302,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663302, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ri_lograte_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ri_lograte_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663302, index,
					     &stful_spec, 0);
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663302,
                                NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  pipe_stful_mem_spec_t stful_spec;
  register_Ingress_t_igr_ri_lograte_value_pd_to_pipe(register_value, &stful_spec);
  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663302,
                                &stful_spec);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset_range(sess_hdl, pipe_mgr_dev_tgt, 100663302,
                                      index, count, NULL);
}

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663302,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663302, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Ingress_t_igr_ri_lograte_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}




p4_pd_status_t
p4_pd_fsmmf_snapshot_capture_trigger_set(
              pipe_snapshot_hdl_t hdl,
              p4_pd_fsmmf_snapshot_trig_spec_t *trig_spec,
              p4_pd_fsmmf_snapshot_trig_spec_t *trig_mask)
{
  int                                 dir = 0;
  p4_pd_fsmmf_snapshot_trig_spec_t pd_trig_spec;
  p4_pd_fsmmf_snapshot_trig_spec_t pd_trig_mask;

  memcpy(&pd_trig_spec, trig_spec, sizeof(pd_trig_spec));
  memcpy(&pd_trig_mask, trig_mask, sizeof(pd_trig_mask));

  dir = (hdl >> 1) & 0x1;  // dir is bit 1 of hdl
   
  /* Take care of endianness */ 
    switch (dir) 
    {
       case 0:
       {
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig._hash_field_argument0 = htons(pd_trig_spec.u.ig._hash_field_argument0);
          pd_trig_mask.u.ig._hash_field_argument0 = htons(pd_trig_mask.u.ig._hash_field_argument0);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig._tmp2 = htons(pd_trig_spec.u.ig._tmp2);
          pd_trig_mask.u.ig._tmp2 = htons(pd_trig_mask.u.ig._tmp2);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.bottlenecked_rate_cms_output_1 = htonl(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_1);
          pd_trig_mask.u.ig.bottlenecked_rate_cms_output_1 = htonl(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_1);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.bottlenecked_rate_cms_output_2 = htonl(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_2);
          pd_trig_mask.u.ig.bottlenecked_rate_cms_output_2 = htonl(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_2);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.bottlenecked_rate_cms_output_3 = htonl(pd_trig_spec.u.ig.bottlenecked_rate_cms_output_3);
          pd_trig_mask.u.ig.bottlenecked_rate_cms_output_3 = htonl(pd_trig_mask.u.ig.bottlenecked_rate_cms_output_3);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.const_to_phv_32w20000 = htonl(pd_trig_spec.u.ig.const_to_phv_32w20000);
          pd_trig_mask.u.ig.const_to_phv_32w20000 = htonl(pd_trig_mask.u.ig.const_to_phv_32w20000);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.const_to_phv_32w5000000 = htonl(pd_trig_spec.u.ig.const_to_phv_32w5000000);
          pd_trig_mask.u.ig.const_to_phv_32w5000000 = htonl(pd_trig_mask.u.ig.const_to_phv_32w5000000);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_ethernet_ether_type = htons(pd_trig_spec.u.ig.hdr_ethernet_ether_type);
          pd_trig_mask.u.ig.hdr_ethernet_ether_type = htons(pd_trig_mask.u.ig.hdr_ethernet_ether_type);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_ip_dst_addr = htonl(pd_trig_spec.u.ig.hdr_ip_dst_addr);
          pd_trig_mask.u.ig.hdr_ip_dst_addr = htonl(pd_trig_mask.u.ig.hdr_ip_dst_addr);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_ip_frag_offset = htons(pd_trig_spec.u.ig.hdr_ip_frag_offset);
          pd_trig_mask.u.ig.hdr_ip_frag_offset = htons(pd_trig_mask.u.ig.hdr_ip_frag_offset);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_ip_hdr_checksum = htons(pd_trig_spec.u.ig.hdr_ip_hdr_checksum);
          pd_trig_mask.u.ig.hdr_ip_hdr_checksum = htons(pd_trig_mask.u.ig.hdr_ip_hdr_checksum);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_ip_identification = htons(pd_trig_spec.u.ig.hdr_ip_identification);
          pd_trig_mask.u.ig.hdr_ip_identification = htons(pd_trig_mask.u.ig.hdr_ip_identification);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_ip_src_addr = htonl(pd_trig_spec.u.ig.hdr_ip_src_addr);
          pd_trig_mask.u.ig.hdr_ip_src_addr = htonl(pd_trig_mask.u.ig.hdr_ip_src_addr);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_ip_total_len = htons(pd_trig_spec.u.ig.hdr_ip_total_len);
          pd_trig_mask.u.ig.hdr_ip_total_len = htons(pd_trig_mask.u.ig.hdr_ip_total_len);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_tcp_ack_no = htonl(pd_trig_spec.u.ig.hdr_tcp_ack_no);
          pd_trig_mask.u.ig.hdr_tcp_ack_no = htonl(pd_trig_mask.u.ig.hdr_tcp_ack_no);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_tcp_checksum = htons(pd_trig_spec.u.ig.hdr_tcp_checksum);
          pd_trig_mask.u.ig.hdr_tcp_checksum = htons(pd_trig_mask.u.ig.hdr_tcp_checksum);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_tcp_dst_port = htons(pd_trig_spec.u.ig.hdr_tcp_dst_port);
          pd_trig_mask.u.ig.hdr_tcp_dst_port = htons(pd_trig_mask.u.ig.hdr_tcp_dst_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_tcp_seq_no = htonl(pd_trig_spec.u.ig.hdr_tcp_seq_no);
          pd_trig_mask.u.ig.hdr_tcp_seq_no = htonl(pd_trig_mask.u.ig.hdr_tcp_seq_no);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_tcp_src_port = htons(pd_trig_spec.u.ig.hdr_tcp_src_port);
          pd_trig_mask.u.ig.hdr_tcp_src_port = htons(pd_trig_mask.u.ig.hdr_tcp_src_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_tcp_urgent_ptr = htons(pd_trig_spec.u.ig.hdr_tcp_urgent_ptr);
          pd_trig_mask.u.ig.hdr_tcp_urgent_ptr = htons(pd_trig_mask.u.ig.hdr_tcp_urgent_ptr);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_tcp_window = htons(pd_trig_spec.u.ig.hdr_tcp_window);
          pd_trig_mask.u.ig.hdr_tcp_window = htons(pd_trig_mask.u.ig.hdr_tcp_window);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_udp_checksum = htons(pd_trig_spec.u.ig.hdr_udp_checksum);
          pd_trig_mask.u.ig.hdr_udp_checksum = htons(pd_trig_mask.u.ig.hdr_udp_checksum);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_udp_dst_port = htons(pd_trig_spec.u.ig.hdr_udp_dst_port);
          pd_trig_mask.u.ig.hdr_udp_dst_port = htons(pd_trig_mask.u.ig.hdr_udp_dst_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_udp_hdr_lenght = htons(pd_trig_spec.u.ig.hdr_udp_hdr_lenght);
          pd_trig_mask.u.ig.hdr_udp_hdr_lenght = htons(pd_trig_mask.u.ig.hdr_udp_hdr_lenght);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.hdr_udp_src_port = htons(pd_trig_spec.u.ig.hdr_udp_src_port);
          pd_trig_mask.u.ig.hdr_udp_src_port = htons(pd_trig_mask.u.ig.hdr_udp_src_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.ig_intr_md_for_tm_ucast_egress_port = htons(pd_trig_spec.u.ig.ig_intr_md_for_tm_ucast_egress_port);
          pd_trig_mask.u.ig.ig_intr_md_for_tm_ucast_egress_port = htons(pd_trig_mask.u.ig.ig_intr_md_for_tm_ucast_egress_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.md_RC = htonl(pd_trig_spec.u.ig.md_RC);
          pd_trig_mask.u.ig.md_RC = htonl(pd_trig_mask.u.ig.md_RC);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.md_dport = htons(pd_trig_spec.u.ig.md_dport);
          pd_trig_mask.u.ig.md_dport = htons(pd_trig_mask.u.ig.md_dport);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.md_fid = htons(pd_trig_spec.u.ig.md_fid);
          pd_trig_mask.u.ig.md_fid = htons(pd_trig_mask.u.ig.md_fid);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.md_measured_rate = htonl(pd_trig_spec.u.ig.md_measured_rate);
          pd_trig_mask.u.ig.md_measured_rate = htonl(pd_trig_mask.u.ig.md_measured_rate);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.md_pktlen = htonl(pd_trig_spec.u.ig.md_pktlen);
          pd_trig_mask.u.ig.md_pktlen = htonl(pd_trig_mask.u.ig.md_pktlen);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.md_sport = htons(pd_trig_spec.u.ig.md_sport);
          pd_trig_mask.u.ig.md_sport = htons(pd_trig_mask.u.ig.md_sport);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_RC_minus_threshold = htonl(pd_trig_spec.u.ig.t_igr_RC_minus_threshold);
          pd_trig_mask.u.ig.t_igr_RC_minus_threshold = htonl(pd_trig_mask.u.ig.t_igr_RC_minus_threshold);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_burst = htonl(pd_trig_spec.u.ig.t_igr_burst);
          pd_trig_mask.u.ig.t_igr_burst = htonl(pd_trig_mask.u.ig.t_igr_burst);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_dt = htonl(pd_trig_spec.u.ig.t_igr_dt);
          pd_trig_mask.u.ig.t_igr_dt = htonl(pd_trig_mask.u.ig.t_igr_dt);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_dt_ms = htonl(pd_trig_spec.u.ig.t_igr_dt_ms);
          pd_trig_mask.u.ig.t_igr_dt_ms = htonl(pd_trig_mask.u.ig.t_igr_dt_ms);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_dt_x_rate_B = htonl(pd_trig_spec.u.ig.t_igr_dt_x_rate_B);
          pd_trig_mask.u.ig.t_igr_dt_x_rate_B = htonl(pd_trig_mask.u.ig.t_igr_dt_x_rate_B);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_gapRC = htonl(pd_trig_spec.u.ig.t_igr_gapRC);
          pd_trig_mask.u.ig.t_igr_gapRC = htonl(pd_trig_mask.u.ig.t_igr_gapRC);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_log_dt = htons(pd_trig_spec.u.ig.t_igr_log_dt);
          pd_trig_mask.u.ig.t_igr_log_dt = htons(pd_trig_mask.u.ig.t_igr_log_dt);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_pktlen_minus_dt_x_rate = htonl(pd_trig_spec.u.ig.t_igr_pktlen_minus_dt_x_rate);
          pd_trig_mask.u.ig.t_igr_pktlen_minus_dt_x_rate = htonl(pd_trig_mask.u.ig.t_igr_pktlen_minus_dt_x_rate);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_rate = htonl(pd_trig_spec.u.ig.t_igr_rate);
          pd_trig_mask.u.ig.t_igr_rate = htonl(pd_trig_mask.u.ig.t_igr_rate);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_table_key = htonl(pd_trig_spec.u.ig.t_igr_table_key);
          pd_trig_mask.u.ig.t_igr_table_key = htonl(pd_trig_mask.u.ig.t_igr_table_key);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_ts = htonl(pd_trig_spec.u.ig.t_igr_ts);
          pd_trig_mask.u.ig.t_igr_ts = htonl(pd_trig_mask.u.ig.t_igr_ts);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.ig.t_igr_ts_ms = htonl(pd_trig_spec.u.ig.t_igr_ts_ms);
          pd_trig_mask.u.ig.t_igr_ts_ms = htonl(pd_trig_mask.u.ig.t_igr_ts_ms);
#endif
         break;
       
       }
       case 1:
       {
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.eg_intr_md_egress_port = htons(pd_trig_spec.u.eg.eg_intr_md_egress_port);
          pd_trig_mask.u.eg.eg_intr_md_egress_port = htons(pd_trig_mask.u.eg.eg_intr_md_egress_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_ethernet_ether_type = htons(pd_trig_spec.u.eg.hdr_ethernet_ether_type);
          pd_trig_mask.u.eg.hdr_ethernet_ether_type = htons(pd_trig_mask.u.eg.hdr_ethernet_ether_type);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_ip_dst_addr = htonl(pd_trig_spec.u.eg.hdr_ip_dst_addr);
          pd_trig_mask.u.eg.hdr_ip_dst_addr = htonl(pd_trig_mask.u.eg.hdr_ip_dst_addr);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_ip_frag_offset = htons(pd_trig_spec.u.eg.hdr_ip_frag_offset);
          pd_trig_mask.u.eg.hdr_ip_frag_offset = htons(pd_trig_mask.u.eg.hdr_ip_frag_offset);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_ip_hdr_checksum = htons(pd_trig_spec.u.eg.hdr_ip_hdr_checksum);
          pd_trig_mask.u.eg.hdr_ip_hdr_checksum = htons(pd_trig_mask.u.eg.hdr_ip_hdr_checksum);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_ip_identification = htons(pd_trig_spec.u.eg.hdr_ip_identification);
          pd_trig_mask.u.eg.hdr_ip_identification = htons(pd_trig_mask.u.eg.hdr_ip_identification);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_ip_src_addr = htonl(pd_trig_spec.u.eg.hdr_ip_src_addr);
          pd_trig_mask.u.eg.hdr_ip_src_addr = htonl(pd_trig_mask.u.eg.hdr_ip_src_addr);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_ip_total_len = htons(pd_trig_spec.u.eg.hdr_ip_total_len);
          pd_trig_mask.u.eg.hdr_ip_total_len = htons(pd_trig_mask.u.eg.hdr_ip_total_len);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_tcp_ack_no = htonl(pd_trig_spec.u.eg.hdr_tcp_ack_no);
          pd_trig_mask.u.eg.hdr_tcp_ack_no = htonl(pd_trig_mask.u.eg.hdr_tcp_ack_no);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_tcp_checksum = htons(pd_trig_spec.u.eg.hdr_tcp_checksum);
          pd_trig_mask.u.eg.hdr_tcp_checksum = htons(pd_trig_mask.u.eg.hdr_tcp_checksum);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_tcp_dst_port = htons(pd_trig_spec.u.eg.hdr_tcp_dst_port);
          pd_trig_mask.u.eg.hdr_tcp_dst_port = htons(pd_trig_mask.u.eg.hdr_tcp_dst_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_tcp_seq_no = htonl(pd_trig_spec.u.eg.hdr_tcp_seq_no);
          pd_trig_mask.u.eg.hdr_tcp_seq_no = htonl(pd_trig_mask.u.eg.hdr_tcp_seq_no);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_tcp_src_port = htons(pd_trig_spec.u.eg.hdr_tcp_src_port);
          pd_trig_mask.u.eg.hdr_tcp_src_port = htons(pd_trig_mask.u.eg.hdr_tcp_src_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_tcp_urgent_ptr = htons(pd_trig_spec.u.eg.hdr_tcp_urgent_ptr);
          pd_trig_mask.u.eg.hdr_tcp_urgent_ptr = htons(pd_trig_mask.u.eg.hdr_tcp_urgent_ptr);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_tcp_window = htons(pd_trig_spec.u.eg.hdr_tcp_window);
          pd_trig_mask.u.eg.hdr_tcp_window = htons(pd_trig_mask.u.eg.hdr_tcp_window);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_udp_checksum = htons(pd_trig_spec.u.eg.hdr_udp_checksum);
          pd_trig_mask.u.eg.hdr_udp_checksum = htons(pd_trig_mask.u.eg.hdr_udp_checksum);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_udp_dst_port = htons(pd_trig_spec.u.eg.hdr_udp_dst_port);
          pd_trig_mask.u.eg.hdr_udp_dst_port = htons(pd_trig_mask.u.eg.hdr_udp_dst_port);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_udp_hdr_lenght = htons(pd_trig_spec.u.eg.hdr_udp_hdr_lenght);
          pd_trig_mask.u.eg.hdr_udp_hdr_lenght = htons(pd_trig_mask.u.eg.hdr_udp_hdr_lenght);
#endif
#ifdef LITTLE_ENDIAN_CALLER
          pd_trig_spec.u.eg.hdr_udp_src_port = htons(pd_trig_spec.u.eg.hdr_udp_src_port);
          pd_trig_mask.u.eg.hdr_udp_src_port = htons(pd_trig_mask.u.eg.hdr_udp_src_port);
#endif
         break;
       
       }
       default:  
       {
         break;
       }
  }  

  return bf_snapshot_capture_trigger_set(hdl, (void*)&pd_trig_spec, 
                                           (void*)&pd_trig_mask);
}

p4_pd_status_t
p4_pd_fsmmf_snapshot_capture_data_get(
              pipe_snapshot_hdl_t hdl,
              bf_dev_pipe_t dev_pipe_id,
              p4_pd_fsmmf_snapshot_capture_arr_t *capture_arr,
              bf_snapshot_capture_ctrl_info_arr_t *capture_ctrl_arr,
              int *num_captures)
{
  p4_pd_status_t status = 0;
  uint32_t data_size = 0, stage_size = 0;
  int i = 0;
  
  *num_captures = 0;
 
  /* Allocate memory for snapshot capture data */
  bf_snapshot_capture_phv_fields_dict_size(hdl, &data_size, &stage_size);
  uint8_t *capture = bf_sys_calloc(1, data_size);
  if (!capture) {
    return PIPE_NO_SYS_RESOURCES;
  }

  /* Call the Snapshot get API */
  status = bf_snapshot_capture_get(hdl, dev_pipe_id, capture, capture_ctrl_arr, num_captures);

  /* Copy the snapshot data into the user memory. User memory is a PD structure */
  for (i=0; (i < BF_MAX_SNAPSHOT_CAPTURES) && (i < data_size/stage_size) ; i++) { 
    memcpy(&capture_arr->captures[i], capture + i*stage_size, sizeof(p4_pd_fsmmf_snapshot_capture_t));
  }

  bf_sys_free(capture);

  return status;
}

p4_pd_status_t
p4_pd_fsmmf_snapshot_create(
            p4_pd_dev_target_t dev_tgt,
            uint8_t start_stage_id, uint8_t end_stage_id,
            bf_snapshot_dir_t direction,
            pipe_snapshot_hdl_t *hdl)
{
  bf_dev_id_t device_id = dev_tgt.device_id;
  bf_dev_pipe_t dev_pipe_id = (dev_tgt.dev_pipe_id == PD_DEV_PIPE_ALL) ?
                                   DEV_PIPE_ALL : dev_tgt.dev_pipe_id;
  return bf_snapshot_create(device_id,
            dev_pipe_id, start_stage_id, end_stage_id, direction, hdl);
}

p4_pd_status_t
p4_pd_fsmmf_snapshot_delete(
            pipe_snapshot_hdl_t hdl)
{
  return bf_snapshot_delete(hdl); 
}




static void prepend_to_bytestream(uint8_t **p, uint32_t *bit_pos, uint8_t *val, uint32_t bit_width) {
  uint8_t tmp;
  uint8_t *val_p = (val + (bit_width + 7) / 8 - 1);
  uint32_t val_bit_pos = 0;
  while (bit_width) {
    if (*bit_pos != 0) {
      tmp = *val_p << *bit_pos;
      **p |= tmp;
      val_bit_pos = 8 - *bit_pos;
      if (bit_width >= val_bit_pos) {
        (*p)--;
        *bit_pos = 0;
        bit_width -= val_bit_pos;
      } else {
        *bit_pos += bit_width;
        bit_width = 0;
      }
    } else if (val_bit_pos != 0) {
      tmp = *val_p >> val_bit_pos;
      **p |= tmp;
      if (bit_width >= (8 - val_bit_pos)) {
        val_p--;
        *bit_pos = 8 - val_bit_pos;
        bit_width -= (8 - val_bit_pos);
      } else {
        *bit_pos = bit_width;
        bit_width = 0;
      }
      val_bit_pos = 0;
    } else {
      **p = *val_p;
      if (bit_width >= 8) {
        (*p)--;
        val_p--;
        bit_width -= 8;
      } else {
        *bit_pos = bit_width;
        bit_width = 0;
      }
    }
  }
  return;
}


p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648132;
  }
  return pipe_mgr_hash_calc_input_set(sess_hdl, dev_id, 570425348, field_list_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t *input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425348, &field_list_hdl);
  if (553648132 == field_list_hdl) {
    *input = P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t algo
)
{
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_ALGORITHM_CRC_32 == algo) {
    algorithm_hdl = 587202561;
  }
  return pipe_mgr_hash_calc_algorithm_set(sess_hdl, dev_id, 570425348,
          algorithm_hdl, NULL, 0);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t *algo
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;

  status = pipe_mgr_hash_calc_algorithm_get(sess_hdl, dev_id, 570425348,
          &algorithm_hdl, NULL, NULL);
  if (587202561 == algorithm_hdl) {
    *algo = P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_ALGORITHM_CRC_32;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
)
{
  return pipe_mgr_hash_calc_seed_set(sess_hdl, dev_id, 570425348, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
)
{
  return pipe_mgr_hash_calc_seed_get(sess_hdl, dev_id, 570425348, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648132;
  }

  pipe_hash_calc_input_field_attribute_t *pipe_attrs = NULL;
  if (attr_count) {
    pipe_attrs = bf_sys_calloc(attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    for (uint32_t i = 0; i < attr_count; i++) {
      pipe_attrs[i].slice_start_bit = 0;
      pipe_attrs[i].slice_length = 0;
      pipe_attrs[i].order = array_of_attrs[i].input_field.id + 1;
      pipe_attrs[i].input_field = array_of_attrs[i].input_field.id;
      pipe_attrs[i].type = array_of_attrs[i].type;
      pipe_attrs[i].value.val = array_of_attrs[i].value.val;
    }
  }

  status = pipe_mgr_hash_calc_input_field_attribute_set(
      sess_hdl, dev_id, 570425348, field_list_hdl, attr_count, pipe_attrs);

  if (pipe_attrs) {
    bf_sys_free(pipe_attrs);
  }
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t *attr_count
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425348, &field_list_hdl);

  if (553648132 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  *attr_count = 0;
  return pipe_mgr_hash_calc_input_field_attribute_count_get(
      sess_hdl, dev_id, 570425348, field_list_hdl, attr_count);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;
  int i = 0, len = 0;
  *num_attr_filled = 0;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425348, &field_list_hdl);

  if (553648132 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  if (max_attr_count) {
    pipe_hash_calc_input_field_attribute_t *pipe_attrs =
        bf_sys_calloc(max_attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    status = pipe_mgr_hash_calc_input_field_attribute_get(
        sess_hdl, dev_id, 570425348, field_list_hdl, max_attr_count, pipe_attrs, num_attr_filled);
    if (status != PIPE_SUCCESS) {
      bf_sys_free(pipe_attrs);
      return status;
    }

    for (uint32_t i = 0; i < *num_attr_filled; i++) {
      array_of_attrs[i].input_field.id = pipe_attrs[i].input_field;
      array_of_attrs[i].type = pipe_attrs[i].type;
      array_of_attrs[i].value.val = pipe_attrs[i].value.val;
    }
    bf_sys_free(pipe_attrs);
  }

  return BF_SUCCESS;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
)
{
  bf_status_t status = BF_SUCCESS;
  uint8_t *stream = NULL, *p = NULL, *attr = NULL;
  uint32_t stream_len = 0, bit_pos = 0, attr_be = 0;
  int i = 0;

  for (i = 0; i < attr_count; i++) {
    stream_len += attr_sizes[i];
  }
  stream_len = (stream_len + 7) / 8;
  stream = bf_sys_calloc(stream_len, sizeof(uint8_t));
  p = stream + stream_len - 1;

  for (i = attr_count - 1; i >= 0; i--) {
    if (attr_sizes[i] <= 32) {
      /* Convert val to big endian bytestream */
      attr_be = htonl(array_of_attrs[i].value.val);
      attr = (uint8_t *)(&attr_be);
      attr += (4 - (attr_sizes[i] + 7) / 8);
    } else {
      attr = array_of_attrs[i].value.stream;
    }
    prepend_to_bytestream(&p, &bit_pos, attr, attr_sizes[i]);
  }

  status = pipe_mgr_hash_calc_calculate_hash_value(sess_hdl, dev_id, 570425348, stream, stream_len, hash, hash_len);
  bf_sys_free(stream);
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648133;
  }
  return pipe_mgr_hash_calc_input_set(sess_hdl, dev_id, 570425349, field_list_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t *input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425349, &field_list_hdl);
  if (553648133 == field_list_hdl) {
    *input = P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_INPUT__FIELD_LIST_1;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t algo
)
{
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_ALGORITHM_CRC_32 == algo) {
    algorithm_hdl = 587202561;
  }
  return pipe_mgr_hash_calc_algorithm_set(sess_hdl, dev_id, 570425349,
          algorithm_hdl, NULL, 0);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t *algo
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;

  status = pipe_mgr_hash_calc_algorithm_get(sess_hdl, dev_id, 570425349,
          &algorithm_hdl, NULL, NULL);
  if (587202561 == algorithm_hdl) {
    *algo = P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_ALGORITHM_CRC_32;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
)
{
  return pipe_mgr_hash_calc_seed_set(sess_hdl, dev_id, 570425349, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
)
{
  return pipe_mgr_hash_calc_seed_get(sess_hdl, dev_id, 570425349, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *array_of_attrs
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648133;
  }

  pipe_hash_calc_input_field_attribute_t *pipe_attrs = NULL;
  if (attr_count) {
    pipe_attrs = bf_sys_calloc(attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    for (uint32_t i = 0; i < attr_count; i++) {
      pipe_attrs[i].slice_start_bit = 0;
      pipe_attrs[i].slice_length = 0;
      pipe_attrs[i].order = array_of_attrs[i].input_field.id + 1;
      pipe_attrs[i].input_field = array_of_attrs[i].input_field.id;
      pipe_attrs[i].type = array_of_attrs[i].type;
      pipe_attrs[i].value.val = array_of_attrs[i].value.val;
    }
  }

  status = pipe_mgr_hash_calc_input_field_attribute_set(
      sess_hdl, dev_id, 570425349, field_list_hdl, attr_count, pipe_attrs);

  if (pipe_attrs) {
    bf_sys_free(pipe_attrs);
  }
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input,
 uint32_t *attr_count
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425349, &field_list_hdl);

  if (553648133 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  *attr_count = 0;
  return pipe_mgr_hash_calc_input_field_attribute_count_get(
      sess_hdl, dev_id, 570425349, field_list_hdl, attr_count);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;
  int i = 0, len = 0;
  *num_attr_filled = 0;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425349, &field_list_hdl);

  if (553648133 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  if (max_attr_count) {
    pipe_hash_calc_input_field_attribute_t *pipe_attrs =
        bf_sys_calloc(max_attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    status = pipe_mgr_hash_calc_input_field_attribute_get(
        sess_hdl, dev_id, 570425349, field_list_hdl, max_attr_count, pipe_attrs, num_attr_filled);
    if (status != PIPE_SUCCESS) {
      bf_sys_free(pipe_attrs);
      return status;
    }

    for (uint32_t i = 0; i < *num_attr_filled; i++) {
      array_of_attrs[i].input_field.id = pipe_attrs[i].input_field;
      array_of_attrs[i].type = pipe_attrs[i].type;
      array_of_attrs[i].value.val = pipe_attrs[i].value.val;
    }
    bf_sys_free(pipe_attrs);
  }

  return BF_SUCCESS;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
)
{
  bf_status_t status = BF_SUCCESS;
  uint8_t *stream = NULL, *p = NULL, *attr = NULL;
  uint32_t stream_len = 0, bit_pos = 0, attr_be = 0;
  int i = 0;

  for (i = 0; i < attr_count; i++) {
    stream_len += attr_sizes[i];
  }
  stream_len = (stream_len + 7) / 8;
  stream = bf_sys_calloc(stream_len, sizeof(uint8_t));
  p = stream + stream_len - 1;

  for (i = attr_count - 1; i >= 0; i--) {
    if (attr_sizes[i] <= 32) {
      /* Convert val to big endian bytestream */
      attr_be = htonl(array_of_attrs[i].value.val);
      attr = (uint8_t *)(&attr_be);
      attr += (4 - (attr_sizes[i] + 7) / 8);
    } else {
      attr = array_of_attrs[i].value.stream;
    }
    prepend_to_bytestream(&p, &bit_pos, attr, attr_sizes[i]);
  }

  status = pipe_mgr_hash_calc_calculate_hash_value(sess_hdl, dev_id, 570425349, stream, stream_len, hash, hash_len);
  bf_sys_free(stream);
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648129;
  }
  return pipe_mgr_hash_calc_input_set(sess_hdl, dev_id, 570425345, field_list_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t *input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425345, &field_list_hdl);
  if (553648129 == field_list_hdl) {
    *input = P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_INPUT__FIELD_LIST_1;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t algo
)
{
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_ALGORITHM_CRC_16 == algo) {
    algorithm_hdl = 587202560;
  }
  return pipe_mgr_hash_calc_algorithm_set(sess_hdl, dev_id, 570425345,
          algorithm_hdl, NULL, 0);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t *algo
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;

  status = pipe_mgr_hash_calc_algorithm_get(sess_hdl, dev_id, 570425345,
          &algorithm_hdl, NULL, NULL);
  if (587202560 == algorithm_hdl) {
    *algo = P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_ALGORITHM_CRC_16;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
)
{
  return pipe_mgr_hash_calc_seed_set(sess_hdl, dev_id, 570425345, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
)
{
  return pipe_mgr_hash_calc_seed_get(sess_hdl, dev_id, 570425345, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *array_of_attrs
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648129;
  }

  pipe_hash_calc_input_field_attribute_t *pipe_attrs = NULL;
  if (attr_count) {
    pipe_attrs = bf_sys_calloc(attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    for (uint32_t i = 0; i < attr_count; i++) {
      pipe_attrs[i].slice_start_bit = 0;
      pipe_attrs[i].slice_length = 0;
      pipe_attrs[i].order = array_of_attrs[i].input_field.id + 1;
      pipe_attrs[i].input_field = array_of_attrs[i].input_field.id;
      pipe_attrs[i].type = array_of_attrs[i].type;
      pipe_attrs[i].value.val = array_of_attrs[i].value.val;
    }
  }

  status = pipe_mgr_hash_calc_input_field_attribute_set(
      sess_hdl, dev_id, 570425345, field_list_hdl, attr_count, pipe_attrs);

  if (pipe_attrs) {
    bf_sys_free(pipe_attrs);
  }
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input,
 uint32_t *attr_count
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425345, &field_list_hdl);

  if (553648129 == field_list_hdl && P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  *attr_count = 0;
  return pipe_mgr_hash_calc_input_field_attribute_count_get(
      sess_hdl, dev_id, 570425345, field_list_hdl, attr_count);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;
  int i = 0, len = 0;
  *num_attr_filled = 0;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425345, &field_list_hdl);

  if (553648129 == field_list_hdl && P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  if (max_attr_count) {
    pipe_hash_calc_input_field_attribute_t *pipe_attrs =
        bf_sys_calloc(max_attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    status = pipe_mgr_hash_calc_input_field_attribute_get(
        sess_hdl, dev_id, 570425345, field_list_hdl, max_attr_count, pipe_attrs, num_attr_filled);
    if (status != PIPE_SUCCESS) {
      bf_sys_free(pipe_attrs);
      return status;
    }

    for (uint32_t i = 0; i < *num_attr_filled; i++) {
      array_of_attrs[i].input_field.id = pipe_attrs[i].input_field;
      array_of_attrs[i].type = pipe_attrs[i].type;
      array_of_attrs[i].value.val = pipe_attrs[i].value.val;
    }
    bf_sys_free(pipe_attrs);
  }

  return BF_SUCCESS;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
)
{
  bf_status_t status = BF_SUCCESS;
  uint8_t *stream = NULL, *p = NULL, *attr = NULL;
  uint32_t stream_len = 0, bit_pos = 0, attr_be = 0;
  int i = 0;

  for (i = 0; i < attr_count; i++) {
    stream_len += attr_sizes[i];
  }
  stream_len = (stream_len + 7) / 8;
  stream = bf_sys_calloc(stream_len, sizeof(uint8_t));
  p = stream + stream_len - 1;

  for (i = attr_count - 1; i >= 0; i--) {
    if (attr_sizes[i] <= 32) {
      /* Convert val to big endian bytestream */
      attr_be = htonl(array_of_attrs[i].value.val);
      attr = (uint8_t *)(&attr_be);
      attr += (4 - (attr_sizes[i] + 7) / 8);
    } else {
      attr = array_of_attrs[i].value.stream;
    }
    prepend_to_bytestream(&p, &bit_pos, attr, attr_sizes[i]);
  }

  status = pipe_mgr_hash_calc_calculate_hash_value(sess_hdl, dev_id, 570425345, stream, stream_len, hash, hash_len);
  bf_sys_free(stream);
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648131;
  }
  return pipe_mgr_hash_calc_input_set(sess_hdl, dev_id, 570425347, field_list_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t *input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425347, &field_list_hdl);
  if (553648131 == field_list_hdl) {
    *input = P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_INPUT__FIELD_LIST_1;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t algo
)
{
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_ALGORITHM_CRC_16 == algo) {
    algorithm_hdl = 587202560;
  }
  return pipe_mgr_hash_calc_algorithm_set(sess_hdl, dev_id, 570425347,
          algorithm_hdl, NULL, 0);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t *algo
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;

  status = pipe_mgr_hash_calc_algorithm_get(sess_hdl, dev_id, 570425347,
          &algorithm_hdl, NULL, NULL);
  if (587202560 == algorithm_hdl) {
    *algo = P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_ALGORITHM_CRC_16;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
)
{
  return pipe_mgr_hash_calc_seed_set(sess_hdl, dev_id, 570425347, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
)
{
  return pipe_mgr_hash_calc_seed_get(sess_hdl, dev_id, 570425347, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *array_of_attrs
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648131;
  }

  pipe_hash_calc_input_field_attribute_t *pipe_attrs = NULL;
  if (attr_count) {
    pipe_attrs = bf_sys_calloc(attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    for (uint32_t i = 0; i < attr_count; i++) {
      pipe_attrs[i].slice_start_bit = 0;
      pipe_attrs[i].slice_length = 0;
      pipe_attrs[i].order = array_of_attrs[i].input_field.id + 1;
      pipe_attrs[i].input_field = array_of_attrs[i].input_field.id;
      pipe_attrs[i].type = array_of_attrs[i].type;
      pipe_attrs[i].value.val = array_of_attrs[i].value.val;
    }
  }

  status = pipe_mgr_hash_calc_input_field_attribute_set(
      sess_hdl, dev_id, 570425347, field_list_hdl, attr_count, pipe_attrs);

  if (pipe_attrs) {
    bf_sys_free(pipe_attrs);
  }
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input,
 uint32_t *attr_count
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425347, &field_list_hdl);

  if (553648131 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  *attr_count = 0;
  return pipe_mgr_hash_calc_input_field_attribute_count_get(
      sess_hdl, dev_id, 570425347, field_list_hdl, attr_count);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;
  int i = 0, len = 0;
  *num_attr_filled = 0;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425347, &field_list_hdl);

  if (553648131 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  if (max_attr_count) {
    pipe_hash_calc_input_field_attribute_t *pipe_attrs =
        bf_sys_calloc(max_attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    status = pipe_mgr_hash_calc_input_field_attribute_get(
        sess_hdl, dev_id, 570425347, field_list_hdl, max_attr_count, pipe_attrs, num_attr_filled);
    if (status != PIPE_SUCCESS) {
      bf_sys_free(pipe_attrs);
      return status;
    }

    for (uint32_t i = 0; i < *num_attr_filled; i++) {
      array_of_attrs[i].input_field.id = pipe_attrs[i].input_field;
      array_of_attrs[i].type = pipe_attrs[i].type;
      array_of_attrs[i].value.val = pipe_attrs[i].value.val;
    }
    bf_sys_free(pipe_attrs);
  }

  return BF_SUCCESS;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
)
{
  bf_status_t status = BF_SUCCESS;
  uint8_t *stream = NULL, *p = NULL, *attr = NULL;
  uint32_t stream_len = 0, bit_pos = 0, attr_be = 0;
  int i = 0;

  for (i = 0; i < attr_count; i++) {
    stream_len += attr_sizes[i];
  }
  stream_len = (stream_len + 7) / 8;
  stream = bf_sys_calloc(stream_len, sizeof(uint8_t));
  p = stream + stream_len - 1;

  for (i = attr_count - 1; i >= 0; i--) {
    if (attr_sizes[i] <= 32) {
      /* Convert val to big endian bytestream */
      attr_be = htonl(array_of_attrs[i].value.val);
      attr = (uint8_t *)(&attr_be);
      attr += (4 - (attr_sizes[i] + 7) / 8);
    } else {
      attr = array_of_attrs[i].value.stream;
    }
    prepend_to_bytestream(&p, &bit_pos, attr, attr_sizes[i]);
  }

  status = pipe_mgr_hash_calc_calculate_hash_value(sess_hdl, dev_id, 570425347, stream, stream_len, hash, hash_len);
  bf_sys_free(stream);
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648134;
  }
  return pipe_mgr_hash_calc_input_set(sess_hdl, dev_id, 570425350, field_list_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t *input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425350, &field_list_hdl);
  if (553648134 == field_list_hdl) {
    *input = P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t algo
)
{
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_ALGORITHM_CRC_32 == algo) {
    algorithm_hdl = 587202561;
  }
  return pipe_mgr_hash_calc_algorithm_set(sess_hdl, dev_id, 570425350,
          algorithm_hdl, NULL, 0);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t *algo
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;

  status = pipe_mgr_hash_calc_algorithm_get(sess_hdl, dev_id, 570425350,
          &algorithm_hdl, NULL, NULL);
  if (587202561 == algorithm_hdl) {
    *algo = P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_ALGORITHM_CRC_32;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
)
{
  return pipe_mgr_hash_calc_seed_set(sess_hdl, dev_id, 570425350, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
)
{
  return pipe_mgr_hash_calc_seed_get(sess_hdl, dev_id, 570425350, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648134;
  }

  pipe_hash_calc_input_field_attribute_t *pipe_attrs = NULL;
  if (attr_count) {
    pipe_attrs = bf_sys_calloc(attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    for (uint32_t i = 0; i < attr_count; i++) {
      pipe_attrs[i].slice_start_bit = 0;
      pipe_attrs[i].slice_length = 0;
      pipe_attrs[i].order = array_of_attrs[i].input_field.id + 1;
      pipe_attrs[i].input_field = array_of_attrs[i].input_field.id;
      pipe_attrs[i].type = array_of_attrs[i].type;
      pipe_attrs[i].value.val = array_of_attrs[i].value.val;
    }
  }

  status = pipe_mgr_hash_calc_input_field_attribute_set(
      sess_hdl, dev_id, 570425350, field_list_hdl, attr_count, pipe_attrs);

  if (pipe_attrs) {
    bf_sys_free(pipe_attrs);
  }
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t *attr_count
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425350, &field_list_hdl);

  if (553648134 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  *attr_count = 0;
  return pipe_mgr_hash_calc_input_field_attribute_count_get(
      sess_hdl, dev_id, 570425350, field_list_hdl, attr_count);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;
  int i = 0, len = 0;
  *num_attr_filled = 0;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425350, &field_list_hdl);

  if (553648134 == field_list_hdl && P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  if (max_attr_count) {
    pipe_hash_calc_input_field_attribute_t *pipe_attrs =
        bf_sys_calloc(max_attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    status = pipe_mgr_hash_calc_input_field_attribute_get(
        sess_hdl, dev_id, 570425350, field_list_hdl, max_attr_count, pipe_attrs, num_attr_filled);
    if (status != PIPE_SUCCESS) {
      bf_sys_free(pipe_attrs);
      return status;
    }

    for (uint32_t i = 0; i < *num_attr_filled; i++) {
      array_of_attrs[i].input_field.id = pipe_attrs[i].input_field;
      array_of_attrs[i].type = pipe_attrs[i].type;
      array_of_attrs[i].value.val = pipe_attrs[i].value.val;
    }
    bf_sys_free(pipe_attrs);
  }

  return BF_SUCCESS;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
)
{
  bf_status_t status = BF_SUCCESS;
  uint8_t *stream = NULL, *p = NULL, *attr = NULL;
  uint32_t stream_len = 0, bit_pos = 0, attr_be = 0;
  int i = 0;

  for (i = 0; i < attr_count; i++) {
    stream_len += attr_sizes[i];
  }
  stream_len = (stream_len + 7) / 8;
  stream = bf_sys_calloc(stream_len, sizeof(uint8_t));
  p = stream + stream_len - 1;

  for (i = attr_count - 1; i >= 0; i--) {
    if (attr_sizes[i] <= 32) {
      /* Convert val to big endian bytestream */
      attr_be = htonl(array_of_attrs[i].value.val);
      attr = (uint8_t *)(&attr_be);
      attr += (4 - (attr_sizes[i] + 7) / 8);
    } else {
      attr = array_of_attrs[i].value.stream;
    }
    prepend_to_bytestream(&p, &bit_pos, attr, attr_sizes[i]);
  }

  status = pipe_mgr_hash_calc_calculate_hash_value(sess_hdl, dev_id, 570425350, stream, stream_len, hash, hash_len);
  bf_sys_free(stream);
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648128;
  }
  return pipe_mgr_hash_calc_input_set(sess_hdl, dev_id, 570425344, field_list_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t *input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425344, &field_list_hdl);
  if (553648128 == field_list_hdl) {
    *input = P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_INPUT__FIELD_LIST_1;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t algo
)
{
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_ALGORITHM_CRC_16 == algo) {
    algorithm_hdl = 587202560;
  }
  return pipe_mgr_hash_calc_algorithm_set(sess_hdl, dev_id, 570425344,
          algorithm_hdl, NULL, 0);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t *algo
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;

  status = pipe_mgr_hash_calc_algorithm_get(sess_hdl, dev_id, 570425344,
          &algorithm_hdl, NULL, NULL);
  if (587202560 == algorithm_hdl) {
    *algo = P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_ALGORITHM_CRC_16;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
)
{
  return pipe_mgr_hash_calc_seed_set(sess_hdl, dev_id, 570425344, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
)
{
  return pipe_mgr_hash_calc_seed_get(sess_hdl, dev_id, 570425344, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *array_of_attrs
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648128;
  }

  pipe_hash_calc_input_field_attribute_t *pipe_attrs = NULL;
  if (attr_count) {
    pipe_attrs = bf_sys_calloc(attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    for (uint32_t i = 0; i < attr_count; i++) {
      pipe_attrs[i].slice_start_bit = 0;
      pipe_attrs[i].slice_length = 0;
      pipe_attrs[i].order = array_of_attrs[i].input_field.id + 1;
      pipe_attrs[i].input_field = array_of_attrs[i].input_field.id;
      pipe_attrs[i].type = array_of_attrs[i].type;
      pipe_attrs[i].value.val = array_of_attrs[i].value.val;
    }
  }

  status = pipe_mgr_hash_calc_input_field_attribute_set(
      sess_hdl, dev_id, 570425344, field_list_hdl, attr_count, pipe_attrs);

  if (pipe_attrs) {
    bf_sys_free(pipe_attrs);
  }
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input,
 uint32_t *attr_count
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425344, &field_list_hdl);

  if (553648128 == field_list_hdl && P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  *attr_count = 0;
  return pipe_mgr_hash_calc_input_field_attribute_count_get(
      sess_hdl, dev_id, 570425344, field_list_hdl, attr_count);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;
  int i = 0, len = 0;
  *num_attr_filled = 0;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425344, &field_list_hdl);

  if (553648128 == field_list_hdl && P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  if (max_attr_count) {
    pipe_hash_calc_input_field_attribute_t *pipe_attrs =
        bf_sys_calloc(max_attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    status = pipe_mgr_hash_calc_input_field_attribute_get(
        sess_hdl, dev_id, 570425344, field_list_hdl, max_attr_count, pipe_attrs, num_attr_filled);
    if (status != PIPE_SUCCESS) {
      bf_sys_free(pipe_attrs);
      return status;
    }

    for (uint32_t i = 0; i < *num_attr_filled; i++) {
      array_of_attrs[i].input_field.id = pipe_attrs[i].input_field;
      array_of_attrs[i].type = pipe_attrs[i].type;
      array_of_attrs[i].value.val = pipe_attrs[i].value.val;
    }
    bf_sys_free(pipe_attrs);
  }

  return BF_SUCCESS;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
)
{
  bf_status_t status = BF_SUCCESS;
  uint8_t *stream = NULL, *p = NULL, *attr = NULL;
  uint32_t stream_len = 0, bit_pos = 0, attr_be = 0;
  int i = 0;

  for (i = 0; i < attr_count; i++) {
    stream_len += attr_sizes[i];
  }
  stream_len = (stream_len + 7) / 8;
  stream = bf_sys_calloc(stream_len, sizeof(uint8_t));
  p = stream + stream_len - 1;

  for (i = attr_count - 1; i >= 0; i--) {
    if (attr_sizes[i] <= 32) {
      /* Convert val to big endian bytestream */
      attr_be = htonl(array_of_attrs[i].value.val);
      attr = (uint8_t *)(&attr_be);
      attr += (4 - (attr_sizes[i] + 7) / 8);
    } else {
      attr = array_of_attrs[i].value.stream;
    }
    prepend_to_bytestream(&p, &bit_pos, attr, attr_sizes[i]);
  }

  status = pipe_mgr_hash_calc_calculate_hash_value(sess_hdl, dev_id, 570425344, stream, stream_len, hash, hash_len);
  bf_sys_free(stream);
  return status;
}


p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648130;
  }
  return pipe_mgr_hash_calc_input_set(sess_hdl, dev_id, 570425346, field_list_hdl);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t *input
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425346, &field_list_hdl);
  if (553648130 == field_list_hdl) {
    *input = P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_INPUT__FIELD_LIST_1;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t algo
)
{
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_ALGORITHM_CRC_16 == algo) {
    algorithm_hdl = 587202560;
  }
  return pipe_mgr_hash_calc_algorithm_set(sess_hdl, dev_id, 570425346,
          algorithm_hdl, NULL, 0);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t *algo
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t algorithm_hdl = 0;

  status = pipe_mgr_hash_calc_algorithm_get(sess_hdl, dev_id, 570425346,
          &algorithm_hdl, NULL, NULL);
  if (587202560 == algorithm_hdl) {
    *algo = P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_ALGORITHM_CRC_16;
    return status;
  }

  return BF_INVALID_ARG;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
)
{
  return pipe_mgr_hash_calc_seed_set(sess_hdl, dev_id, 570425346, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
)
{
  return pipe_mgr_hash_calc_seed_get(sess_hdl, dev_id, 570425346, seed);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *array_of_attrs
)
{
  bf_status_t status = BF_SUCCESS;
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  if (P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_INPUT__FIELD_LIST_1 == input) {
    field_list_hdl = 553648130;
  }

  pipe_hash_calc_input_field_attribute_t *pipe_attrs = NULL;
  if (attr_count) {
    pipe_attrs = bf_sys_calloc(attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    for (uint32_t i = 0; i < attr_count; i++) {
      pipe_attrs[i].slice_start_bit = 0;
      pipe_attrs[i].slice_length = 0;
      pipe_attrs[i].order = array_of_attrs[i].input_field.id + 1;
      pipe_attrs[i].input_field = array_of_attrs[i].input_field.id;
      pipe_attrs[i].type = array_of_attrs[i].type;
      pipe_attrs[i].value.val = array_of_attrs[i].value.val;
    }
  }

  status = pipe_mgr_hash_calc_input_field_attribute_set(
      sess_hdl, dev_id, 570425346, field_list_hdl, attr_count, pipe_attrs);

  if (pipe_attrs) {
    bf_sys_free(pipe_attrs);
  }
  return status;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input,
 uint32_t *attr_count
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425346, &field_list_hdl);

  if (553648130 == field_list_hdl && P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  *attr_count = 0;
  return pipe_mgr_hash_calc_input_field_attribute_count_get(
      sess_hdl, dev_id, 570425346, field_list_hdl, attr_count);
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
)
{
  pipe_sel_tbl_hdl_t field_list_hdl = 0;
  bf_status_t status = BF_SUCCESS;
  int i = 0, len = 0;
  *num_attr_filled = 0;

  status = pipe_mgr_hash_calc_input_get(sess_hdl, dev_id, 570425346, &field_list_hdl);

  if (553648130 == field_list_hdl && P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_INPUT__FIELD_LIST_1 != input) {
    return BF_INVALID_ARG;
  }

  if (max_attr_count) {
    pipe_hash_calc_input_field_attribute_t *pipe_attrs =
        bf_sys_calloc(max_attr_count, sizeof(pipe_hash_calc_input_field_attribute_t));
    status = pipe_mgr_hash_calc_input_field_attribute_get(
        sess_hdl, dev_id, 570425346, field_list_hdl, max_attr_count, pipe_attrs, num_attr_filled);
    if (status != PIPE_SUCCESS) {
      bf_sys_free(pipe_attrs);
      return status;
    }

    for (uint32_t i = 0; i < *num_attr_filled; i++) {
      array_of_attrs[i].input_field.id = pipe_attrs[i].input_field;
      array_of_attrs[i].type = pipe_attrs[i].type;
      array_of_attrs[i].value.val = pipe_attrs[i].value.val;
    }
    bf_sys_free(pipe_attrs);
  }

  return BF_SUCCESS;
}

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
)
{
  bf_status_t status = BF_SUCCESS;
  uint8_t *stream = NULL, *p = NULL, *attr = NULL;
  uint32_t stream_len = 0, bit_pos = 0, attr_be = 0;
  int i = 0;

  for (i = 0; i < attr_count; i++) {
    stream_len += attr_sizes[i];
  }
  stream_len = (stream_len + 7) / 8;
  stream = bf_sys_calloc(stream_len, sizeof(uint8_t));
  p = stream + stream_len - 1;

  for (i = attr_count - 1; i >= 0; i--) {
    if (attr_sizes[i] <= 32) {
      /* Convert val to big endian bytestream */
      attr_be = htonl(array_of_attrs[i].value.val);
      attr = (uint8_t *)(&attr_be);
      attr += (4 - (attr_sizes[i] + 7) / 8);
    } else {
      attr = array_of_attrs[i].value.stream;
    }
    prepend_to_bytestream(&p, &bit_pos, attr, attr_sizes[i]);
  }

  status = pipe_mgr_hash_calc_calculate_hash_value(sess_hdl, dev_id, 570425346, stream, stream_len, hash, hash_len);
  bf_sys_free(stream);
  return status;
}



