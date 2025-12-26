#!/bin/bash
set -euo pipefail

echo "run fsmmf.py ..."
python3 ./fsmmf.py
echo "fsmmf.py finished."

echo "set PYTHONPATH for BFRT python modules ..."
PYVER=`python3 -c "import sys; print('%d.%d'%(sys.version_info[0],sys.version_info[1]))"`
INC1=$SDE_INSTALL/lib/python$PYVER/site-packages/tofino/bfrt_grpc/
INC2=$SDE_INSTALL/lib/python$PYVER/site-packages/tofino/
INC3=$SDE_INSTALL/lib/python$PYVER/site-packages/

export PYTHONPATH=$INC1:$INC2:$INC3:PYTHONPATH
echo $PYTHONPATH

echo "add LPF rules ..."
python3 ./add_lpf_rules.py -d 12e6 -s 2

echo "All done."
