#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

VVI board;
VVI defended;


void update(int i, int j, int to_add){
    defended[i - 2][j - 1] += to_add;
    defended[i - 2][j + 1] += to_add;
    defended[i + 2][j - 1] += to_add;
    defended[i + 2][j + 1] += to_add;
    defended[i - 1][j - 2] += to_add;
    defended[i + 1][j - 2] += to_add;
    defended[i - 1][j + 2] += to_add;
    defended[i + 1][j + 2] += to_add;
}



int search(int i, int j, int imax, int jmax, int padding){
    if (i == imax - 1 and j == jmax) return 0;
    if (j == jmax) return search(i + 1, padding, imax, jmax, padding);

    int skip = search(i, j + 1, imax, jmax, padding);
    // Forced to skip
    if (defended[i][j] > 0) return skip;

    update(i, j, 1);
    int add = search(i, j + 1, imax, jmax, padding);
    update(i, j, -1);

    return max(skip, add + board[i][j]);
}


int main(){
    int n, m;
    int padding = 2;
    while (cin >> n >> m){
        board = VVI(n + 2 * padding, VI(m + 2 * padding, 0));
        defended = VVI(n + 2 * padding, VI(m + 2 * padding, 0));
        for (int i = padding; i < n + padding; ++i){
            for (int j = padding; j < m + padding; ++j){
                cin >> board[i][j];
            }
        }
        cout << search(padding, padding, n + padding, m + padding, padding) << endl;
    }
}