# AGILE: Achieving Max-Min Fairness and High Utilization for In-Network Bandwidth Allocation

This repository hosts the prototype implementation of our INFOCOM 2026 paper:

**AGILE: Achieving Max-Min Fairness and High Utilization for In-Network Bandwidth Allocation**

AGILE is an in-network bandwidth allocation system that achieves **max-min fairness** while maintaining **high link utilization**, by leveraging programmable switches. The system is implemented and evaluated on **Barefoot Tofino-1 switches** using **BF-SDE 9.11**.

---

## Code Structure

This repository contains both **data-plane** and **control-plane** implementations of AGILE.

### Key Files

- `fsmmf.p4`  
  The **data-plane P4 program** (P4_16).  
  It implements AGILE’s in-network bandwidth allocation logic and the required packet processing pipeline on Tofino switches.

- `fsmmf.py`, `add_lpf_rules.py` and `fsmmf.cpp`  
  The **control-plane implementations**.  
  They interact with the switch through the PD interface and bfruntime interface to:
  - install forwarding rules,
  - configure data-plane tables/actions,
  - set registers,
  - adjust runtime parameters (e.g., LPF-related settings),
  - manage AGILE runtime control logic.

### Scripts

- `build.sh`  
  1. **Compile the data-plane P4 program (`fsmmf.p4`)**
  2. **Generate PD interface helper files** for both data-plane and control-plane programming
  3. **Compile the C++ control-plane implementation (`fsmmf.cpp`)**

- `run.sh`  
  Launch the switch runtime.  

- `controlplane.sh`  
  Starts the control plane to configure forwarding and AGILE-related rules.

---
## Building and Running
### Build
To build both the data plane and control plane, run:

```bash
./build.sh
```
After the build completes, compiled data-plane artifacts will be available in the fsmmf/ directory.

### Run the Switch
To launch the switch with AGILE:
```bash
./run.sh
```

### Start the Control Plane
After the switch starts and **gRPC becomes available**, start the control plane:
```bash
./controlplane.sh
```
## Notes
Some parameters (e.g., LPF settings) may need adjustment depending on the experimental setup.

Note: The internal development codename for the AGILE project is 'fsmmf'. All source files use the fsmmf prefix.
