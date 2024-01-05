#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

using VI = vector<int>;
using VVI =  vector<VI>;

int n, m;
VVI board;

bool is_off(){
    for (int i = 1; i < n + 1; ++i)
    for (int j = 1; j < m + 1; ++j)
        if (board[i][j] == 1) return false;
    return true;
}


void switch_(int i, int j){
        board[i][j] = 1 - board[i][j];
        board[i - 1][j] = 1 - board[i - 1][j];
        board[i + 1][j] = 1 - board[i + 1][j];
        board[i][j - 1] = 1 - board[i][j - 1];
        board[i][j + 1] = 1 - board[i][j + 1];
        board[i - 1][j - 1] = 1 - board[i - 1][j - 1];
        board[i - 1][j + 1] = 1 - board[i - 1][j + 1];
        board[i + 1][j - 1] = 1 - board[i + 1][j - 1];
        board[i + 1][j + 1] = 1 - board[i + 1][j + 1];
};


bool is_valid(int i, int j){
    bool first_row = i == 1;
    bool second_row = i == 2;
    bool first_rows = first_row or second_row;
    bool first_col = j == 1;
    bool second_col = j == 2;
    bool first_cols = first_col or second_col;
    bool last_row = i == n;

    bool possible_solution_general = (
        first_row or first_cols or (board[i - 1][j - 2] == 0)
    );

    bool possible_solution_first_col = (
        first_rows or not first_col or (board[i - 2][m] == 0 and board[i - 2][m - 1] == 0)
    );

    bool possible_solution_last_row = (
        first_cols or not last_row or (board[i][j - 2] == 0)
    );

    return (
        possible_solution_general and possible_solution_last_row and possible_solution_first_col
    );
}


void search(int i, int j, int switches, int& min_switches){
    if (switches >= min_switches) return;
    if (is_off()){
        min_switches = min(min_switches, switches);
        return;
    }
    if (j >= m + 1) {++i; j = 1;}
    if (i == n + 1) return;
    //cout << "step: " << step << " " << i << " " << j << endl;


    if (is_valid(i, j)){
        search(i, j + 1, switches, min_switches);
        switch_(i, j);
        search(i, j + 1, switches + 1, min_switches);
        switch_(i, j);
    }
}

int main(){
    char c;
    while (cin >> n >> m){
        board = VVI(n + 2, VI(m + 2, 1));
        for (int i = 1; i < n + 1; ++i)
        for (int j = 1; j < m + 1; ++j) {
            cin >> c;
            if (c == '.') board[i][j] = 0;
        }

        int min_steps = n * m + 1;
        search(1, 1, 0, min_steps);
        if (min_steps == n * m + 1) cout << "no";
        else cout << min_steps; cout << endl;
    }
}