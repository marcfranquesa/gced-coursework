#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;

int main(){
    int x, D, n;

    while (cin >> x >> D >> n){
        VI stations(n);
        for (int& station : stations) cin >> station;
        sort(stations.begin(), stations.end());

        int stops = 0;
        int limit = x;

        for (int i = 1; i < n && D > limit; ++i) if (stations[i] > limit) {
                ++stops;
                limit = stations[i-1] + x;
        }

        if (limit < D) ++stops;

        cout << stops << endl;

    }
}