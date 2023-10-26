#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using LLI = long long int;
using VI = vector<LLI>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;


VVVI DP;


LLI find(int zeros, int ones, int remainder){
    LLI& res = DP[zeros][ones][remainder];
    if (res > -1) return res;

    LLI total = 0;
    if (zeros > 0) total += find(zeros - 1, ones, remainder);
    if (ones > 0) {
        int i = (LLI)pow(2, zeros + ones - 1) % 3;
        //cout << "placing a one in pos: " << zeros + ones << " has remainder: " << i << endl;
        //cout << "looking for zeros: " << zeros << " ones: " << ones << " has remainder: " << (((remainder - i) % 3) + 3) % 3 << endl;
        total += find(zeros, ones - 1, (((remainder - i) % 3) + 3) % 3);
    }
    return res = total;

}


int main(){
    DP = VVVI(31, VVI(31, VI(3, -1)));
    DP[0][0][2] = DP[0][0][1] = 0;
    DP[1][1][1] = DP[1][0][0] = DP[1][1][2] = DP[0][1][1] = DP[0][0][0] = 1;
    int z, o;
    while (cin >> z >> o){
        cout << find(z, o, 0) << endl;
    }

}