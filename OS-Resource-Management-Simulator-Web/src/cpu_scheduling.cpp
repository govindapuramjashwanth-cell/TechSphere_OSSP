#include "cpu_scheduling.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {
void resetProcesses(std::vector<Process>& p) {
    for (auto& x : p) {
        x.remainingTime=x.burstTime; x.completionTime=0; x.turnaroundTime=0;
        x.waitingTime=0; x.responseTime=-1; x.started=false; x.completed=false;
    }
}
void sortByArrival(std::vector<Process>& p) {
    std::stable_sort(p.begin(),p.end(),[](const Process&a,const Process&b){
        if(a.arrivalTime!=b.arrivalTime) return a.arrivalTime<b.arrivalTime;
        return a.pid<b.pid;
    });
}
void printGanttChart(const std::vector<GanttEntry>& g) {
    if(g.empty()) return;
    std::cout<<"\nGantt Chart\n ";
    for(std::size_t i=0;i<g.size();++i) std::cout<<"--------";
    std::cout<<"-\n|";
    for(const auto& e:g) std::cout<<"  P"<<e.pid<<"  |";
    std::cout<<"\n ";
    for(std::size_t i=0;i<g.size();++i) std::cout<<"--------";
    std::cout<<"-\n"<<g.front().startTime;
    for(const auto& e:g) std::cout<<std::setw(9)<<e.endTime;
    std::cout<<"\n";
}
void printMetrics(const std::vector<Process>& p) {
    std::cout<<"\n"<<std::left<<std::setw(8)<<"PID"<<std::setw(8)<<"AT"
             <<std::setw(8)<<"BT"<<std::setw(10)<<"Priority"<<std::setw(8)<<"CT"
             <<std::setw(8)<<"TAT"<<std::setw(8)<<"WT"<<std::setw(8)<<"RT"<<"\n";
    std::cout<<std::string(66,'-')<<"\n";
    double wt=0,tat=0,rt=0;
    for(const auto& x:p){
        std::cout<<std::left<<std::setw(8)<< ("P"+std::to_string(x.pid))
                 <<std::setw(8)<<x.arrivalTime<<std::setw(8)<<x.burstTime
                 <<std::setw(10)<<x.priority<<std::setw(8)<<x.completionTime
                 <<std::setw(8)<<x.turnaroundTime<<std::setw(8)<<x.waitingTime
                 <<std::setw(8)<<x.responseTime<<"\n";
        wt+=x.waitingTime; tat+=x.turnaroundTime; rt+=x.responseTime;
    }
    std::cout<<std::fixed<<std::setprecision(2)
             <<"\nAverage Waiting Time    : "<<wt/p.size()
             <<"\nAverage Turnaround Time : "<<tat/p.size()
             <<"\nAverage Response Time   : "<<rt/p.size()<<"\n";
}
}
void fcfs(std::vector<Process> p){
    sortByArrival(p); resetProcesses(p); std::vector<GanttEntry> g; int t=0;
    for(auto& x:p){ if(t<x.arrivalTime)t=x.arrivalTime; int s=t;
        x.responseTime=t-x.arrivalTime; t+=x.burstTime; x.completionTime=t;
        x.turnaroundTime=t-x.arrivalTime; x.waitingTime=x.turnaroundTime-x.burstTime;
        x.completed=true; g.push_back({x.pid,s,t});
    }
    std::cout<<"\n========== FCFS ==========\n"; printGanttChart(g); printMetrics(p);
}
void sjf(std::vector<Process> p){
    resetProcesses(p); std::vector<GanttEntry> g; int done=0,t=0,n=p.size();
    while(done<n){int s=-1;
        for(int i=0;i<n;++i) if(!p[i].completed&&p[i].arrivalTime<=t)
            if(s==-1||p[i].burstTime<p[s].burstTime||
               (p[i].burstTime==p[s].burstTime&&p[i].arrivalTime<p[s].arrivalTime)||
               (p[i].burstTime==p[s].burstTime&&p[i].arrivalTime==p[s].arrivalTime&&p[i].pid<p[s].pid)) s=i;
        if(s==-1){++t;continue;} auto&x=p[s]; int st=t; x.responseTime=t-x.arrivalTime;
        t+=x.burstTime;x.completionTime=t;x.turnaroundTime=t-x.arrivalTime;
        x.waitingTime=x.turnaroundTime-x.burstTime;x.completed=true;g.push_back({x.pid,st,t});++done;
    }
    std::cout<<"\n========== SJF (NON-PREEMPTIVE) ==========\n";printGanttChart(g);printMetrics(p);
}
void priorityScheduling(std::vector<Process> p){
    resetProcesses(p); std::vector<GanttEntry> g; int done=0,t=0,n=p.size();
    while(done<n){int s=-1;
        for(int i=0;i<n;++i) if(!p[i].completed&&p[i].arrivalTime<=t)
            if(s==-1||p[i].priority<p[s].priority||
               (p[i].priority==p[s].priority&&p[i].arrivalTime<p[s].arrivalTime)||
               (p[i].priority==p[s].priority&&p[i].arrivalTime==p[s].arrivalTime&&p[i].pid<p[s].pid)) s=i;
        if(s==-1){++t;continue;} auto&x=p[s];int st=t;x.responseTime=t-x.arrivalTime;t+=x.burstTime;
        x.completionTime=t;x.turnaroundTime=t-x.arrivalTime;x.waitingTime=x.turnaroundTime-x.burstTime;
        x.completed=true;g.push_back({x.pid,st,t});++done;
    }
    std::cout<<"\n========== PRIORITY (NON-PREEMPTIVE) ==========\nLower priority number = higher priority.\n";
    printGanttChart(g);printMetrics(p);
}
void roundRobin(std::vector<Process> p,int q){
    if(q<=0){std::cout<<"Time quantum must be greater than zero.\n";return;}
    resetProcesses(p);sortByArrival(p);std::vector<GanttEntry>g;std::vector<int>rq;
    int next=0,done=0,t=0,n=p.size();
    while(done<n){
        while(next<n&&p[next].arrivalTime<=t)rq.push_back(next++);
        if(rq.empty()){if(next<n)t=p[next].arrivalTime;continue;}
        int i=rq.front();rq.erase(rq.begin());auto&x=p[i];
        if(!x.started){x.responseTime=t-x.arrivalTime;x.started=true;}
        int st=t,run=std::min(q,x.remainingTime);t+=run;x.remainingTime-=run;g.push_back({x.pid,st,t});
        while(next<n&&p[next].arrivalTime<=t)rq.push_back(next++);
        if(x.remainingTime>0)rq.push_back(i);
        else{x.completed=true;x.completionTime=t;x.turnaroundTime=t-x.arrivalTime;
             x.waitingTime=x.turnaroundTime-x.burstTime;++done;}
    }
    std::cout<<"\n========== ROUND ROBIN ==========\nTime Quantum: "<<q<<"\n";printGanttChart(g);printMetrics(p);
}
void cpuSchedulingMenu(){
    int n;std::cout<<"\n========== CPU SCHEDULING ==========\nEnter number of processes: ";std::cin>>n;
    if(!std::cin||n<=0){std::cout<<"Invalid number of processes.\n";return;}
    std::vector<Process>p(n);
    for(int i=0;i<n;++i){p[i].pid=i+1;std::cout<<"\nProcess P"<<i+1<<"\nArrival Time : ";std::cin>>p[i].arrivalTime;
        std::cout<<"Burst Time   : ";std::cin>>p[i].burstTime;std::cout<<"Priority     : ";std::cin>>p[i].priority;
        std::cout<<"Memory Req.  : ";std::cin>>p[i].memoryRequired;
        if(!std::cin||p[i].arrivalTime<0||p[i].burstTime<=0||p[i].memoryRequired<0){std::cout<<"Invalid process data.\n";return;}}
    int c;std::cout<<"\n1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. Back\nEnter choice: ";std::cin>>c;
    switch(c){case 1:fcfs(p);break;case 2:sjf(p);break;case 3:priorityScheduling(p);break;case 4:{int q;std::cout<<"Enter Time Quantum: ";std::cin>>q;roundRobin(p,q);break;}case 5:break;default:std::cout<<"Invalid choice.\n";}
}
