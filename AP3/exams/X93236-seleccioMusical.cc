#include <iostream>
#include <vector>
#include <set>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

int n, m, k;

VVI people_per_song;
VI songs_per_person;
VI solution;

void write(){
    bool first = true;
    for (int i = 0; i < n; ++i){
        if (solution[i] == 1){
            if (not first) cout << ',';
            else first = false;
            cout << i;
        }
    }
    cout << endl;
}

void find(int song, int placed){
    if (placed > k) return;

    if (song == n){
        write();
        return;
    }

    solution[song] = 0;

    int j;
    for (j = 0; j < people_per_song[song].size() and songs_per_person[people_per_song[song][j]] > 1; ++j){
        --songs_per_person[people_per_song[song][j]];
    }

    if (j == people_per_song[song].size()) find(song + 1, placed);

    for (--j; j >= 0; --j){
        ++songs_per_person[people_per_song[song][j]];
    }

    solution[song] = 1;
    find(song + 1, placed + 1);
}


int main(){
    cin >> n >> m;
    people_per_song = VVI(n);
    songs_per_person = VI(m);
    int song;
    for (int i = 0; i < m; ++i){
        cin >> songs_per_person[i];
        for (int j = 0; j < songs_per_person[i]; ++j){
            cin >> song;
            people_per_song[song].push_back(i);
        }
    }

    cin >> k;
    solution = VI(n);
    find(0, 0);
}