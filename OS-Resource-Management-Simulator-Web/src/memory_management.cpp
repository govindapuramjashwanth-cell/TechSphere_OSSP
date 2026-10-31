#include "memory_management.h"
#include <iomanip>
#include <iostream>
#include <string>
namespace {
MemoryAllocationResult makeResult(const std::vector<int>&b,const std::vector<int>&p){
    MemoryAllocationResult r;r.allocation.assign(p.size(),-1);r.remainingBlocks=b;
    for(int x:b) r.totalMemory+=x;
    for(int x:p) r.requestedMemory+=x;
    return r;
}
void finish(MemoryAllocationResult&r){if(r.totalMemory>0)r.utilization=100.0*r.allocatedMemory/r.totalMemory;}
void print(const std::vector<int>&p,const MemoryAllocationResult&r,const std::string&name){
    std::cout<<"\n========== "<<name<<" ==========\n"<<std::left<<std::setw(12)<<"Process"<<std::setw(18)<<"Required(KB)"<<std::setw(16)<<"Allocation"<<"\n"<<std::string(46,'-')<<"\n";
    for(size_t i=0;i<p.size();++i){std::cout<<std::left<<std::setw(12)<< ("P"+std::to_string(i+1))<<std::setw(18)<<p[i];
        std::cout<<std::setw(16)<<(r.allocation[i]<0?"Not Allocated":"Block "+std::to_string(r.allocation[i]+1))<<"\n";}
    std::cout<<"\nRemaining Blocks:\n";for(size_t i=0;i<r.remainingBlocks.size();++i)std::cout<<"Block "<<i+1<<" : "<<r.remainingBlocks[i]<<" KB\n";
    std::cout<<std::fixed<<std::setprecision(2)<<"\nTotal Memory      : "<<r.totalMemory<<" KB\nRequested Memory  : "<<r.requestedMemory<<" KB\nAllocated Memory  : "<<r.allocatedMemory<<" KB\nMemory Utilization: "<<r.utilization<<"%\n";
}}
MemoryAllocationResult firstFit(const std::vector<int>&b,const std::vector<int>&p){auto r=makeResult(b,p);for(size_t i=0;i<p.size();++i)for(size_t j=0;j<r.remainingBlocks.size();++j)if(r.remainingBlocks[j]>=p[i]){r.allocation[i]=j;r.remainingBlocks[j]-=p[i];r.allocatedMemory+=p[i];break;}finish(r);return r;}
MemoryAllocationResult bestFit(const std::vector<int>&b,const std::vector<int>&p){auto r=makeResult(b,p);for(size_t i=0;i<p.size();++i){int k=-1;for(size_t j=0;j<r.remainingBlocks.size();++j)if(r.remainingBlocks[j]>=p[i]&&(k<0||r.remainingBlocks[j]<r.remainingBlocks[k]))k=j;if(k>=0){r.allocation[i]=k;r.remainingBlocks[k]-=p[i];r.allocatedMemory+=p[i];}}finish(r);return r;}
MemoryAllocationResult worstFit(const std::vector<int>&b,const std::vector<int>&p){auto r=makeResult(b,p);for(size_t i=0;i<p.size();++i){int k=-1;for(size_t j=0;j<r.remainingBlocks.size();++j)if(r.remainingBlocks[j]>=p[i]&&(k<0||r.remainingBlocks[j]>r.remainingBlocks[k]))k=j;if(k>=0){r.allocation[i]=k;r.remainingBlocks[k]-=p[i];r.allocatedMemory+=p[i];}}finish(r);return r;}
void memoryManagementMenu(){
    int nb;std::cout<<"\n========== MEMORY MANAGEMENT ==========\nEnter number of memory blocks: ";std::cin>>nb;if(!std::cin||nb<=0){std::cout<<"Invalid number of blocks.\n";return;}
    std::vector<int>b(nb);for(int i=0;i<nb;++i){std::cout<<"Block "<<i+1<<" size (KB): ";std::cin>>b[i];if(!std::cin||b[i]<=0){std::cout<<"Invalid block size.\n";return;}} 
    int np;std::cout<<"Enter number of memory requests: ";std::cin>>np;if(!std::cin||np<=0){std::cout<<"Invalid number of requests.\n";return;}
    std::vector<int>p(np);for(int i=0;i<np;++i){std::cout<<"P"<<i+1<<" memory requirement (KB): ";std::cin>>p[i];if(!std::cin||p[i]<=0){std::cout<<"Invalid memory requirement.\n";return;}}
    int c;std::cout<<"\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Back\nEnter choice: ";std::cin>>c;MemoryAllocationResult r;
    switch(c){case 1:r=firstFit(b,p);print(p,r,"FIRST FIT");break;case 2:r=bestFit(b,p);print(p,r,"BEST FIT");break;case 3:r=worstFit(b,p);print(p,r,"WORST FIT");break;case 4:break;default:std::cout<<"Invalid choice.\n";}
}
