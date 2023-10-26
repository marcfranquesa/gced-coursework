#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VI = vector<int>;

int main(){
    string s;
    while (cin >> s){
        int total = 0;
        VI subsequences(s.size(), 0);
        for(int i = subsequences.size() - 2; i > -1; --i){
            for (int j = i + 1; j < subsequences.size(); ++j){
                if (s[i] < s[j]){
                    subsequences[i] += subsequences[j] + 1;
                }
            }
            total += subsequences[i];
        }
        cout << total << endl;
    }
}