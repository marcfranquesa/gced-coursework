#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

using VI = vector<int>;
using VC = vector<char>;
using VB = vector<bool>;
using VVB = vector<VB>;
using MCI = map<char, int>;

int n;
VVB compatible;
VC animals;
MCI translator;
VB used;
VI placement;

void read_compatibilites(){
    int m; cin >> m;
    char s1, s2;
    for (int i = 0; i < m; ++i){
        cin >> s1 >> s2;
        compatible[translator[s1]][translator[s2]] = false;
        compatible[translator[s2]][translator[s1]] = false;
    }
}

void gen(int pos, int aa){
    if (pos == n){
        for (int index : placement){
            cout << animals[index];
        }
        cout << endl;
        return;
    }


    for (int index = 0; index < n; ++index){
        if (not used[index]){
            if ((pos > 0 and compatible[index][placement[pos - 1]]) or
                (pos == 0)
            ){
                placement[pos] = index;
                used[index] = true;
                gen(pos + 1, aa + 5);
                used[index] = false;
                placement[pos] = -1;
            }
        }
    }
}

int main(){
    cin >> n;
    animals = VC(n);
    compatible = VVB(n, VB(n, true));
    placement = VI(n, -1);
    used = VB(n, false);

    for (int i = 0; i < n; ++i){
        cin >> animals[i];
        translator[animals[i]] = i;
    }

    read_compatibilites();
    gen(0, 0);
}