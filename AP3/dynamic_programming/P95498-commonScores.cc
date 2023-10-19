#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

VI A, B;
VVI dp;


int find_length_longest_common_subsequence(int posA, int posB, int m, int n){
    if (posA == m or posB == n) return 0;

    int& res = dp[posA][posB];
    if (res > -1) return res;
    

    return res = max(
        (int)(A[posA] == B[posB]) + find_length_longest_common_subsequence(posA + 1, posB + 1, m, n),
        max(
            find_length_longest_common_subsequence(posA, posB + 1, m, n),
            find_length_longest_common_subsequence(posA + 1, posB, m, n)
        )
    );
}

int main(){
    int m, n;
    while (cin >> m >> n){
        A = VI(m); for (int& points : A) cin >> points;
        B = VI(n); for (int& points : B) cin >> points;
        dp = VVI(m, VI(n, -1));
        
        cout << find_length_longest_common_subsequence(0, 0, m, n) << endl;
    }
}