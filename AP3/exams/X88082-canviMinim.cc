#include <iostream>
#include <vector>
#include <map>
using namespace std;

using VI = vector<int>;
using DP = VI;

VI coins;
DP dp;

int search(int c){
    int& candidate = dp[c];
    if (candidate != -1) return candidate;

    candidate = 1e6;
    for (int coin : coins){
        if (coin <= c)
            candidate = min(candidate, 1 + search(c - coin));
    }

    return candidate;
}

int main(){
    int n, c;

    while (cin >> c >> n){
        coins = VI(n);
        dp = DP(c + 1, -1);
        dp[0] = 0;

        for (int& coin : coins) {
            cin >> coin;
        }

        int i = search(c);

        if (i == 1e6) cout << "no" << endl;
        else cout << i << endl;
    }
}