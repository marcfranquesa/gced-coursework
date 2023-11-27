#include <vector>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

const int INF = 1e6;


struct Edge {
    int node;
    int weight;
};

bool operator< (const Edge& e1, const Edge& e2){
    return e1.weight > e2.weight;
}

using Graph = vector<vector<Edge>>;

Graph read_graph(int n, int m){
    Graph g(n);
    int u, v, w;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    return g;
}

int dijkstra (const Graph& g, int source, int sink){

    vector<int> cost(g.size(), INF);
    priority_queue<Edge> tentative; tentative.push({source, 0});

    while(not tentative.empty()){

        Edge u = tentative.top(); tentative.pop();

        if (cost[u.node] == INF) {
            if (u.node == sink) return u.weight;

            cost[u.node] = u.weight;
            for(Edge e : g[u.node]){
                tentative.push({e.node, cost[u.node] + e.weight});
            }
        }
    }

    return cost[sink];
}




int main() {
    int n, m;
    while(cin >> n >> m){
        Graph g = read_graph(n, m);
        int source, sink; cin >> source >> sink;
        int weight = dijkstra(g, source, sink);
        weight < INF ? cout << weight << endl :
        cout << "no path from "<< source <<" to "<< sink << endl;
    }
}