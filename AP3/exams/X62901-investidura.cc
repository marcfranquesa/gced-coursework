#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int UNDEF = -1;
const int FAVOR = 2;
const int CONTRA = 0;
const int ABST = 1;

struct Partit {
    int escons;
    int perfil;
};

using Partits = vector<Partit>;
using VI = vector<int>;

Partits partits;
VI solucio;
int n, m, escons_totals;


void escriu(int escons_max){
    cout << "President de";
    for (int i = 0; i < n; ++i){
        if (solucio[i] == FAVOR and partits[i].escons == escons_max) cout << " " << i;
    } cout << endl;
    cout << "A favor";
    for (int i = 0; i < n; ++i){
        if (solucio[i] == FAVOR) cout << " " << i;
    } cout << endl;
    cout << "Abstencio";
    for (int i = 0; i < n; ++i){
        if (solucio[i] == ABST) cout << " " << i;
    } cout << endl;
    cout << "En contra";
    for (int i = 0; i < n; ++i){
        if (solucio[i] == CONTRA) cout << " " << i;
    } cout << endl;
    cout << endl;
}


void investidures(int partit, int escons_a_favor, int escons_en_contra,
                  int escons_restants, int rang_baix, int rang_alt, int escons_max){

    if (escons_a_favor + escons_restants <= escons_en_contra) return;
    if (rang_alt - rang_baix > m) return;

    if (partit == n) return escriu(escons_max);

    auto& [escons, perfil] = partits[partit];
    escons_restants -= escons;

    solucio[partit] = CONTRA;
    investidures(partit + 1, escons_a_favor, escons_en_contra + escons,
                 escons_restants, rang_baix, rang_alt, escons_max);

    rang_baix = min(rang_baix, perfil);
    rang_alt = max(rang_alt, perfil);
    solucio[partit] = ABST;
    investidures(partit + 1, escons_a_favor, escons_en_contra,
                 escons_restants, rang_baix, rang_alt, escons_max);

    if (escons > escons_max) escons_max = escons;
    solucio[partit] = FAVOR;
    investidures(partit + 1, escons_a_favor + escons, escons_en_contra,
                 escons_restants, rang_baix, rang_alt, escons_max);


}


int main(){
    while (cin >> n){
        partits = Partits(n);
        escons_totals = 0;
        for (Partit& p : partits) {
            cin >> p.escons >> p.perfil;
            escons_totals += p.escons;
        }
        cin >> m;

        solucio = VI(n, UNDEF);
        investidures(0, 0, 0, escons_totals, 1000, 0, 0);
    }
}