#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;

VI DP;


int min_cards(int n, int depth){
    int& res = DP[n];
    if (res > -1) return res;

    if (n == 0) return res = 0;

    int min_found = min_cards(n-1, depth + 5);
    if (n > 4 and (min_cards(n-5, depth + 5) < min_found)) min_found = min_cards(n-5, depth + 5);
    if (n > 7 and (min_cards(n-8, depth + 5) < min_found)) min_found = min_cards(n-8, depth + 5);
    if (n > 13 and (min_cards(n-14, depth + 5) < min_found)) min_found = min_cards(n-14, depth + 5);

    return res = min_found + 1;

}


int main(){
    int n;
    DP = VI(500000 + 1, -1);
    while (cin >> n and n != -1){
        cout << min_cards(n, 0) << endl;
    }
}