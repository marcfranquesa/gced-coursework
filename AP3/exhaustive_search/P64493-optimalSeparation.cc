#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

using VI = vector<int>;

int n;
int best_diff;
VI numbers;

void minimum_difference(int pos, int difference, int remaining){
    // cout << pos << " " << group1 << " " << group2 << " " << remaining << endl;


    if (pos == n) {
        best_diff = min(best_diff, abs(difference));
        return;
    };

    if (abs(difference) - remaining >= best_diff or best_diff == 0) return;

    minimum_difference(pos + 1, difference + numbers[pos], remaining - numbers[pos]);
    minimum_difference(pos + 1, difference - numbers[pos], remaining - numbers[pos]);

}


int main(){
    while (cin >> n){
        numbers = VI(n);
        for (int& number : numbers) {
            cin >> number;
            best_diff += number;
        }

        minimum_difference(0, 0, best_diff);

        cout << best_diff << endl;

    }
}