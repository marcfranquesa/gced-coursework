#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

VI costs;
VVI DP;

int distance(int pos1, int pos2, const string& s1, const string& s2, const VI& costs){
    int& res = DP[pos1][pos2]; if (res > -1) return res;
    if (pos1 == s1.size()){
        int remaining = 0;
        for (int i = pos2; i < s2.size(); ++i) remaining += costs[s2[i] - 'a'];
        return res = remaining;
    }
    if (pos2 == s2.size()){
        int remaining = 0;
        for (int i = pos1; i < s1.size(); ++i) remaining += costs[s1[i] - 'a'];
        return res = remaining;
    }

    if (s1[pos1] == s2[pos2]) return res = distance(pos1 + 1, pos2 + 1, s1, s2, costs);

    return res = min(
        distance(pos1 + 1, pos2, s1, s2, costs) + costs[s1[pos1] - 'a'],
        distance(pos1, pos2 + 1, s1, s2, costs) + costs[s2[pos2] - 'a']
    );
}


int main(){
    int n;
    string s1, s2;
    while (cin >> n){
        costs = VI(n); for (int& cost : costs) cin >> cost;
        cin >> s1 >> s2;
        DP = VVI(s1.size() + 1, VI(s2.size() + 1, -1));
        cout << distance(0, 0, s1, s2, costs) << endl;
    }
}