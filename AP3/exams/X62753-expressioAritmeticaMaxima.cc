#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using VD = vector<double>;
using VVD = vector<VD>;


VD numbers;
VVD DP;

const int UNDEF = -1;


double find_max_expression(int begin, int end){
    // cout << begin << ' ' << end << endl;
    double& res = DP[begin][end];

    if (res != UNDEF) return res;

    if (begin == end) return res = numbers[begin];

    for (int i = begin; i < end; ++i){
        res = max(
            res,
            max(
                find_max_expression(begin, i) + find_max_expression(i + 1, end),
                find_max_expression(begin, i) * find_max_expression(i + 1, end)
            )
        );
    }

    return res;

}


int main(){
    cout.setf(ios::fixed);
    cout.precision(4);

    int n;

    while (cin >> n){
        numbers = VD(n);
        DP = VVD(n, VD(n, UNDEF));
        for (double& number : numbers) cin >> number;

        cout << find_max_expression(0, n - 1) << endl;
    }
}