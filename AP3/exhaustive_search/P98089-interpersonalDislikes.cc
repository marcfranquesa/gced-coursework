#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

using VS = vector<string>;
using VI = vector<int>;
using VII = vector<VI>;

VS names;
VII dislikes;
VI cycle;
VI best_cycle;


void read(){
    for (string& name : names) cin >> name;
    for(VI& person : dislikes) for (int& dislike : person) cin >> dislike;
}


void find(int pos, int previous, int total_dislike, 
          int& lowest_dislike, int n){
    if (total_dislike > lowest_dislike) return;

    if (pos == n && total_dislike < lowest_dislike){
        lowest_dislike = total_dislike;
        best_cycle = cycle;
        return;
    }

    for (int i = 0; i < n; ++i){
        if (cycle[i] == -1 && i != previous){
            cycle[previous] = i;
            find(pos + 1, i, total_dislike + dislikes[previous][i], lowest_dislike, n);
            cycle[previous] = -1;
        }
    }
}


int main(){
    int n;
    while (cin >> n){
        names = VS(n);
        dislikes = VII(n, VI(n, 0));
        read();

        cycle = VI(n, -1);
        best_cycle = VI(n, -1);
        int lowest_dislike = 1e9;
        find(1, 0, 0, lowest_dislike, n);


        cout << lowest_dislike << endl;
        int prev = 0; cout << names[0];
        for (int i = 1; i < n; ++i){
            prev = best_cycle[prev];
            cout << ' ' << names[prev];
        }
        cout << endl;
    }
}