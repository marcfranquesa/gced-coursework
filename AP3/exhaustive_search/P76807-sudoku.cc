#include <iostream>
#include <vector>

using namespace std;

using VB = vector<bool>;
using VVB = vector<VB>;
using VI = vector<int>;
using VVI = vector<VI>;

VVB rows;
VVB columns;
VVB squares;
VVI sudoku;
bool found;


void show(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (j > 0) cout << ' ';
            if (sudoku[i][j] == -1) cout << '.';
            else cout << sudoku[i][j] + 1; 
        }
        cout << endl;
    }
}


void update(int i, int j, int n, bool add){
    if (add) sudoku[i][j] = n;
    else sudoku[i][j] = -1;

    rows[i][n] = add;
    columns[j][n] = add;
    squares[3 * (i / int(3)) + j / int(3)][n] = add;

}


void read(){
    char c;
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            cin >> c;
            if (c != '.'){
                update(i, j, c - '1', true);
            } 
        }
    }
}


bool possible(int i, int j, int n){
    return not (
        rows[i][n] or
        columns[j][n] or
        squares[3 * (i / int(3)) + j / int(3)][n]
    );
}


void solve(int i, int j){
    i += j / 9;
    j %= 9;
    if (i == 9){
        found = true;
        show();
        return;
    }
    if (sudoku[i][j] != -1){
        solve(i, j + 1);
        return;
    }
    for (int n = 0; n < 9; ++n){
        if (possible(i, j, n) && not found){
            update(i, j, n, true);
            solve(i, j + 1);
            update(i, j, n, false);
        }
    }
}



int main(){
    int n; cin >> n; cout << n << endl;
    while (n > 0){
        cout << endl;
        rows = VVB(9, VB(9, false));
        columns = VVB(9, VB(9, false));
        squares = VVB(9, VB(9, false));
        sudoku = VVI(9, VI(9, -1));
        read();
        found = false;
        solve(0, 0);
        --n;
    }
}