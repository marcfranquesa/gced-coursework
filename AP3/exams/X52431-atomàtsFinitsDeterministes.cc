#include <iostream>
#include <vector>
using namespace std;

using VB = vector<bool>;
using VI = vector<int>;
using VVI = vector<VI>;


VVI adj;
VVI DP;
VI acceptance;

int main(){
    int n, m;
    cin >> n;

    adj = VVI(n);

    int dest;
    for (int digit = 0; digit < 2; ++ digit){
        for (int state = 0; state < n; ++state){
            cin >> dest;
            adj[dest].push_back(state);
        }
    }

    acceptance = VI(n);
    for (int& acc : acceptance) cin >> acc;

    cin >> m;

    DP = VVI(n, VI(m + 1, 0));

    for (int state = 0; state < n; ++state){
        DP[state][0] = acceptance[state];
    }
    cout << DP[0][0] << endl;

    for (int step = 1; step <= m; ++step){
        for (int to = 0; to < n; ++to){
            for (int from : adj[to]){
                DP[from][step] += DP[to][step - 1];
            }
        }
        cout << DP[0][step] << endl;
    }
}