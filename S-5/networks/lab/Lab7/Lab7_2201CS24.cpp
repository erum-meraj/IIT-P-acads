#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <bits/stdc++.h>

using namespace std;

struct rtentry {                
    string dst;                
    string nhp;                
    int cost;                  
};

// Structure for representation of each router
struct Router {                
    string name;              
    vector<rtentry> rttable;    
    queue<pair<string,vector<rtentry>>>shq;   
    vector<string> nbrs;              
};

const int inf=1e9;                 
int n;                             
vector<string>rtnms;               
map<pair<string,string>,int>cst;   
map<string,vector<string>>ad;      
map<string,int>vi;               
vector<thread>th;                  
vector<Router>rts;                
map<string,int>ind;               
mutex mtx;

void dfs(string x){
    vi[x]=1;
    for(auto it:ad[x]){
        if(!vi[it]){dfs(it);}
    }
}
void cmpt(Router* x);

int main(){
    freopen("topology.txt", "r", stdin);
    cin>>n;
    rtnms.clear();rtnms.resize(n);
    rts.clear();rts.resize(n);
    for(int i=0;i<n;i++){
        cin>>rtnms[i];vi[rtnms[i]]=0;
        rts[i].name=rtnms[i];
        rts[i].rttable.clear();
        rts[i].nbrs.clear();
        ind[rts[i].name]=i;
    }
    for(int i=0;i<1e9;i++){
        string x,y; int di;
        cin>>x;
        if(x=="END"){break;}
        cin>>y>>di;
        ad[x].push_back(y);
        ad[y].push_back(x);
        cst[{x,y}]=di;
        cst[{y,x}]=di;
    }

// To check if the network is connected or not

int c=0;  // c is count of no of connected components
for(auto it:rtnms){
    if(!vi[it]){dfs(it);c++;}
}
if(c>1){
    cout<<"It is a disconnected network.So quitting the program\n";
    exit(0);
}

// The network is connected
th.clear();th.resize(n);
for(int i=0;i<n;i++){
        // Get the names  of neighbours for each router
        for(auto it:ad[rts[i].name]){
            rts[i].nbrs.push_back(it);
        }
        // Initialise the routing table of each router
        for(int j=0;j<n;j++){
            rtentry x;
            x.dst=rts[j].name;
            x.nhp="-";
            x.cost=inf;
            if(i==j){
                 x.nhp=x.dst;
                 x.cost=0;
             }
             bool fnd=false;
             for(auto it:rts[i].nbrs){
                if(it==rts[j].name){fnd=true;break;}
            }
            if(fnd){x.cost=cst[{rts[i].name,rts[j].name}];x.nhp=rts[j].name;}
            rts[i].rttable.push_back(x);
        }
    }
    cout<<"Initial Status of each router \t\n";
    for(int i=0;i<n;i++){
        cout<<"Router"<<" "<<rts[i].name<<" \t\n";
        cout<<"Destination"<<" \t"<<"Next Hop"<<" \t"<<"Cost\n";
        for(auto it:rts[i].rttable){
            cout<<it.dst<<" \t::"<<it.nhp<<" \t::"<<it.cost<<"\n";
        }
    }
    cout<<"________________________________________________________\n\n";
    for(int i=0;i<n;i++){
     th[i] = thread(cmpt,&rts[i]);
    }

    for(int i=0;i<n;i++){
     th[i].join();
    }

    return 0;
}


void cmpt(Router* x) {
    int iteration=1;
    // after each 3 sec , each router should forward its routing table to neighbours
    for(int i=0;i<n;i++){
        for(auto it:x->nbrs){
            rts[ind[it]].shq.push({x->name,x->rttable});
        }
        std::this_thread::sleep_for(chrono::seconds(2));
    //After 2 sec from previous computation , the router should start new computation
    // check if you have recieved routing tables from all neighbouring routers

        if(x->shq.size()==x->nbrs.size() && !x->shq.empty()){
        // now compute routing table and update it
           vector<int>chngd(n,0);
           while(!x->shq.empty()){
            pair<string,vector<rtentry>>p=x->shq.front();
            x->shq.pop();
            for(int j=0;j<n;j++){
                rtentry te =x->rttable[j];
                int di1=te.cost;
                string wh=p.first;
                for(auto it:p.second){
                    if(it.dst==rts[j].name){
                        if(di1>x->rttable[ind[wh]].cost+it.cost){
                          x->rttable[j].cost= x->rttable[ind[wh]].cost+it.cost;
                          x->rttable[j].nhp=wh;
                          chngd[j]=1;
                      }
                  }
              }
          }

      }
      mtx.lock();
      cout<<"Routing Table of "<<x->name<<"\tIteration: "<<iteration<<" \t\n";
      cout<<"Destination"<<"  "<<"Next Hop"<<"   "<<"Cost\n";
      for(int i=0;i<n;i++){
        cout<<x->rttable[i].dst;
        if(chngd[i]){cout<<"*      ::    ";}
        else{cout<<"      ::      ";}
        cout<<x->rttable[i].nhp<<"      ::      ";
        cout<<x->rttable[i].cost<<"        \n";

    }
    mtx.unlock();
}
iteration++;
std::this_thread::sleep_for(chrono::seconds(3));
}
}