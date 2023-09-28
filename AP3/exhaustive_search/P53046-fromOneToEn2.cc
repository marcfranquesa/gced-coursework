#include <iostream>
#include <vector>
using namespace std;


using VI = vector<int>;
using VB = vector<bool>;

int n;
VI perm;
VB used;


void show(){
    cout << '(';
    bool first = true;
    for (int i = 0; i < perm.size(); ++i){
        if (not first) cout << ',';
        else first = false;
        cout << perm[i] + 1;
    }
    cout << ')' << endl;
}


void find(int curr, int placed){
    if (placed == n - 1){
        show();
        return;
    }

    for (int i = 1; i < n; ++i){
        if (not used[i]){
            perm[curr] = i;
            used[i] = true;
            find(i, placed + 1);
            perm[curr] = 0;
            used[i] = false;
        }
    }
}


int main(){
    cin >> n;
    perm = VI(n, 0);
    used = VB(n, false);
    find(0, 0);
}
