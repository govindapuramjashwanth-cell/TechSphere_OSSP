# Build and Test

## Build
Run from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    src/main.cpp src/cpu_scheduling.cpp src/memory_management.cpp \
    src/banker.cpp src/process_management.cpp -Iinclude -o os_simulator
```

## Run
```bash
./os_simulator
```

## Suggested CPU test
Use 4 processes:
- P1: AT=0, BT=5, Priority=2
- P2: AT=1, BT=3, Priority=1
- P3: AT=2, BT=8, Priority=3
- P4: AT=3, BT=6, Priority=2

Test FCFS, SJF, Priority, and Round Robin (quantum 2).

## Suggested memory test
Blocks: 100, 500, 200, 300, 600 KB
Requests: 212, 417, 112, 426 KB

Test First Fit, Best Fit, and Worst Fit.

## Banker's test
Use the matrices in README.md. The state should be reported safe.
