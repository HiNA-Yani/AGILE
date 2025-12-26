# AGILE: Achieving Max-Min Fairness and High Utilization for In-Network Bandwidth Allocation
This repository hosts the prototype implementation of our INFOCOM 2026 paper:

**AGILE: Achieving Max-Min Fairness and High Utilization for In-Network Bandwidth Allocation**

AGILE is an in-network bandwidth allocation system that achieves **max-min fairness** while maintaining **high link utilization**, by leveraging programmable switches. The system is implemented and evaluated on **Barefoot Tofino-1 switches** using **BF-SDE 9.11**.

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
``bash
./run.sh
```

### Start the Control Plane
After the switch is running, start the control plane:
``bash
./controlplane.sh
```
## Notes
Some parameters may need adjustment depending on the experimental setup.
