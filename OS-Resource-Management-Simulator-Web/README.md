# OS Resource Management Simulator — Web Dashboard

A browser-based dashboard for the **OS Resource Management Simulator** project. It provides interactive demonstrations of:

- CPU Scheduling: FCFS, SJF, Priority Scheduling and Round Robin
- CPU metrics: Completion Time, Turnaround Time, Waiting Time and Response Time
- Memory Management: First Fit, Best Fit and Worst Fit
- Process Management: New, Ready, Running, Waiting and Terminated states
- Resource Allocation: Banker's Algorithm with Need Matrix and Safe/Unsafe State
- Gantt chart and allocation result visualization

The original C++ implementation is retained in `include/` and `src/`. The `web/` folder is the browser demonstration layer, so the faculty can open the simulator in Chrome/Safari without installing a web framework.

## Mac commands

### 1. Open Terminal and enter the project folder

```bash
cd ~/Downloads/OS-Resource-Management-Simulator-Web
```

If the folder is somewhere else, use `cd ` and drag the folder into Terminal.

### 2. Check Python

```bash
python3 --version
```

Python 3 is normally available on macOS. No Flask, Node.js or npm package is required.

### 3. Start the web dashboard

```bash
python3 run_web.py
```

Your browser should open automatically at:

```text
http://localhost:8000
```

If it does not open automatically, copy the address into Chrome/Safari.

### 4. Stop the dashboard

In Terminal press:

```text
Control + C
```

## Optional: run the original C++ console version

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp src/cpu_scheduling.cpp src/memory_management.cpp src/banker.cpp src/process_management.cpp -Iinclude -o os_simulator
./os_simulator
```

## Recommended faculty demonstration

1. Open Dashboard.
2. Open CPU Scheduling → load sample → run FCFS.
3. Change to Round Robin → set Time Quantum = 2 → run.
4. Explain the Gantt chart and WT/TAT/RT metrics.
5. Open Memory Management → compare First Fit, Best Fit and Worst Fit.
6. Open Process Management → select a process and advance its state.
7. Open Banker's Algorithm → load safe sample → show Allocation, Maximum, Available and calculated Need Matrix.
8. Explain the Safe Sequence and why the state is safe.

## Folder structure

```text
OS-Resource-Management-Simulator-Web/
├── include/                         # C++ header files
│   ├── banker.h
│   ├── cpu_scheduling.h
│   ├── memory_management.h
│   └── process_management.h
├── src/                             # C++ implementation
│   ├── main.cpp
│   ├── banker.cpp
│   ├── cpu_scheduling.cpp
│   ├── memory_management.cpp
│   └── process_management.cpp
├── web/                             # Browser dashboard
│   ├── index.html
│   ├── css/
│   │   └── styles.css
│   └── js/
│       ├── app.js
│       └── algorithms/
│           ├── cpu.js
│           ├── memory.js
│           ├── banker.js
│           └── process.js
├── docs/
│   └── BUILD_AND_TEST.md
├── run_web.py                       # Local web server
└── README.md
```






<img width="1280" height="800" alt="Screenshot 2026-10-31 at 1 22 35 PM" src="https://github.com/user-attachments/assets/d0e771ff-a91a-4048-a521-7a6f3b001bd9" />
<img width="1280" height="800" alt="Screenshot 2026-10-31 at 1 23 01 PM" src="https://github.com/user-attachments/assets/3bf122cd-8357-46a1-97c4-8ce892ff44cb" />



## Test Cases

The following test cases are used to verify the functionality and correctness of the OS Resource Management Simulator. Each module is tested with different inputs to check whether the algorithms produce the expected results.

### 1. CPU Scheduling Test Cases

| Test Case ID | Test Scenario | Input / Condition | Expected Result |
|---|---|---|---|
| TC-01 | FCFS Scheduling | P1(AT=0, BT=4), P2(AT=0, BT=3), P3(AT=0, BT=2) | Execution order: P1 → P2 → P3 |
| TC-02 | SJF Scheduling | P1(BT=4), P2(BT=3), P3(BT=2), all AT=0 | Execution order: P3 → P2 → P1 |
| TC-03 | Priority Scheduling | P1(Priority=2), P2(Priority=1), P3(Priority=3), all AT=0 | Execution order: P2 → P1 → P3 |
| TC-04 | Round Robin | P1(BT=4), P2(BT=3), P3(BT=2), Time Quantum=2 | Processes execute in rotation until completion |
| TC-05 | Different Arrival Times | Processes with different arrival times | CPU execution follows process arrival and scheduling rules |
| TC-06 | Performance Calculation | Execute any scheduling algorithm | CT, TAT, WT and RT are calculated and displayed correctly |

### 2. Memory Management Test Cases

| Test Case ID | Test Scenario | Input / Condition | Expected Result |
|---|---|---|---|
| TC-07 | First Fit | Blocks: 100, 500, 200; Request: 150 | First suitable memory block is selected |
| TC-08 | Best Fit | Blocks: 100, 500, 200; Request: 150 | Smallest suitable memory block is selected |
| TC-09 | Worst Fit | Blocks: 100, 500, 200; Request: 150 | Largest suitable memory block is selected |
| TC-10 | Insufficient Memory | Process requests more memory than available | Process is reported as not allocated |
| TC-11 | Multiple Process Allocation | Multiple processes request different memory sizes | Allocation results are displayed for each process |

### 3. Process Management Test Cases

| Test Case ID | Test Scenario | Input / Condition | Expected Result |
|---|---|---|---|
| TC-12 | New Process | Select a process in NEW state | Process moves to READY state |
| TC-13 | Ready Process | Advance a process in READY state | Process moves to RUNNING state |
| TC-14 | Running Process | Advance a process in RUNNING state | Process moves to TERMINATED state |
| TC-15 | Waiting Process | Advance a process in WAITING state | Process returns to READY state |
| TC-16 | Terminated Process | Advance a terminated process | Process remains TERMINATED |
| TC-17 | Reset Process States | Click Reset States | Process cards return to their initial states |

### 4. Banker's Algorithm Test Cases

| Test Case ID | Test Scenario | Test Input / Condition | Expected Result |
|---|---|---|---|
| TC-18 | Safe State Detection | Enter a valid resource allocation with a safe sequence | System displays SAFE state |
| TC-19 | Unsafe State Detection | Enter resource values for which no safe sequence exists | System displays UNSAFE state |
| TC-20 | Need Matrix Calculation | Enter Allocation and Maximum matrices | Need Matrix is calculated as Maximum − Allocation |
| TC-21 | Available Resources | Enter available resource values | Safety algorithm uses the available resources correctly |
| TC-22 | Safe Sequence Generation | Run the algorithm with safe resource values | A valid safe execution sequence is displayed |

### 5. Web Application Test Cases

| Test Case ID | Test Scenario | Expected Result |
|---|---|---|
| TC-23 | Open Dashboard | Main dashboard loads successfully |
| TC-24 | Navigate Between Modules | Selected module opens correctly |
| TC-25 | Load Sample Data | Sample values are populated in the input fields |
| TC-26 | Run Simulation | Selected algorithm executes and displays results |
| TC-27 | Reset Inputs / States | Relevant inputs or process states return to their initial values |
| TC-28 | Invalid Input Handling | Invalid or incomplete inputs are handled appropriately without crashing the application |

### Testing Conclusion

The test cases cover the major functionalities of the OS Resource Management Simulator. They are designed to verify CPU scheduling algorithms, memory allocation techniques, process-state transitions, deadlock avoidance and web dashboard functionality.

Successful execution of these tests helps confirm that the application performs its intended educational simulations and displays the expected results.
