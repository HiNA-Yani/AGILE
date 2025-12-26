# AGILE: Achieving Max-Min Fairness and High Utilization for In-Network Bandwidth Allocation
This repository hosts the prototype implementation of our INFOCOM 2026 paper:

**AGILE: Achieving Max-Min Fairness and High Utilization for In-Network Bandwidth Allocation**

AGILE is an in-network bandwidth allocation system that achieves **max-min fairness** while maintaining **high link utilization**, by leveraging programmable switches. The system is implemented and evaluated on **Barefoot Tofino-1 switches** using **BF-SDE 9.11**.

---

## Overview

AGILE tightly couples data-plane rate measurement and enforcement with control-plane coordination to achieve scalable and efficient bandwidth allocation directly inside the network.

The system consists of:
- A **P4-based data plane** for real-time rate estimation and fairness enforcement.
- A **C++ control plane** for switch initialization and runtime management.
- **Python and shell scripts** for configuration, automation, and experimentation.
---
## Repository Structure
AGILE/
├── fsmmf/ # Compiled data-plane artifacts (generated after build)
├── include/ # Data-plane header files
├── libs/ # Supporting libraries
├── pd/ # PD-related generated files
├── README.md
├── fsmmf.p4 # Main P4 data-plane program
├── fsmmf.cpp # Control-plane implementation (C++)
├── add_lpf_rules.py # Script to configure LPF rules in the data plane
├── pd_helpers.hpp
├── pd_helpers_gen.py
├── build.sh # Build script (data plane + control plane)
├── run.sh # Script to launch the switch
├── controlplane.sh # Script to run control-plane logic
└── bf_switchd # Switch daemon configuration



