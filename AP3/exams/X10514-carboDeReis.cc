#include <vector>
#include <iostream>
#include <map>

using namespace std;

struct Treballador {
    int productivitat;
    int cost;
    int pes;
};

using Treballadors = vector<Treballador>;

Treballadors trs;

using VI = vector<int>; using VVI = vector<VI>; using VVVI = vector<VVI>;
VVVI DP;

const int UNDEF = -1;


int maxima_productivitat(int pressupost_restant, int pes_restant, int pos){
    // cout << pressupost_restant << ' ' << pes_restant << ' ' << pos << endl;
    int& res = DP[pos][pressupost_restant][pes_restant];

    if (res != UNDEF) return res;

    if (pos == trs.size()) return res = 0;

    res = maxima_productivitat(pressupost_restant, pes_restant, pos + 1);

    const Treballador& actual = trs[pos];
    if (actual.cost <= pressupost_restant and actual.pes <= pes_restant){
        res = max(
            res, actual.productivitat + maxima_productivitat(pressupost_restant - actual.cost, pes_restant - actual.pes, pos + 1)
        );
    }

    return res;
}

int main(){
    int treballadors, pressupost, pes_max;
    while (cin >> treballadors >> pressupost >> pes_max){
        trs = Treballadors(treballadors);

        for (Treballador& tr : trs) cin >> tr.productivitat >> tr.cost >> tr.pes;

        DP = VVVI(treballadors+1, VVI(pressupost+1, VI(pes_max+1, UNDEF)));
        cout << maxima_productivitat(pressupost, pes_max, 0) << endl;
    }
}