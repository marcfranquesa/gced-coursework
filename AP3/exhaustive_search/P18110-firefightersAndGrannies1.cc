#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;

VI schools;


int search(int school, int remaining_g, int last_school){
    // cout << "School: " << school << ", remaining groups: " << remaining_g << endl;
    if (remaining_g == 0) return 0;
    if (school == last_school) return schools[school - 1] / 2;
    if (school > last_school) return 0;

    return max(
        schools[school] + (schools[school + 1] + schools[school - 1]) / 2 + search(school + 2, remaining_g - 1, last_school),
        search(school + 1, remaining_g, last_school)
    );
}


int main(){
    int g, n;
    while (cin >> g >> n){
        schools = VI(n + 2, 0);
        for (int i = 1; i < n + 1; ++i) cin >> schools[i];
        cout << search(1, g, n + 1) << endl;
    }

}

