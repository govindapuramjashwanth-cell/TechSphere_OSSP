#ifndef CPU_SCHEDULING_H
#define CPU_SCHEDULING_H
#include <vector>
struct Process {
    int pid{};
    int arrivalTime{};
    int burstTime{};
    int priority{};
    int memoryRequired{};
    int remainingTime{};
    int completionTime{};
    int turnaroundTime{};
    int waitingTime{};
    int responseTime{-1};
    bool started{false};
    bool completed{false};
};
struct GanttEntry { int pid{}; int startTime{}; int endTime{}; };
void cpuSchedulingMenu();
void fcfs(std::vector<Process> processes);
void sjf(std::vector<Process> processes);
void priorityScheduling(std::vector<Process> processes);
void roundRobin(std::vector<Process> processes, int quantum);
#endif
