#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

using VB = vector<bool>;

VVI graph;
VB visited;


int search(int from, int last){
    int m = 0;
    for (int to = 0; to < last; ++to){
        if (not visited[to]){
            visited[to] = true;
            m = max(m, search(to, last) + graph[from][to]);
            visited[to] = false;
        }
    }
    return m;
}


int main(){
    int n, x;
    while (cin >> n){
        graph = VVI(n, VI(n));
        visited = VB(n, false);

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cin >> graph[i][j];
            }
        }

        cin >> x;
        visited[x] = true;

        cout << search(x, n) << endl;
    }
}