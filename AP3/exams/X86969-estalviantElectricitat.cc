#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Moli {
    int autonomia;
    int productivitat;
    int consum;
};

using Molins = vector<Moli>;


bool operator<(const Moli& m1, const Moli& m2){
    return ((double) m1.productivitat / m1.consum) > ((double) m2.productivitat / m2.consum);
}


int main(){
    cout.setf(ios::fixed);
    cout.precision(4);

    int n, m;
    double sum_farina, sum_consum, hores;
    while (cin >> n){
        Molins molins(n);
        for (Moli& moli : molins) cin >> moli.autonomia;
        for (Moli& moli : molins) cin >> moli.productivitat;
        for (Moli& moli : molins) cin >> moli.consum;

        sort(molins.begin(), molins.end());

        cin >> m;

        sum_farina = sum_consum = 0;

        for (int moli_id = 0; sum_farina < m; ++moli_id){
            hores = min(
                (double) (m - sum_farina) / molins[moli_id].productivitat,
                (double) molins[moli_id].autonomia
            );
            sum_farina += hores * molins[moli_id].productivitat;
            sum_consum += hores * molins[moli_id].consum;
        }

        cout << sum_consum << endl;

    }
}