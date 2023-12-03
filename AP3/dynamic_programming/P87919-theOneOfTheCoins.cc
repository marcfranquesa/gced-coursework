#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;

VI coins;
VI DP;

bool search(int A){
    if (A < 0) return false;
    if (A == 0) return true;
    if (DP[A] == -1) return false;
    if (DP[A] > 0) return true;

    for (int i = coins.size() - 1; i >= 0; --i){
        if (search(A - coins[i])){
            DP[A] = A - coins[i];
            return true;
        }
    }
    DP[A] = -1;
    return false;
}


int main(){
    int n, A;
    while (cin >> n){
        coins = VI(n);
        for (int i = 0; i < n; ++i) cin >> coins[i];
        sort(coins.begin(), coins.end());
        cin >> A;
        DP = VI(A+1, -2);

        if (not search(A)) cout << -1 << endl;
        else {
            cout << A - DP[A];
            A = DP[A];
            while (DP[A] != -2){
                cout << ',' << A - DP[A];
                A = DP[A];
            }
            cout << endl;
        }
    }
}