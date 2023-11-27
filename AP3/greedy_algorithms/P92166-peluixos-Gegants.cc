#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;

int main(){
    int n;
    while (cin >> n){
        VI preus(3*n);
        for (int& p : preus) cin >> p;
        sort(preus.begin(), preus.end());

        int s = 0;
        for (int i = 0; i < 3*n; ++i) if (i % 3 != 0){
            s += preus[i];
        }

        cout << s << endl;
    }
}