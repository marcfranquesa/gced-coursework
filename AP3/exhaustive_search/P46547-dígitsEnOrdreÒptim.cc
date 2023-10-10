#include <iostream>
#include <vector>
using namespace std;

using VI = vector<int>;
using VB = vector<bool>;
using VII = vector<VI>;


VII points;
VB used;

void read_points(int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> points[i][j];
        }
    }
}


void find(int pos, int number, int cur_points, int m, int n, int& highest){
    if (number > 0 and number % m == 0) return;
    if (pos == n and cur_points > highest){
        highest = cur_points;
        return;
    }
    int add = 0;
    for (int i = 0; i < n; ++i){
        if (not used[i]){
            if (pos > 0) add = points[number % 10 - 1][i];
            used[i] = true;
            find(pos + 1, number * 10 + (i + 1), cur_points + add, m, n, highest);
            used[i] = false;
        }
    }
}


int main(){
    int m, n, highest;
    while (cin >> m >> n){
        points = VII(n, VI(n, 0));
        used = VB(n, false);
        highest = 0;
        read_points(n);
        find(0, 0, 0, m, n, highest);
        cout << highest << endl;
    }
}