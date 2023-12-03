#include <iostream>
#include <vector>
#include <string>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;
using VS = vector<string>;


int main(){
    int l = 26;
    VI letters(l, 1);
    for (int i = 1; i < l; ++i) letters[i] = letters[i-1] + i + 1;

    VS rectangle;
    string s;
    while (cin >> s) rectangle.push_back(s);

    VVI subrectangles(rectangle.size(), VI(rectangle[0].size()));

    subrectangles[0][0] = letters[rectangle[0][0] - 'A'];
    for (int i = 1; i < subrectangles.size(); ++i)  subrectangles[i][0] = subrectangles[i - 1][0] + letters[rectangle[i][0] - 'A'];
    for (int j = 1; j < subrectangles[0].size(); ++j)  subrectangles[0][j] = subrectangles[0][j-1] + letters[rectangle[0][j] - 'A'];

    for (int i = 1; i < subrectangles.size(); ++i) for (int j = 1; j < subrectangles[0].size(); ++j){
        subrectangles[i][j] = (
            letters[rectangle[i][j] - 'A']
            + subrectangles[i - 1][j]
            + subrectangles[i][j - 1]
            - subrectangles[i - 1][j - 1]
        );
    }

    for (int i = 0; i < subrectangles.size(); ++i){
        cout << subrectangles[i][0];
        for (int j = 1; j < subrectangles[0].size(); ++j) cout << ' ' << subrectangles[i][j];
        cout << endl;
    }

}