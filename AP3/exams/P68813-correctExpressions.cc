#include <iostream>
#include <vector>

using namespace std;

using ll = long long int;

using VI = vector<ll>;
using VVI = vector<VI>;

const int UNDEF = -1;

int n, m;

VVI DP;


int search(int length, int variables){
    if (length <= 0 or variables <= 0) return 0;

    // cout << length << "   " << variables << endl;
    ll& res = DP[length][variables];

    if (res != UNDEF) return res;

    if (length % 2 == 0) return res = 0;

    if (length == 1) return res = variables;

    res = search(length - 2, variables);

    // Placing a '-' in between
    for (int i = 0; i < length; ++i){
        int length1 = i - 2;
        int length2 = length - i - 3;
        res += search(length1, variables) * search(length2, variables);
    }

    return res;

}



int main(){
    DP = VVI(25 + 1, VI(25 + 1, UNDEF));
    while (cin >> n >> m){

        cout << search(n, m) << endl;
    }
}