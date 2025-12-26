typedef struct p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec {
  uint32_t table_key;
} p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec_t;
typedef struct p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec {
  uint32_t action_Allocate_rate;
} p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec_t;
typedef struct p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec {
  uint16_t log_dt;
  uint32_t rate;
} p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec_t;
typedef struct p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec {
  uint32_t action_Calc_dt_x_rate;
  uint32_t action_Calc_dt_x_rate_B;
} p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec_t;

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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_riRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_bottleneckF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_bottlenecked_rate_bottleneckedRate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_riburstStage
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestburstdrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestgapRC
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ridt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_dt_x_rate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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

p4_pd_status_t
p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_lograte
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
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
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
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