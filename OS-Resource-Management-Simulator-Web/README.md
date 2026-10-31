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

