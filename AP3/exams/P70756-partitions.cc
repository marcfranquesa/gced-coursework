#include <iostream>
#include <vector>
#include <string>
using namespace std;

using VS = vector<string>;
using VI = vector<int>;


VS names;
VI solution;

int n, p;

void show(){
    for (int i = 0; i < p; ++i){
        cout << "subset " << i + 1 << ": {";
        bool first = true;
        for(int j = 0; j < n; ++j){
            if (solution[j] == i){
                if (not first){
                    cout << ',';
                }
                else first = false;

                cout << names[j];
            }
        }
        cout << '}' << endl;
    }
    cout << endl;
}


void search(int pos){
    if (pos == n) return show();

    for (int i = 0; i < p; ++i){
        solution[pos] = i;
        search(pos + 1);
    }
}


int main(){
    while (cin >> n){
        names = VS(n);
        solution = VI(n);

        for (string& name : names) cin >> name;

        cin >> p;

        search(0);
    }
}