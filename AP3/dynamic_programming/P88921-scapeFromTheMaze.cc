#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

VVI maze;
VVI paths;


void read_maze(int n, int m){
    maze = VVI(n, VI(m, 1));
    char c;
    for (VI& row : maze) for (int& cell : row) {
        cin >> c;
        if (c == 'X'){
            cell = 0;
        }
    }
}

int find_paths(int n, int m){
    int& res = paths[n][m];
    if (res > -1) return res;

    if (maze[n][m] == 0) return res = 0;
    
    int down = 0, right = 0;
    if (n + 1 < maze.size()) down = find_paths(n + 1, m);
    if (m + 1 < maze[0].size()) right = find_paths(n, m + 1);
    return res = min(down + right, (int)1e6);
}


int main(){
    int n, m; 
    while (cin >> n >> m and (n != 0 and m != 0)){
        read_maze(n, m);
        paths = VVI(n, VI(m, -1));
        paths[n - 1][m - 1] = 1;
        int paths_found = find_paths(0, 0);
        (paths_found < 1e6) ? cout << paths_found : cout << "!!!";
        cout << endl;
    }

}