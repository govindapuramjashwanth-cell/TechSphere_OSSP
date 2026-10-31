#include "banker.h"
#include <iostream>
#include <string>
namespace {
std::vector<std::vector<int>> needOf(const std::vector<std::vector<int>>&a,const std::vector<std::vector<int>>&m){
    int n=a.size(),r=a[0].size();std::vector<std::vector<int>>nxt(n,std::vector<int>(r));
    for(int i=0;i<n;++i)
        for(int j=0;j<r;++j)
            nxt[i][j]=m[i][j]-a[i][j];
    return nxt;
}
void printMatrix(const std::vector<std::vector<int>>&m,const std::string&title){
    std::cout<<"\n"<<title<<"\n";for(size_t i=0;i<m.size();++i){std::cout<<"P"<<i+1<<" : ";for(int x:m[i])std::cout<<x<<" ";std::cout<<"\n";}
}
}
bool isSafe(const std::vector<std::vector<int>>&a,const std::vector<std::vector<int>>&m,const std::vector<int>&avail,std::vector<int>&seq){
    if(a.empty()||a.size()!=m.size()||avail.empty())
        return false;
    int n=a.size(),r=avail.size();
    for(int i=0;i<n;++i)if((int)a[i].size()!=r||(int)m[i].size()!=r)return false;
    auto need=needOf(a,m);auto work=avail;std::vector<bool>finish(n,false);seq.clear();
    while((int)seq.size()<n){bool found=false;for(int i=0;i<n;++i)if(!finish[i]){
        bool ok=true;for(int j=0;j<r;++j)if(need[i][j]>work[j]){ok=false;break;}
        if(ok){for(int j=0;j<r;++j)work[j]+=a[i][j];finish[i]=true;seq.push_back(i);found=true;}
    }if(!found)return false;}return true;
}
void bankerMenu(){
    int n,r;std::cout<<"\n========== RESOURCE ALLOCATION ==========\nEnter number of processes: ";std::cin>>n;std::cout<<"Enter number of resource types: ";std::cin>>r;
    if(!std::cin||n<=0||r<=0){std::cout<<"Invalid input.\n";return;}
    std::vector<std::vector<int>>a(n,std::vector<int>(r)),m(n,std::vector<int>(r));std::vector<int>av(r);
    std::cout<<"\nEnter Allocation Matrix:\n";for(int i=0;i<n;++i){std::cout<<"P"<<i+1<<": ";for(int j=0;j<r;++j)std::cin>>a[i][j];}
    std::cout<<"\nEnter Maximum Matrix:\n";for(int i=0;i<n;++i){std::cout<<"P"<<i+1<<": ";for(int j=0;j<r;++j)std::cin>>m[i][j];}
    std::cout<<"\nEnter Available Resources:\n";for(int&x:av)std::cin>>x;
    for(int i=0;i<n;++i)for(int j=0;j<r;++j)if(a[i][j]<0||m[i][j]<a[i][j]){std::cout<<"Invalid allocation/maximum data.\n";return;}
    for(int x:av)if(x<0){std::cout<<"Available resources cannot be negative.\n";return;}
    auto need=needOf(a,m);printMatrix(a,"ALLOCATION MATRIX");printMatrix(m,"MAXIMUM MATRIX");printMatrix(need,"NEED MATRIX");
    std::cout<<"\nAVAILABLE: ";for(int x:av)std::cout<<x<<" ";std::cout<<"\n";std::vector<int>seq;
    if(isSafe(a,m,av,seq)){std::cout<<"\nRESULT: SAFE STATE\nSafe Sequence: ";for(size_t i=0;i<seq.size();++i){std::cout<<"P"<<seq[i]+1;if(i+1<seq.size())std::cout<<" -> ";}std::cout<<"\n";}
    else std::cout<<"\nRESULT: UNSAFE STATE\nNo safe sequence exists for the current state.\n";
}
