#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int b;
    int w;
};

bool operator<(const Edge& e1, const Edge& e2){
        return e1.w > e2.w;
}

using Graph = vector<vector<Edge>>;

Graph read_graph(int n, int m){
    Graph g(n);
    int u, v, w;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> w; u-=1; v-=1;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    return g;
}

void show_queue(priority_queue<Edge> pq){{}
    while(not pq.empty()){
        Edge e = pq.top(); pq.pop();
        cout << '(' << e.b + 1 << ',' << e.w << ") "<< endl;
    }
    cout << endl;
}

int weight(const Graph g, int n){
    vector<bool> visited(n, false);
    visited[0] = true;
    int weight = 0;

    priority_queue<Edge> pq;
    for (Edge e : g[0]) pq.push(e);
    int i = 1;
    while(i < n){
        //show_queue(pq);
        Edge e = pq.top(); pq.pop();
        if (not visited[e.b]){
            visited[e.b] = true;
            weight += e.w;
            i+=1;
            //cout <<' ' << e.b + 1 << ' ' << e.w << endl;

            for (Edge e1 : g[e.b]){
                if (not visited[e1.b]) pq.push(e1);
            }
        }

    }
    return weight;

}

int main(){
    int n, m;
    while(cin >> n >> m){
        Graph g = read_graph(n, m);
        cout << weight(g, n) << endl;
    }


}