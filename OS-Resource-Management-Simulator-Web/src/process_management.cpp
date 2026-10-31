#include "process_management.h"
#include <iomanip>
#include <iostream>
#include <string>
namespace {
enum class State{NEW,READY,RUNNING,WAITING,TERMINATED};
std::string name(State s){switch(s){case State::NEW:return"NEW";case State::READY:return"READY";case State::RUNNING:return"RUNNING";case State::WAITING:return"WAITING";case State::TERMINATED:return"TERMINATED";}return"UNKNOWN";}
}
void processManagementMenu(){
    std::cout<<"\n========== PROCESS MANAGEMENT ==========\n\n";
    std::cout<<"Process State Model\n\nNEW -> READY -> RUNNING -> TERMINATED\n                    |\n                    v\n                 WAITING\n                    |\n                    +----> READY\n\n";
    std::cout<<std::left<<std::setw(18)<<"State"<<"Description\n"<<std::string(72,'-')<<"\n";
    std::cout<<std::setw(18)<<name(State::NEW)<<"Process has been created.\n";
    std::cout<<std::setw(18)<<name(State::READY)<<"Process is waiting for CPU execution.\n";
    std::cout<<std::setw(18)<<name(State::RUNNING)<<"Process is currently executing on the CPU.\n";
    std::cout<<std::setw(18)<<name(State::WAITING)<<"Process is waiting for an event or resource.\n";
    std::cout<<std::setw(18)<<name(State::TERMINATED)<<"Process has completed execution.\n";
}
