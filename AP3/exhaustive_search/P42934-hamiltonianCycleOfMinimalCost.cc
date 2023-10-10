#include <iostream>
#include <vector>
using namespace std;

using VI = vector<int>;
using VB = vector<bool>;
using VII = vector<VI>;


VII costs;


void read_costs(int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> costs[i][j];
        }
    }
}


void find(int pos, int latest, VI& cycle, int cost, int& lowest_cost, int n){
    if (cost > lowest_cost) return;

    if (pos == n && ((cost + costs[latest][0]) < lowest_cost)){
        lowest_cost = cost + costs[latest][0];
        return;
    }

    for (int i = 0; i < n; ++i){
        if (cycle[i] == -1 and latest != i){
            cycle[latest] = i;
            find(pos + 1, i, cycle, cost + costs[latest][i], lowest_cost, n);
            cycle[latest] = -1;
        }
    }
}


int main(){
    int n; 
    while(cin >> n){
        VI cycle(n, -1);

        costs = VII(n, VI(n, -1));
        int lowest_cost = 1e9;
        
        read_costs(n);
        find(1, 0, cycle, 0, lowest_cost, n);

        cout << lowest_cost << endl;
    }
}