#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;

int main(){
    int k, n;
    while (cin >> k >> n){
        VI numbers(n);
        for (int& n : numbers) cin >> n;
        sort(numbers.begin(), numbers.end());

        int m = 1;
        int pre = numbers[0] + k;
        for (int i = 1; i < n; ++i){
            if (numbers[i] > pre){
                pre = numbers[i] + k;
                ++m;
            }
        }

        cout << m << endl;
    }
}