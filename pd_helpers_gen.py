#!/usr/bin/env python3
'''
 * The structure of this file is inspired by the Cebinae project:
 *   https://github.com/eniac/Cebinae
 *
 * All implementation in this file is original unless otherwise stated.
'''

import re

# generate pd_helpers.hpp by copying the most recent definitions from pd.h and pd.c

pdh_fn = "pd/pd/pd.h"
pdc_fn = "pd/src/pd.c"
pd_helpers_fn = "pd_helpers.hpp"

def patch_voidcast(src):
    # cast outputs of bf_sys_calloc to not be void...
    # in declarations.
    res = re.findall(r"(.*?)( \*.* = )(bf_sys_calloc.*)", src)
    for res in res:
        cast_str = "(%s*)"%res[0]
        newline = res[0]+res[1]+cast_str+res[2]
        oldline = res[0]+res[1]+res[2]
        # print ("----")
        # print (oldline)
        # print ("---> ")
        # print (newline)
        # print ("----")
        src = src.replace(oldline, newline)

    # stragglers...
    return src.replace("stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);", 
        "stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);")

def patch_num_actually_read(src):
    return src.replace("int *num_actually_read,", "uint32_t *num_actually_read,")

def main():
    pdh = open(pdh_fn, "r").read()
    pdc = open(pdc_fn, "r").read()

    typedef_names = [
        "p4_pd_fsmmf_Ingress_t_igr_tiRate_match_spec",
        "p4_pd_fsmmf_Ingress_t_igr_aiRate_action_spec",
        "p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_match_spec",
        "p4_pd_fsmmf_Ingress_t_igr_aiCalc_dt_x_rate_action_spec"
        ]
    typedef_blocks = []
    for name in typedef_names:
        print ("extracting pd for: %s"%name)
        res = re.findall("typedef struct %s {.*?} %s_t;"%(name, name), pdh, re.DOTALL)
        typedef_blocks.append(res[0])

    fcn_names = [
    
    # rate table 
    "build_key_Ingress_t_igr_tiRate",
    "build_match_spec_Ingress_t_igr_tiRate",
    "build_action_spec_Ingress_t_igr_aiRate",
    "p4_pd_fsmmf_Ingress_t_igr_tiRate_table_add_with_Ingress_t_igr_aiRate",
    "p4_pd_fsmmf_Ingress_t_igr_tiRate_table_modify_with_Ingress_t_igr_aiRate",
    "p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete",
    "p4_pd_fsmmf_Ingress_t_igr_tiRate_table_delete_by_match_spec",

    # dt_x_rate_table
    "build_key_Ingress_t_igr_tiCalc_dt_x_rate",
    "build_match_spec_Ingress_t_igr_tiCalc_dt_x_rate",
    "build_action_spec_Ingress_t_igr_aiCalc_dt_x_rate",
    "p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_add_with_Ingress_t_igr_aiCalc_dt_x_rate",
    "p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_modify_with_Ingress_t_igr_aiCalc_dt_x_rate",
    "p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete",
    "p4_pd_fsmmf_Ingress_t_igr_tiCalc_dt_x_rate_table_delete_by_match_spec",



    # flow count register
    "register_Ingress_t_igr_fCount_value_pipe_to_pd",
    "register_Ingress_t_igr_fCount_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_fCount",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_fCount",

    # RC / ts register
    "register_Ingress_t_igr_riRC_value_pipe_to_pd",
    "register_Ingress_t_igr_riRC_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_riRC",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riRC",
    "p4_pd_fsmmf_register_write_Ingress_t_igr_riRC",
    # "register_Ingress_t_igr_riTs_value_pipe_to_pd",
    # "register_Ingress_t_igr_riTs_value_pd_to_pipe",
    # "p4_pd_fsmmf_register_range_read_Ingress_t_igr_riTs",
    # "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riTs",

    # bottleneckF register
    "register_Ingress_t_igr_bottleneckF_value_pipe_to_pd",
    "register_Ingress_t_igr_bottleneckF_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_bottleneckF",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_bottleneckF",

    # bottleneckedRate register
    "register_Ingress_bottlenecked_rate_bottleneckedRate_value_pipe_to_pd",
    "register_Ingress_bottlenecked_rate_bottleneckedRate_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_bottlenecked_rate_bottleneckedRate",
    "p4_pd_fsmmf_register_reset_all_Ingress_bottlenecked_rate_bottleneckedRate",

    # burst control
    "register_Ingress_t_igr_riburstStage_value_pipe_to_pd",
    "register_Ingress_t_igr_riburstStage_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_riburstStage",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_riburstStage",
    "p4_pd_fsmmf_register_write_Ingress_t_igr_riburstStage",

    "register_Ingress_t_igr_ritestburstdrop_value_pipe_to_pd",
    "register_Ingress_t_igr_ritestburstdrop_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestburstdrop",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestburstdrop",
    "p4_pd_fsmmf_register_write_Ingress_t_igr_ritestburstdrop",

    "register_Ingress_t_igr_ritestgapRC_value_pipe_to_pd",
    "register_Ingress_t_igr_ritestgapRC_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_ritestgapRC",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ritestgapRC",
    "p4_pd_fsmmf_register_write_Ingress_t_igr_ritestgapRC",

    #test 
    "register_Ingress_t_igr_ridt_value_pipe_to_pd",
    "register_Ingress_t_igr_ridt_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_ridt",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ridt",

    "register_Ingress_t_igr_ri_dt_x_rate_value_pipe_to_pd",
    "register_Ingress_t_igr_ri_dt_x_rate_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_dt_x_rate",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_dt_x_rate",
    # "register_Ingress_t_igr_ri_pktlen_value_pipe_to_pd",
    # "register_Ingress_t_igr_ri_pktlen_value_pd_to_pipe",
    # "p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_pktlen",
    # "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_pktlen",
    "register_Ingress_t_igr_ri_lograte_value_pipe_to_pd",
    "register_Ingress_t_igr_ri_lograte_value_pd_to_pipe",
    "p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_lograte",
    "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_lograte",
    # "register_Ingress_t_igr_ri_pktlen_minus_dt_x_rate_value_pipe_to_pd",    
    # "register_Ingress_t_igr_ri_pktlen_minus_dt_x_rate_value_pd_to_pipe",
    # "p4_pd_fsmmf_register_range_read_Ingress_t_igr_ri_pktlen_minus_dt_x_rate",
    # "p4_pd_fsmmf_register_reset_all_Ingress_t_igr_ri_pktlen_minus_dt_x_rate",

    ]

    fcn_blocks = []
    for name in fcn_names:
        print ("extracting pd for: %s"%name)
        pat = re.compile(r"^[\w\s_]*?%s.*?^}"%(name), re.DOTALL | re.MULTILINE)
        res = re.findall(pat , pdc)
        fcn_blocks.append(res[0])

    # blocks = typedef_blocks + fcn_blocks
    blocks =  typedef_blocks + fcn_blocks
    codeout = "\n".join(blocks)
    codeout = patch_voidcast(codeout)
    codeout = patch_num_actually_read(codeout)
    # print ("------")
    # print (codeout)
    # print ("------")
    open(pd_helpers_fn, "w").write(codeout)

if __name__ == '__main__':
    main()