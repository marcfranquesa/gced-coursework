#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using LLI = long long int;
using VI = vector<LLI>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;

VVVI DP;

LLI find_sequence(int z, int u, int prev){
    if (z + u == 0) return 1;

    LLI& res = DP[z][u][prev];
    if (res > -1) return res;

    LLI options = 0;
    if (prev != 1 and u > 0){
        options += find_sequence(z, u - 1, 1);
        if (u > 1) options += find_sequence(z, u - 2, 1);
    }
    if (prev != 0 and z > 0) options += find_sequence(z - 1, u, 0);
    return res = options;
    
}


int main(){
    int z, u;
    DP = VVVI(91, VVI(91, VI(2, -1)));
    while (cin >> z >> u){
        if (z + u == 0) cout << 1 << endl;
        else cout << find_sequence(z, u, 0) + find_sequence(z, u, 1) << endl;
    }
}



// CLEANER SOLUTION:

// #include <iostream>
// #include <algorithm>
// #include <vector>

// using namespace std;

// using LLI = long long int;
// using VI = vector<LLI>;
// using VVI = vector<VI>;
// using VVVI = vector<VVI>;

// VVI DP;

// LLI find_sequence(int z, int u){

//     LLI& res = DP[z][u];
//     if (res > -1) return res;

//     LLI options = 0;
//     if (z > 0 and u > 0){
//         options += find_sequence(z - 1, u - 1);
//         if (u > 1) options += find_sequence(z - 1, u - 2);
//     }
//     return res = options; 
// }


// int main(){
//     int z, u;

//     DP = VVI(91, VI(91, -1));
//     DP[0][0] = DP[0][1] = DP[0][2] = DP[1][0] = 1;
//     DP[1][1] = 2;
//     DP[1][2] = 3;
//     while (cin >> z >> u){
//         cout << find_sequence(z, u) << endl;
//     }
// }