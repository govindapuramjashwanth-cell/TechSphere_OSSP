#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H
#include <vector>
struct MemoryAllocationResult {
    std::vector<int> allocation;
    std::vector<int> remainingBlocks;
    int requestedMemory{};
    int allocatedMemory{};
    int totalMemory{};
    double utilization{};
};
MemoryAllocationResult firstFit(const std::vector<int>&,const std::vector<int>&);
MemoryAllocationResult bestFit(const std::vector<int>&,const std::vector<int>&);
MemoryAllocationResult worstFit(const std::vector<int>&,const std::vector<int>&);
void memoryManagementMenu();
#endif
