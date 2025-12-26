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



