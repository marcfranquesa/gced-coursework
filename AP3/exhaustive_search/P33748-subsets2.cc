#include <iostream>
#include <vector>
#include <string>
using namespace std;

using VB = vector<bool>;
using VS = vector<string>;

int m, n;
VS words;
VB use;


void show_subset(){
    cout << '{';
    for (int i = 0; i < use.size(); ++i){
        if (use[i]){
            if (i != 0) cout << ',';
            cout << words[i];
        } 
    }
    cout << '}' << endl;
}


void create_subsets(int k, int l){
    if (m == k) {
        show_subset(); return;
    }
    for (int i = l + 1; i < words.size() - (m - k - 1); ++i){
        use[i] = true;
        create_subsets(k + 1, i);
        use[i] = false;
    }
}


int main(){
    cin >> m >> n;
    use = VB(n, false);
    words = VS(n);
    for(int i = 0; i < n; ++i){
        cin >> words[i];
    }
    
    create_subsets(0, -1);
}