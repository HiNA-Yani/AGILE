#ifndef _PD_FSMMF_PD_H
#define _PD_FSMMF_PD_H

#include <stdint.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN_
#define LITTLE_ENDIAN_CALLER 1
#endif

#include <tofino/pdfixed/pd_common.h>
#include <pipe_mgr/pipe_mgr_intf.h>



/* MATCH STRUCTS */

typedef struct p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec {
  uint16_t ig_intr_md_ingress_port;
} p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec {
  uint8_t hdr_ethernet_dst_addr[6];
} p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec {
  uint32_t table_key;
} p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec {
  uint16_t log_dt;
  uint32_t rate;
} p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec {
  uint32_t md_RC;
  uint32_t md_RC_mask;
} p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec {
  uint32_t gapRC;
  uint32_t gapRC_mask;
} p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t;



/* Dynamic Exm Table Key Mask */

/* IngressParser__PORT_METADATA has no dynamic key masks */

/* Ingress_t_igr_tiForward has no dynamic key masks */

/* Ingress_t_igr_tiRate has no dynamic key masks */

/* Ingress_t_igr_tiCalc_dt_x_rate has no dynamic key masks */

/* Ingress_t_igr_tiRC_nag has no dynamic key masks */

/* Ingress_t_igr_tiGapRC_pos has no dynamic key masks */



/* ACTION STRUCTS */

/* Enum of all action names. */
typedef enum p4_pd_fsmmf_action_names {
  p4_pd_fsmmf_set_port_metadata,
  p4_pd_fsmmf_Ingress_t_igr_aiSetEgress,
  p4_pd_fsmmf_Ingress_t_igr_aiNoop,
  p4_pd_fsmmf_Ingress_t_igr_aiRate,
  p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate,
  p4_pd_fsmmf_NoAction,
  p4_pd_fsmmf_Ingress_t_igr_aiRC_neg,
  p4_pd_fsmmf_Ingress_t_igr_aiRC_pos,
  p4_pd_fsmmf_Ingress_t_igr_aiGapRC_neg,
  p4_pd_fsmmf_Ingress_t_igr_aiGapRC_pos,
  p4_pd_fsmmf_action_names_t_invalid
} p4_pd_fsmmf_action_names_t;

const char* p4_pd_fsmmf_action_enum_to_string(p4_pd_fsmmf_action_names_t e);

p4_pd_fsmmf_action_names_t p4_pd_fsmmf_action_string_to_enum(const char* s);

typedef struct p4_pd_fsmmf_set_port_metadata_action_spec {
  uint8_t action_ig_intr_md[8];
} p4_pd_fsmmf_set_port_metadata_action_spec_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec {
  uint16_t action_egr_port;
} p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t;

  /* Ingress_t_igr_aiNoop has no parameters */

typedef struct p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec {
  uint32_t action_Allocate_rate;
} p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec {
  uint32_t action_Calc_dt_x_rate;
  uint32_t action_Calc_dt_x_rate_B;
} p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t;

  /* NoAction has no parameters */

  /* Ingress_t_igr_aiRC_neg has no parameters */

  /* Ingress_t_igr_aiRC_pos has no parameters */

  /* Ingress_t_igr_aiGapRC_neg has no parameters */

  /* Ingress_t_igr_aiGapRC_pos has no parameters */


typedef struct p4_pd_fsmmf_action_specs_t {
  p4_pd_fsmmf_action_names_t name;
  union {
    struct p4_pd_fsmmf_set_port_metadata_action_spec p4_pd_fsmmf_set_port_metadata;
    struct p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec p4_pd_fsmmf_Ingress_t_igr_aiSetEgress;
  /* Ingress_t_igr_aiNoop has no parameters */
    struct p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec p4_pd_fsmmf_Ingress_t_igr_aiRate;
    struct p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate;
  /* NoAction has no parameters */
  /* Ingress_t_igr_aiRC_neg has no parameters */
  /* Ingress_t_igr_aiRC_pos has no parameters */
  /* Ingress_t_igr_aiGapRC_neg has no parameters */
  /* Ingress_t_igr_aiGapRC_pos has no parameters */
  } u;
} p4_pd_fsmmf_action_specs_t;

void p4_pd_fsmmf_init(void);

/* HA TESTING INFRASTRUCTURE */

/* REGISTER VALUES */


/* IDLE TIME CONFIG */


p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);



/* Dynamic Exm Table Key Mask */


/* ADD ENTRIES */

/**
 * @brief p4_pd_fsmmf_IngressParser__PORT_METADATA_table_add_with_set_port_metadata
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_add_with_set_port_metadata
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_neg
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_pos
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_neg
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_pos
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);


/* DELETE ENTRIES */

/**
 * @brief p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
);


/* Get default entry handle */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_fsmmf_action_specs_t * const action_spec
);


/* Clear default entry */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);


/* MODIFY TABLE PROPERTIES */

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);


/* MODIFY ENTRIES */

/**
 * @brief p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 const p4_pd_fsmmf_set_port_metadata_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * const match_spec,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t * const match_spec,
 int priority
);



/* SET DEFAULT_ACTION */

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRate_set_default_action_Ingress_t_igr_aiRate
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_set_default_action_Ingress_t_igr_aiRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_set_default_action_Ingress_t_igr_aiCalc_dt_x_rate
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_set_default_action_Ingress_t_igr_aiCalc_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_neg
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_pos
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_neg
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_neg
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_pos
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_pos
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);



/* INDIRECT ACTION DATA AND MATCH SELECT */






p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);



p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_fsmmf_IngressParser__PORT_METADATA_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_IngressParser__PORT_METADATA_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiForward_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiForward_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRate_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t * match_spec,
 p4_pd_fsmmf_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiRC_nag_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

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
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_fsmmf_Ingress_t_igr_tiGapRC_pos_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

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
);






p4_pd_status_t
p4_pd_fsmmf_set_learning_timeout(p4_pd_sess_hdl_t shdl,
                                    uint8_t          device_id,
                                    uint32_t         usecs);

/* COUNTERS */




// REGISTERS

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_riTs
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_count_til_drop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_gapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_ts_ms
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_count_til_ecn
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);

p4_pd_status_t
p4_pd_fsmmf_register_hw_sync_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_fsmmf_register_read_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_fsmmf_register_range_reset_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_fsmmf_register_write_all_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

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
);



/* METERS */


/* LPF */

p4_pd_status_t
p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
);

p4_pd_status_t
p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
);

p4_pd_status_t
p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
);

p4_pd_status_t
p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
);

p4_pd_status_t
p4_pd_fsmmf_lpf_set_Ingress_bottlenecked_rate_lpf_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
);

p4_pd_status_t
p4_pd_fsmmf_lpf_read_Ingress_bottlenecked_rate_lpf_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_lpf_spec_t *lpf_spec
);


/* WRED */



typedef struct __attribute__((__packed__)) p4_pd_fsmmf_ig_snapshot_trig_spec {
  uint16_t _hash_field_argument0;
  uint16_t _tmp2;
  uint32_t bottlenecked_rate_cms_output_1;
  uint32_t bottlenecked_rate_cms_output_2;
  uint32_t bottlenecked_rate_cms_output_3;
  uint32_t const_to_phv_32w20000;
  uint32_t const_to_phv_32w5000000;
  uint8_t hdr_ethernet_dst_addr[6];
  uint16_t hdr_ethernet_ether_type;
  uint8_t hdr_ethernet_src_addr[6];
  uint8_t hdr_ip_dscp;
  uint32_t hdr_ip_dst_addr;
  uint8_t hdr_ip_ecn;
  uint8_t hdr_ip_flags;
  uint16_t hdr_ip_frag_offset;
  uint16_t hdr_ip_hdr_checksum;
  uint16_t hdr_ip_identification;
  uint8_t hdr_ip_ihl;
  uint8_t hdr_ip_protocol;
  uint32_t hdr_ip_src_addr;
  uint16_t hdr_ip_total_len;
  uint8_t hdr_ip_ttl;
  uint8_t hdr_ip_version;
  uint32_t hdr_tcp_ack_no;
  uint16_t hdr_tcp_checksum;
  uint8_t hdr_tcp_data_offset;
  uint16_t hdr_tcp_dst_port;
  uint8_t hdr_tcp_flags;
  uint8_t hdr_tcp_res;
  uint32_t hdr_tcp_seq_no;
  uint16_t hdr_tcp_src_port;
  uint16_t hdr_tcp_urgent_ptr;
  uint16_t hdr_tcp_window;
  uint16_t hdr_udp_checksum;
  uint16_t hdr_udp_dst_port;
  uint16_t hdr_udp_hdr_lenght;
  uint16_t hdr_udp_src_port;
  uint8_t ig_intr_md_ingress_mac_tstamp[6];
  uint8_t ig_intr_md_for_dprsr_drop_ctl;
  uint8_t ig_intr_md_for_dprsr_mirror_type;
  uint16_t ig_intr_md_for_tm_ucast_egress_port;
  uint32_t md_RC;
  uint16_t md_dport;
  uint16_t md_fid;
  uint32_t md_measured_rate;
  uint32_t md_pktlen;
  uint16_t md_sport;
  uint32_t t_igr_RC_minus_threshold;
  uint8_t t_igr_RC_nag;
  uint32_t t_igr_burst;
  uint8_t t_igr_drop_flag;
  uint32_t t_igr_dt;
  uint32_t t_igr_dt_ms;
  uint32_t t_igr_dt_x_rate_B;
  uint8_t t_igr_ecn_flag;
  uint32_t t_igr_gapRC;
  uint8_t t_igr_ifburstStage;
  uint16_t t_igr_log_dt;
  uint32_t t_igr_pktlen_minus_dt_x_rate;
  uint32_t t_igr_rate;
  uint32_t t_igr_table_key;
  uint8_t t_igr_tcp_drop_flag;
  uint32_t t_igr_ts;
  uint32_t t_igr_ts_ms;
  /* POV fields */
  uint8_t hdr_ethernet_valid;
  uint8_t hdr_ip_valid;
  uint8_t hdr_tcp_valid;
  uint8_t hdr_udp_valid;

} p4_pd_fsmmf_ig_snapshot_trig_spec_t;


typedef struct __attribute__((__packed__)) p4_pd_fsmmf_eg_snapshot_trig_spec {
  uint16_t eg_intr_md_egress_port;
  uint8_t hdr_ethernet_dst_addr[6];
  uint16_t hdr_ethernet_ether_type;
  uint8_t hdr_ethernet_src_addr[6];
  uint8_t hdr_ip_dscp;
  uint32_t hdr_ip_dst_addr;
  uint8_t hdr_ip_ecn;
  uint8_t hdr_ip_flags;
  uint16_t hdr_ip_frag_offset;
  uint16_t hdr_ip_hdr_checksum;
  uint16_t hdr_ip_identification;
  uint8_t hdr_ip_ihl;
  uint8_t hdr_ip_protocol;
  uint32_t hdr_ip_src_addr;
  uint16_t hdr_ip_total_len;
  uint8_t hdr_ip_ttl;
  uint8_t hdr_ip_version;
  uint8_t hdr_min_parse_depth_padding_0_0__packet_payload[11];
  uint8_t hdr_min_parse_depth_padding_0_1__packet_payload[11];
  uint8_t hdr_min_parse_depth_padding_0_2__packet_payload[11];
  uint8_t hdr_min_parse_depth_padding_0__stkvalid;
  uint32_t hdr_tcp_ack_no;
  uint16_t hdr_tcp_checksum;
  uint8_t hdr_tcp_data_offset;
  uint16_t hdr_tcp_dst_port;
  uint8_t hdr_tcp_flags;
  uint8_t hdr_tcp_res;
  uint32_t hdr_tcp_seq_no;
  uint16_t hdr_tcp_src_port;
  uint16_t hdr_tcp_urgent_ptr;
  uint16_t hdr_tcp_window;
  uint16_t hdr_udp_checksum;
  uint16_t hdr_udp_dst_port;
  uint16_t hdr_udp_hdr_lenght;
  uint16_t hdr_udp_src_port;
  /* POV fields */
  uint8_t hdr_ethernet_valid;
  uint8_t hdr_ip_valid;
  uint8_t hdr_min_parse_depth_padding_0_0__valid;
  uint8_t hdr_min_parse_depth_padding_0_1__valid;
  uint8_t hdr_min_parse_depth_padding_0_2__valid;
  uint8_t hdr_tcp_valid;
  uint8_t hdr_udp_valid;

} p4_pd_fsmmf_eg_snapshot_trig_spec_t;


typedef struct __attribute__((__packed__)) p4_pd_fsmmf_snapshot_trig_spec {
    union {
        p4_pd_fsmmf_ig_snapshot_trig_spec_t ig;
        p4_pd_fsmmf_eg_snapshot_trig_spec_t eg;
    } u;
}  p4_pd_fsmmf_snapshot_trig_spec_t;


typedef p4_pd_fsmmf_ig_snapshot_trig_spec_t p4_pd_fsmmf_ig_snapshot_capture_data_t;
typedef p4_pd_fsmmf_eg_snapshot_trig_spec_t p4_pd_fsmmf_eg_snapshot_capture_data_t;


typedef struct __attribute__ ((__packed__)) p4_pd_fsmmf_snapshot_capture {
     union {
         p4_pd_fsmmf_ig_snapshot_capture_data_t ig;
         p4_pd_fsmmf_eg_snapshot_capture_data_t eg;
     } u;
} p4_pd_fsmmf_snapshot_capture_t;

/* Array of snapshot captures if start and en stage are different */
typedef struct p4_pd_fsmmf_snapshot_capture_arr {
    p4_pd_fsmmf_snapshot_capture_t captures[BF_MAX_SNAPSHOT_CAPTURES];
} p4_pd_fsmmf_snapshot_capture_arr_t;


/**
 * @brief Set snapshot trigger.
 * @param hdl Snapshot handle.
 * @param trig_spec Trigger spec.
 * @param trig_mask Trigger mask.
 * @return status.
*/
p4_pd_status_t
p4_pd_fsmmf_snapshot_capture_trigger_set(
              pipe_snapshot_hdl_t hdl,
              p4_pd_fsmmf_snapshot_trig_spec_t *trig_spec,
              p4_pd_fsmmf_snapshot_trig_spec_t *trig_mask);

/**
 * @brief Get snapshot capture data.
 * @param hdl Snapshot handle.
 * @param pipe Pipe.
 * @param capture Captured data
 * @param num_captures Num of captures
 * @return status.
*/
p4_pd_status_t
p4_pd_fsmmf_snapshot_capture_data_get(
              pipe_snapshot_hdl_t hdl,
              bf_dev_pipe_t dev_pipe_id,
              p4_pd_fsmmf_snapshot_capture_arr_t *capture,
              bf_snapshot_capture_ctrl_info_arr_t *capture_ctrl_arr,
              int *num_captures);

/**
 * @brief Create a snapshot.
 * @param dev_tgt Device information.
 * @param start_stage_id Start stage.
 * @param end_stage_id End stage.
 * @param direction Ingress or egress
 * @param hdl Snapshot handle.
 * @return status.
*/
p4_pd_status_t
p4_pd_fsmmf_snapshot_create(
            p4_pd_dev_target_t dev_tgt,
            uint8_t start_stage_id, uint8_t end_stage_id,
            bf_snapshot_dir_t direction,
            pipe_snapshot_hdl_t *hdl);

/**
 * @brief Delete snapshot.
 * @param hdl Snapshot handle.
 * @return status.
*/
p4_pd_status_t
p4_pd_fsmmf_snapshot_delete(
            pipe_snapshot_hdl_t hdl);





typedef enum p4_pd_fsmmf_input_fields__field_list_1{
  P4_PD_INPUT_FIELD__FIELD_LIST_1__HASH_FIELD_ARGUMENT0 = 0,
} p4_pd_fsmmf_input_fields__field_list_1_t;

typedef enum p4_pd_fsmmf_input_field_attr_type {
  P4_PD_INPUT_FIELD_ATTR_TYPE_MASK = 0,
  P4_PD_INPUT_FIELD_ATTR_TYPE_VALUE,
} p4_pd_fsmmf_input_field_attr_type_t;

typedef enum p4_pd_fsmmf_input_field_attr_value_mask {
  P4_PD_INPUT_FIELD_EXCLUDED = 0,
  P4_PD_INPUT_FIELD_INCLUDED
} p4_pd_fsmmf_input_field_attr_value_mask_t;

typedef enum p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input{
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute{
  union {
    p4_pd_fsmmf_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_fsmmf_input_field_attr_type_t type;
  union {
    p4_pd_fsmmf_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t;

typedef enum p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_ALGORITHM_CRC_32,
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t;

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t *input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

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
);
typedef enum p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input{
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute{
  union {
    p4_pd_fsmmf_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_fsmmf_input_field_attr_type_t type;
  union {
    p4_pd_fsmmf_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t;

typedef enum p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_ALGORITHM_CRC_32,
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t;

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t *input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

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
);
typedef enum p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input{
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t;

typedef struct p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute{
  union {
    p4_pd_fsmmf_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_fsmmf_input_field_attr_type_t type;
  union {
    p4_pd_fsmmf_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t;

typedef enum p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_ALGORITHM_CRC_16,
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t;

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t *input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

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
);
typedef enum p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input{
  P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute{
  union {
    p4_pd_fsmmf_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_fsmmf_input_field_attr_type_t type;
  union {
    p4_pd_fsmmf_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t;

typedef enum p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo {
  P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_ALGORITHM_CRC_16,
} p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t;

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t *input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

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
);
typedef enum p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input{
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t;

typedef struct p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute{
  union {
    p4_pd_fsmmf_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_fsmmf_input_field_attr_type_t type;
  union {
    p4_pd_fsmmf_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t;

typedef enum p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_ALGORITHM_CRC_32,
} p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t;

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t *input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

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
);
typedef enum p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input{
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t;

typedef struct p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute{
  union {
    p4_pd_fsmmf_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_fsmmf_input_field_attr_type_t type;
  union {
    p4_pd_fsmmf_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t;

typedef enum p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_ALGORITHM_CRC_16,
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t;

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t *input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

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
);
typedef enum p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input{
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t;

typedef struct p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute{
  union {
    p4_pd_fsmmf_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_fsmmf_input_field_attr_type_t type;
  union {
    p4_pd_fsmmf_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t;

typedef enum p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_ALGORITHM_CRC_16,
} p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t;

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t *input
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input,
 uint32_t attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_fsmmf_hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

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
);

#endif
