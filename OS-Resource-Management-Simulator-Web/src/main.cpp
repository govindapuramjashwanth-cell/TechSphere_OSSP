#include <iostream>
#include "banker.h"
#include "cpu_scheduling.h"
#include "memory_management.h"
#include "process_management.h"

void menu(){
    std::cout<<"\n====================================================\n"
             <<"          OS RESOURCE MANAGEMENT SIMULATOR\n"
             <<"====================================================\n"
             <<"1. CPU Scheduling\n"
             <<"2. Memory Management\n"
             <<"3. Process Management\n"
             <<"4. Resource Allocation / Banker's Algorithm\n"
             <<"5. Exit\n"
             <<"====================================================\n";
}
int main(){
    int c;
    do{
        menu();std::cout<<"Enter your choice: ";std::cin>>c;
        if(!std::cin){std::cin.clear();std::cin.ignore(10000,'\n');std::cout<<"Invalid input.\n";continue;}
        switch(c){case 1:cpuSchedulingMenu();break;case 2:memoryManagementMenu();break;case 3:processManagementMenu();break;case 4:bankerMenu();break;case 5:std::cout<<"Exiting simulator...\n";break;default:std::cout<<"Invalid choice.\n";}
    }while(c!=5);
    return 0;
}
