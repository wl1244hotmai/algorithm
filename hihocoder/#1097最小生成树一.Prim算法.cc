#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

struct edge{
    int s = 0;
    int e = 0;
    int value = 0;
    edge(int _s,int _e,int _value):s(_s), e(_e), value(_value){}
};

class comparasion{
    public:
    bool operator()(edge& e1,edge& e2){
        return e1.value>e2.value;
    }
};

int getShorest(vector<vector<edge> >& edges){
    vector<bool> visit(edges.size());
    priority_queue<edge,vector<edge>,comparasion> shortest_pri;
    int this_visit = 0;
    int shortest = 0;
    visit[0] = true;
    edge this_edge(0,0,0);
    while(find(visit.begin(),visit.end(),false) != visit.end()){
            for_each(edges[this_visit].begin(),edges[this_visit].end(),[&](edge e){
                if(e.value!=0 && !visit[e.e]){
                    shortest_pri.push(e);
                }
            });
            while(shortest_pri.size()!=0){
                this_edge = shortest_pri.top();
                shortest_pri.pop();
                if(!visit[this_edge.e]) break;
            }

            visit[this_edge.e] = true;
            this_visit = this_edge.e;
            shortest+=this_edge.value;
    }
    return shortest;
}

int main(){
    int n;
    cin>>n;
    vector<vector<edge> > edges(n);
    int edge_value;
    for(int i = 0;i<n;i++){
        for(int j=0 ;j<n;j++){
            cin>>edge_value;
            edges[i].push_back(edge(i,j,edge_value));
        }
    }
    cout<<getShorest(edges);
    return 0;
}
