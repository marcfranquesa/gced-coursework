#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef vector<char> VC;
typedef vector<bool> VB;

int n;
VC vowels;
VC consonants;
VB usedvowels;
VB usedconsonants;
VC word;


void show(){
    for (char c : word) cout << c;
    cout << endl;
}


void gen(int pos, int n){
    if (pos == 2*n){
        show();
        return;
    }

    const VC& chars = (pos % 2 == 0 ? consonants : vowels);
    VB& used = (pos % 2 == 0 ? usedconsonants : usedvowels);
    
    for(int i = 0; i < n; ++i){
        if (not used[i]){
            word[pos] = chars[i];
            used[i] = true;
            gen(pos+1, n);
            used[i] = false;
        }
    }

}


int main(){
    int n; cin >> n;
    vowels = VC(n);
    consonants = VC(n);
    usedvowels = VB(n, false);
    usedconsonants = VB(n, false);
    word = VC(2*n);

    for (char& c : consonants) cin >> c;
    for (char& c : vowels) cin >> c;

    gen(0, n);
}