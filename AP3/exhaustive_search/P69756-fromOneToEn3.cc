#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


typedef vector<int> VI;
typedef vector<bool> VB;

int n, k;
VI perm;
VB used;


void show(){
    cout << '(';
    for (int i = 0; i < perm.size(); ++i){
        if (i != 0) cout << ',';
        cout << perm[i] + 1;
    }
    cout << ')' << endl;
}


void find(int pos, int inversions){
    if (inversions > k or k > inversions + ((n-pos)*(n-pos-1))/2) return;
    if (pos == n && inversions == k){
        show();
        return;
    }

    int add = 0;
    for (int i = 0; i < n; ++i){
        if (not used[i]){
            perm[pos] = i;
            used[i] = true;
            find(pos + 1, inversions + add);
            used[i] = false;
            add++;
        }
    }
}


int main(){
    cin >> n >> k;
    perm = VI(n, -1);
    used = VB(n, false);
    find(0, 0);
}