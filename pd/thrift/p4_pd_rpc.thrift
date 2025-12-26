# BFN Thrift RPC Input

include "res.thrift"


namespace py p4_pd_rpc
namespace cpp p4_pd_rpc
namespace c_glib p4_pd_rpc

typedef i32 EntryHandle_t
typedef i32 MemberHandle_t
typedef i32 GroupHandle_t
typedef binary MacAddr_t
typedef binary IPv6_t
typedef i32 SnapshotHandle_t
typedef i32 PvsHandle_t

struct fsmmf_counter_value_t {
  1: required i64 packets;
  2: required i64 bytes;
}

struct fsmmf_packets_meter_spec_t {
  1: required i64 cir_pps;
  2: required i64 cburst_pkts;
  3: required i64 pir_pps;
  4: required i64 pburst_pkts;
  5: required bool color_aware;
  6: optional bool is_set = 1;
}

struct fsmmf_bytes_meter_spec_t {
  1: required i64 cir_kbps;
  2: required i64 cburst_kbits;
  3: required i64 pir_kbps;
  4: required i64 pburst_kbits;
  5: required bool color_aware;
  6: optional bool is_set = 1;
}

enum fsmmf_lpf_type {
  TYPE_RATE = 0,
  TYPE_SAMPLE = 1
}

struct fsmmf_lpf_spec_t {
  1: required bool gain_decay_separate_time_constant;
  2: required double gain_time_constant;
  3: required double decay_time_constant;
  4: required double time_constant;
  5: required i32 output_scale_down_factor;
  6: required fsmmf_lpf_type lpf_type;
  7: optional bool is_set = 1;
}

struct fsmmf_wred_spec_t {
  1: required double time_constant;
  2: required i32 red_min_threshold;
  3: required i32 red_max_threshold;
  4: required double max_probability;
  5: optional bool is_set = 1;
}


enum fsmmf_idle_time_mode {
  POLL_MODE = 0,
  NOTIFY_MODE = 1,
  INVALID_MODE = 2
}

enum fsmmf_idle_time_hit_state {
  ENTRY_IDLE = 0,
  ENTRY_ACTIVE = 1
}

struct fsmmf_idle_time_params_t {
  1: required fsmmf_idle_time_mode mode;
  2: optional i32 ttl_query_interval;
  3: optional i32 max_ttl;
  4: optional i32 min_ttl;
  5: optional i32 cookie;
}

struct fsmmf_idle_tmo_expired_t {
  1: required i32 dev_id;
  2: required EntryHandle_t entry;
  3: required i32 cookie;
}

struct fsmmf_sel_update_t {
  1: required res.SessionHandle_t  sess_hdl;
  2: required res.DevTarget_t      dev_tgt;
  3: required i32                  cookie;
  4: required i32                  grp_hdl;
  5: required i32                  mbr_hdl;
  6: required i32                  index;
  7: required bool                 is_add;
}

enum fsmmf_grp_mbr_state {
  MBR_ACTIVE = 0,
  MBR_INACTIVE = 1
}


enum tbl_property_t
{
   TBL_PROP_TBL_ENTRY_SCOPE = 1,
   TBL_PROP_TERN_TABLE_ENTRY_PLACEMENT = 2,
   TBL_PROP_DUPLICATE_ENTRY_CHECK = 3,
   TBL_PROP_IDLETIME_REPEATED_NOTIFICATION = 4
}

enum tbl_property_value_t
{
   ENTRY_SCOPE_ALL_PIPELINES=0,
   ENTRY_SCOPE_SINGLE_PIPELINE=1,
   ENTRY_SCOPE_USER_DEFINED=2,
   TERN_ENTRY_PLACEMENT_DRV_MANAGED=0,
   TERN_ENTRY_PLACEMENT_APP_MANAGED=1,
   DUPLICATE_ENTRY_CHECK_DISABLE=0,
   DUPLICATE_ENTRY_CHECK_ENABLE=1,
   IDLETIME_REPEATED_NOTIFICATION_DISABLE = 0,
   IDLETIME_REPEATED_NOTIFICATION_ENABLE = 1
}

struct tbl_property_value_args_t
{
  1: required tbl_property_value_t value;
  2: required i32                  scope_args;
}

enum pvs_gress_t
{
   PVS_GRESS_INGRESS = 0,
   PVS_GRESS_EGRESS = 1,
   PVS_GRESS_ALL = 0xff
}

enum pvs_property_t {
  PVS_PROP_NONE = 0,
  PVS_GRESS_SCOPE,
  PVS_PIPE_SCOPE,
  PVS_PARSER_SCOPE
}

enum pvs_property_value_t {
  PVS_SCOPE_ALL_GRESS = 0,
  PVS_SCOPE_SINGLE_GRESS = 1,
  PVS_SCOPE_ALL_PIPELINES = 0,
  PVS_SCOPE_SINGLE_PIPELINE = 1,
  PVS_SCOPE_ALL_PARSERS = 0,
  PVS_SCOPE_SINGLE_PARSER = 1
}

enum tbl_dbg_counter_type_t {
  TBL_DBG_CNTR_DISABLED = 0,
  TBL_DBG_CNTR_LOG_TBL_MISS,
  TBL_DBG_CNTR_LOG_TBL_HIT,
  TBL_DBG_CNTR_GW_TBL_MISS,
  TBL_DBG_CNTR_GW_TBL_HIT,
  TBL_DBG_CNTR_GW_TBL_INHIBIT,
  TBL_DBG_CNTR_MAX
}

struct PVSSpec_t {
  1: required i32 parser_value;
  2: required i32 parser_value_mask;
}

struct TblCntrInfo_t {
  1: required tbl_dbg_counter_type_t type;
  2: required i32 value;
}

struct TblDbgStageInfo_t {
  1: required i32 num_counters;
  2: required list<string> tbl_name;
  3: required list<tbl_dbg_counter_type_t> type;
  4: required list<i32> value;
}

# not very space efficient but convenient
struct fsmmf_counter_flags_t {
  1: required bool read_hw_sync;
}

struct fsmmf_register_flags_t {
  1: required bool read_hw_sync;
}

struct fsmmf_snapshot_trig_spec_t {
  1: required string field_name;
  2: required i64 field_value;
  3: required i64 field_mask;
}

struct fsmmf_snapshot_tbl_data_t {
  1: required bool hit;
  2: required bool inhibited;
  3: required bool executed;
  4: required i32 hit_entry_handle;
}

enum fsmmf_input_fields__field_list_1_t {
  _FIELD_LIST_1__HASH_FIELD_ARGUMENT0 = 0,
}

enum fsmmf_input_field_attr_type_t {
  INPUT_FIELD_ATTR_TYPE_MASK,
  INPUT_FIELD_ATTR_TYPE_VALUE
}

enum fsmmf_input_field_attr_value_mask_t {
  INPUT_FIELD_EXCLUDED = 0,
  INPUT_FIELD_INCLUDED
}

enum fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1,
}

union fsmmf_Ingress_t_igr_identity_hasher0_configure_input_fields_union_t {
  1: fsmmf_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attr_value_union_t {
  1: fsmmf_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required fsmmf_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_ALGORITHM_CRC_32,
}
enum fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_INPUT__FIELD_LIST_1,
}

union fsmmf_Ingress_t_igr_identity_hasher1_configure_input_fields_union_t {
  1: fsmmf_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attr_value_union_t {
  1: fsmmf_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required fsmmf_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER1_CONFIGURE_ALGORITHM_CRC_32,
}
enum fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_INPUT__FIELD_LIST_1,
}

union fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_fields_union_t {
  1: fsmmf_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attr_value_union_t {
  1: fsmmf_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required fsmmf_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_2_CONFIGURE_ALGORITHM_CRC_16,
}
enum fsmmf_Ingress_t_igr_hash_index_configure_input_t {
  P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_INPUT__FIELD_LIST_1,
}

union fsmmf_Ingress_t_igr_hash_index_configure_input_fields_union_t {
  1: fsmmf_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union fsmmf_Ingress_t_igr_hash_index_configure_input_field_attr_value_union_t {
  1: fsmmf_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required fsmmf_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum fsmmf_Ingress_t_igr_hash_index_configure_algo_t {
  P4_PD_FSMMF_INGRESS_T_IGR_HASH_INDEX_CONFIGURE_ALGORITHM_CRC_16,
}
enum fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1,
}

union fsmmf_Ingress_t_igr_identity_hasher2_configure_input_fields_union_t {
  1: fsmmf_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attr_value_union_t {
  1: fsmmf_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required fsmmf_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t {
  P4_PD_FSMMF_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_ALGORITHM_CRC_32,
}
enum fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_INPUT__FIELD_LIST_1,
}

union fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_fields_union_t {
  1: fsmmf_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attr_value_union_t {
  1: fsmmf_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required fsmmf_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_1_CONFIGURE_ALGORITHM_CRC_16,
}
enum fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_INPUT__FIELD_LIST_1,
}

union fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_fields_union_t {
  1: fsmmf_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attr_value_union_t {
  1: fsmmf_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required fsmmf_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t {
  P4_PD_FSMMF_INGRESS_BOTTLENECKED_RATE_HASH_3_CONFIGURE_ALGORITHM_CRC_16,
}


# Match structs

struct fsmmf_IngressParser__PORT_METADATA_match_spec_t {
  1: required i16 ig_intr_md_ingress_port;
}

struct fsmmf_Ingress_t_igr_tiForward_match_spec_t {
  1: required MacAddr_t hdr_ethernet_dst_addr;
}

struct fsmmf_Ingress_t_igr_tiRate_match_spec_t {
  1: required i32 table_key;
}

struct fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t {
  1: required i16 log_dt;
  2: required i32 rate;
}

struct fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t {
  1: required i32 md_RC;
  2: required i32 md_RC_mask;
}

struct fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t {
  1: required i32 gapRC;
  2: required i32 gapRC_mask;
}


# Match struct for Dynamic Key Mask Exm Table.


# Action structs

struct fsmmf_set_port_metadata_action_spec_t {
  1: required binary action_ig_intr_md;
}

struct fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t {
  1: required i16 action_egr_port;
}

struct fsmmf_Ingress_t_igr_aiRate_action_spec_t {
  1: required i32 action_Allocate_rate;
}

struct fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t {
  1: required i32 action_Calc_dt_x_rate;
  2: required i32 action_Calc_dt_x_rate_B;
}

union fsmmf_action_specs_t {
  1: fsmmf_set_port_metadata_action_spec_t fsmmf_set_port_metadata;
  2: fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t fsmmf_Ingress_t_igr_aiSetEgress;
  3: fsmmf_Ingress_t_igr_aiRate_action_spec_t fsmmf_Ingress_t_igr_aiRate;
  4: fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t fsmmf_Ingress_t_igr_aiCalc_dt_x_rate;
}

struct fsmmf_action_desc_t {
  1: required string name;
  2: required fsmmf_action_specs_t data;
}


# Register values


# Entry Descriptions

struct fsmmf_IngressParser__PORT_METADATA_entry_desc_t {
  1: required fsmmf_IngressParser__PORT_METADATA_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required fsmmf_action_desc_t action_desc;
}

struct fsmmf_Ingress_t_igr_tiForward_entry_desc_t {
  1: required fsmmf_Ingress_t_igr_tiForward_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required fsmmf_action_desc_t action_desc;
}

struct fsmmf_Ingress_t_igr_tiRate_entry_desc_t {
  1: required fsmmf_Ingress_t_igr_tiRate_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required fsmmf_action_desc_t action_desc;
}

struct fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_entry_desc_t {
  1: required fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required fsmmf_action_desc_t action_desc;
}

struct fsmmf_Ingress_t_igr_tiRC_nag_entry_desc_t {
  1: required fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required fsmmf_action_desc_t action_desc;
}

struct fsmmf_Ingress_t_igr_tiGapRC_pos_entry_desc_t {
  1: required fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required fsmmf_action_desc_t action_desc;
}




exception InvalidTableOperation {
 1:i32 code
}

exception InvalidLearnOperation {
 1:i32 code
}

exception InvalidDbgOperation {
 1:i32 code
}

exception InvalidSnapshotOperation {
 1:i32 code
}

exception InvalidCounterOperation {
 1:i32 code
}

exception InvalidRegisterOperation {
 1:i32 code
}

exception InvalidMeterOperation {
 1:i32 code
}

exception InvalidLPFOperation {
 1:i32 code
}

exception InvalidWREDOperation {
 1:i32 code
}


service fsmmf {

    # Idle time config



    EntryHandle_t IngressParser__PORT_METADATA_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_IngressParser__PORT_METADATA_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRate_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRate_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),


    # Dynamic Key Mask Exm Table.
      # set API

    # Table entry add functions

    EntryHandle_t IngressParser__PORT_METADATA_table_add_with_set_port_metadata(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_IngressParser__PORT_METADATA_match_spec_t match_spec, 4:fsmmf_set_port_metadata_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiForward_match_spec_t match_spec, 4:fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRate_match_spec_t match_spec, 4:fsmmf_Ingress_t_igr_aiRate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t match_spec, 4:fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_neg(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_table_add_with_Ingress_t_igr_aiRC_pos(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_neg(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_add_with_Ingress_t_igr_aiGapRC_pos(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),

    # Table entry modify functions
    void IngressParser__PORT_METADATA_table_modify_with_set_port_metadata(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:fsmmf_set_port_metadata_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_IngressParser__PORT_METADATA_match_spec_t match_spec, 4:fsmmf_set_port_metadata_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiForward_match_spec_t match_spec, 4:fsmmf_Ingress_t_igr_aiSetEgress_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:fsmmf_Ingress_t_igr_aiRate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRate_match_spec_t match_spec, 4:fsmmf_Ingress_t_igr_aiRate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t match_spec, 4:fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRC_nag_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRC_nag_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_neg_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRC_nag_table_modify_with_Ingress_t_igr_aiRC_pos_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGapRC_pos_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_neg_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGapRC_pos_table_modify_with_Ingress_t_igr_aiGapRC_pos_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),

    # Table entry delete functions
# //::   if action_table_hdl: continue
    void IngressParser__PORT_METADATA_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void IngressParser__PORT_METADATA_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_IngressParser__PORT_METADATA_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiForward_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRate_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRate_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRate_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_dt_x_rate_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_dt_x_rate_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRC_nag_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRC_nag_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiRC_nag_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGapRC_pos_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGapRC_pos_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_tiGapRC_pos_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),

    # Table default entry get functions
    EntryHandle_t IngressParser__PORT_METADATA_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    fsmmf_IngressParser__PORT_METADATA_entry_desc_t IngressParser__PORT_METADATA_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    fsmmf_Ingress_t_igr_tiForward_entry_desc_t Ingress_t_igr_tiForward_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRate_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    fsmmf_Ingress_t_igr_tiRate_entry_desc_t Ingress_t_igr_tiRate_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_entry_desc_t Ingress_t_igr_tiCalc_dt_x_rate_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    fsmmf_Ingress_t_igr_tiRC_nag_entry_desc_t Ingress_t_igr_tiRC_nag_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    fsmmf_Ingress_t_igr_tiGapRC_pos_entry_desc_t Ingress_t_igr_tiGapRC_pos_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    # Table default entry clear functions
# //::   if action_table_hdl: continue
    void IngressParser__PORT_METADATA_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiForward_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRate_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_dt_x_rate_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRC_nag_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGapRC_pos_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    i32 IngressParser__PORT_METADATA_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiForward_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiRate_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiCalc_dt_x_rate_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiRC_nag_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiGapRC_pos_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),


    # Get first entry handle functions
    EntryHandle_t IngressParser__PORT_METADATA_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> IngressParser__PORT_METADATA_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    fsmmf_IngressParser__PORT_METADATA_entry_desc_t IngressParser__PORT_METADATA_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiForward_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiForward_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    fsmmf_Ingress_t_igr_tiForward_entry_desc_t Ingress_t_igr_tiForward_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiRate_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiRate_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    fsmmf_Ingress_t_igr_tiRate_entry_desc_t Ingress_t_igr_tiRate_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiCalc_dt_x_rate_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_entry_desc_t Ingress_t_igr_tiCalc_dt_x_rate_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiRC_nag_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiRC_nag_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    fsmmf_Ingress_t_igr_tiRC_nag_entry_desc_t Ingress_t_igr_tiRC_nag_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiGapRC_pos_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiGapRC_pos_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    fsmmf_Ingress_t_igr_tiGapRC_pos_entry_desc_t Ingress_t_igr_tiGapRC_pos_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),



    # Table set default action functions

    EntryHandle_t Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRate_set_default_action_Ingress_t_igr_aiRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_aiRate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_dt_x_rate_set_default_action_Ingress_t_igr_aiCalc_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_neg(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRC_nag_set_default_action_Ingress_t_igr_aiRC_pos(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_neg(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGapRC_pos_set_default_action_Ingress_t_igr_aiGapRC_pos(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    
     # Table set/get property
# //::   if action_table_hdl: continue
    void IngressParser__PORT_METADATA_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t IngressParser__PORT_METADATA_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiForward_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiForward_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRate_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiRate_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_dt_x_rate_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiCalc_dt_x_rate_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRC_nag_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiRC_nag_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGapRC_pos_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiGapRC_pos_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),

    # INDIRECT ACTION DATA AND MATCH SELECT






    void set_learning_timeout(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 usecs) throws (1:InvalidLearnOperation ouch),

    void tbl_dbg_counter_type_set(1:res.DevTarget_t dev_tgt, 2:string tbl_name, 3:tbl_dbg_counter_type_t type) throws (1:InvalidDbgOperation ouch),

    TblCntrInfo_t tbl_dbg_counter_get(1:res.DevTarget_t dev_tgt, 2:string tbl_name) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_clear(1:res.DevTarget_t dev_tgt, 2:string tbl_name) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_type_stage_set(1:res.DevTarget_t dev_tgt, 2:byte stage, 3:tbl_dbg_counter_type_t type) throws (1:InvalidDbgOperation ouch),

    TblDbgStageInfo_t tbl_dbg_counter_stage_get(1:res.DevTarget_t dev_tgt, 2:byte stage) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_stage_clear(1:res.DevTarget_t dev_tgt, 2: byte stage) throws (1:InvalidDbgOperation ouch),

    SnapshotHandle_t snapshot_create(1:res.DevTarget_t dev_tgt, 2:byte start_stage, 3:byte end_stage, 4:byte direction) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_delete(1:SnapshotHandle_t handle) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_state_set(1: SnapshotHandle_t handle, 2:i32 state, 3:i32 usecs) throws (1:InvalidSnapshotOperation ouch),

    i32 snapshot_state_get(1:SnapshotHandle_t handle, 2:i16 pipe) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_timer_enable(1: SnapshotHandle_t handle, 2:byte disable) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_capture_trigger_set(1: SnapshotHandle_t handle,
                2:fsmmf_snapshot_trig_spec_t trig_spec,
                3:fsmmf_snapshot_trig_spec_t trig_spec2) throws (1:InvalidSnapshotOperation ouch),

    i64 snapshot_capture_data_get(1: SnapshotHandle_t handle, 2:i16 pipe, 3:i16 stage_id, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    fsmmf_snapshot_tbl_data_t snapshot_capture_tbl_data_get(1: SnapshotHandle_t handle, 2:i16 pipe, 3:string table_name) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_capture_trigger_fields_clr(1:SnapshotHandle_t handle) throws (1:InvalidSnapshotOperation ouch),

    bool snapshot_field_in_scope(1:res.DevTarget_t dev_tgt, 2:byte stage,
                 3:byte direction, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    bool snapshot_trigger_field_in_scope(1:res.DevTarget_t dev_tgt, 2:byte stage,
                 3:byte direction, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    # counters



    # registers

    void register_hw_sync_Ingress_t_igr_riTs(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_riTs(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_riTs(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_riTs(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_riTs(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_riTs(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_riTs(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ridt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ridt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ridt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ridt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ridt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ridt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ridt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_count_til_drop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_count_til_drop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_count_til_drop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_count_til_drop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_count_til_drop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_count_til_drop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_count_til_drop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_riRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_riRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_riRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_riRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_riRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_riRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_riRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ri_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ri_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ri_dt_x_rate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_bottleneckF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_bottleneckF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_bottleneckF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_bottleneckF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_bottleneckF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_bottleneckF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_bottleneckF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ritestgapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ritestgapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ritestgapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ritestgapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ritestgapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ritestgapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ritestgapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ritestburstdrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ritestburstdrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ritestburstdrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ritestburstdrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ritestburstdrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ritestburstdrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ritestburstdrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ri_gapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ri_gapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_gapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_gapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_gapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_gapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ri_gapRC(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_bottlenecked_rate_bottleneckedRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_bottlenecked_rate_bottleneckedRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_bottlenecked_rate_bottleneckedRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_bottlenecked_rate_bottleneckedRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_bottlenecked_rate_bottleneckedRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_bottlenecked_rate_bottleneckedRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_bottlenecked_rate_bottleneckedRate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ri_ts_ms(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ri_ts_ms(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_ts_ms(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_ts_ms(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_ts_ms(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_ts_ms(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ri_ts_ms(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_riburstStage(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_riburstStage(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_riburstStage(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_riburstStage(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_riburstStage(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_riburstStage(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_riburstStage(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_count_til_ecn(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_count_til_ecn(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_count_til_ecn(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_count_til_ecn(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_count_til_ecn(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_count_til_ecn(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_count_til_ecn(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ri_lograte(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ri_lograte(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_lograte(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_lograte(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_lograte(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_lograte(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ri_lograte(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:fsmmf_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),


    fsmmf_lpf_spec_t lpf_read_Ingress_bottlenecked_rate_lpf_3(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index) throws (1:InvalidLPFOperation ouch),
    void lpf_set_Ingress_bottlenecked_rate_lpf_3(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_lpf_spec_t lpf_spec) throws (1:InvalidLPFOperation ouch),
    fsmmf_lpf_spec_t lpf_read_Ingress_bottlenecked_rate_lpf_2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index) throws (1:InvalidLPFOperation ouch),
    void lpf_set_Ingress_bottlenecked_rate_lpf_2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_lpf_spec_t lpf_spec) throws (1:InvalidLPFOperation ouch),
    fsmmf_lpf_spec_t lpf_read_Ingress_bottlenecked_rate_lpf_1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index) throws (1:InvalidLPFOperation ouch),
    void lpf_set_Ingress_bottlenecked_rate_lpf_1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:fsmmf_lpf_spec_t lpf_spec) throws (1:InvalidLPFOperation ouch),






    void hash_calc_Ingress_t_igr_identity_hasher0_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher0_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher0_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input, 4:list<fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher0_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_t_igr_identity_hasher0_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<fsmmf_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Ingress_t_igr_identity_hasher1_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher1_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher1_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher1_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_t_igr_identity_hasher1_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input, 4:list<fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t> hash_calc_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher1_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_t_igr_identity_hasher1_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<fsmmf_Ingress_t_igr_identity_hasher1_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_2_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_2_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_bottlenecked_rate_hash_2_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input, 4:list<fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t> hash_calc_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_bottlenecked_rate_hash_2_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<fsmmf_Ingress_bottlenecked_rate_hash_2_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Ingress_t_igr_hash_index_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_hash_index_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_hash_index_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_hash_index_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_hash_index_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_hash_index_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_hash_index_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_t_igr_hash_index_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_hash_index_configure_input_t input, 4:list<fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_hash_index_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t> hash_calc_Ingress_t_igr_hash_index_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_hash_index_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_t_igr_hash_index_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<fsmmf_Ingress_t_igr_hash_index_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Ingress_t_igr_identity_hasher2_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher2_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher2_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input, 4:list<fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_t_igr_identity_hasher2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_t_igr_identity_hasher2_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<fsmmf_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_1_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_1_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_bottlenecked_rate_hash_1_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input, 4:list<fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t> hash_calc_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_bottlenecked_rate_hash_1_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<fsmmf_Ingress_bottlenecked_rate_hash_1_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_3_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_3_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_bottlenecked_rate_hash_3_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input, 4:list<fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t> hash_calc_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_bottlenecked_rate_hash_3_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<fsmmf_Ingress_bottlenecked_rate_hash_3_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


} 
