#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

bool smaller(const string& word1, int i, int max_p, int max_l){
    for (int k = 0; k < max_l; ++k){
        if (word1[i + k] < word1[max_p + k]) return true;
        if (word1[i + k] > word1[max_p + k]) return false;
    }
    return false;
}

int main(){
    string word1, word2;
    while (cin >> word1 >> word2){
        VVI DP = VVI(word1.size() + 1, VI(word2.size() + 1, 0));
        int max_l = 0;
        VI max_p;
        for (int i = word1.size() - 1; i > -1; --i){
            for (int j = word2.size() - 1; j >  -1; --j){
                if (word1[i] == word2[j]){
                    DP[i][j] = DP[i + 1][j + 1] + 1;
                    if (DP[i][j] > max_l) {max_p = VI(1, i); max_l = DP[i][j];}
                    else if (DP[i][j] == max_l) max_p.push_back(i);
                }
            }
        }
        if (max_p.size() == 0) cout << endl;
        else{
            int maxp = max_p[0];
            for (int candidate : max_p) if (smaller(word1, candidate, maxp, max_l)) maxp = candidate;
            for (int k = maxp; k < maxp + max_l; ++k) cout << word1[k]; cout << endl;
        }
    }
}