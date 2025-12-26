#!/bin/bash
set -e
sudo pkill bf_switchd || true
sudo $(realpath bf_switchd) --install-dir $SDE_INSTALL --conf-file $(realpath fsmmf)/fsmmf.conf