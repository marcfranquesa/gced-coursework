#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using LLI = long long int;
using VI = vector<LLI>;

VI DP;

LLI catalan_number(int n){
    LLI& res = DP[n];
    if (res > -1) return res;

    if (n == 0) return res = 1;
    if (n == 1) return res = 0;

    LLI total = 0;
    for (int i = 0; i < n - 1; ++i){
        total += catalan_number(n-i-2) * catalan_number(i);
    }
    return res = total;
}


int main(){
    int n;
    DP = VI(67 + 1, -1);
    while (cin >> n){
        cout << catalan_number(n) << endl;
    }
}