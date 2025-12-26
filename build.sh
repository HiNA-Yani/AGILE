#!/bin/bash
BF_DRV_SRC="${SDE}/pkgsrc/bf-drivers"
TOFINO_CPP_FLAGS="-Wno-missing-field-initializers -Werror -Wshadow -g -O2 -std=c++11"
TOFINO_CPP_LIBS="-lpltfm_mgr_thrift -lpltfm_mgr -lthrift-0.14.1 -lcares  -labsl_raw_logging_internal -labsl_log_severity -labsl_bad_optional_access -labsl_exponential_biased -labsl_strings_internal -labsl_base -labsl_spinlock_wait -labsl_throw_delegate  -labsl_debugging_internal -labsl_demangle_internal -labsl_strings -labsl_int128 -lgrpc++_reflection -labsl_graphcycles_internal -labsl_stacktrace -labsl_symbolize -labsl_time -labsl_civil_time -labsl_time_zone -labsl_malloc_internal -labsl_str_format_internal -labsl_cord -labsl_bad_variant_access -labsl_hashtablez_sampler -labsl_wyhash -labsl_city -lgrpc++ -labsl_raw_hash_set -labsl_hash -laddress_sorting -lupb -labsl_synchronization -labsl_status -lgpr -labsl_statusor -lre2 -lgrpc -lprotobuf -lclish -ldriver -ltarget_utils -ltarget_sys -lbfutils -lm -ldl -lpthread -pthread -Wl,--disable-new-dtags -L${SDE_INSTALL}/lib -Wl,-rpath -Wl,${SDE_INSTALL}/lib"


BUILD_DIR=$(realpath fsmmf.p4)
BUILD_DIR=${BUILD_DIR%.p4}
# echo $BUILD_DIR


rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"


# compile p4
$SDE_INSTALL/bin/bf-p4c --std p4-16 --target tofino --arch tna --verbose 3 -o "$BUILD_DIR" --bf-rt-schema "$BUILD_DIR/bf-rt.json" fsmmf.p4


# genarate PD
${SDE_INSTALL}/bin/generate_tofino_pd --context_json "$BUILD_DIR/pipe/context.json" -o pd


# PD helper
./pd_helpers_gen.py


# compile bf_switchd
g++ -I${BF_DRV_SRC}/include -I${SDE_INSTALL}/include ${TOFINO_CPP_FLAGS} -o bf_switchd fsmmf.cpp ${TOFINO_CPP_LIBS}
