#include <iostream>
#include <vector>
using namespace std;

using VB = vector<bool>;
using VI = vector<int>;
using VVI = vector<VI>;

struct Entrada {
    int colors;
    VVI canvis;
    int cotxes;
    VVI cotxes_per_color;
};


struct Solucio {
    VI ordre_colors;
    int cost_total;
    VB usats;
};


void llegeix_canvis(Entrada& e){
    auto& [colors, canvis, _, __] = e;
    canvis = VVI(colors, VI(colors));
    for (VI& filera : canvis) for (int& cost : filera) cin >> cost;
}


void llegeix_cotxes(Entrada& e){
    auto& [colors, _, cotxes, cotxes_per_color] = e;
    cotxes_per_color = VVI(colors);
    int color;
    for (int i = 0; i < cotxes; ++i) {
        cin >> color;
        cotxes_per_color[color].push_back(i);
    }
}


bool mes_petit(const Solucio& a, const Solucio& b, const Entrada& e){
    auto& [p1, _, __] = a;
    auto& [p2, ___, ____] = b;

    for (int i = 0; i < e.colors; ++i){
        if (p1[i] != p2[i]) {
            int k1 = e.cotxes_per_color[p1[i]][0];
            int k2 = e.cotxes_per_color[p2[i]][0];
            return k1 < k2;
        }
    }
    return true;
}


void optimitza(int pos, Solucio& millor, Solucio& s, const Entrada& e){
    auto& [colors, canvis, cotxes, cotxes_per_color] = e;
    auto& [ordre_colors, cost_total, usats] = s;

    if (pos == colors){
        if (
            (cost_total < millor.cost_total) or
            ((cost_total == millor.cost_total) and mes_petit(s, millor, e))
        ){
            millor = s;
        }
        return;
    }

    for (int color = 0; color < colors; ++color){
        if (not usats[color]){
            ordre_colors[pos] = color;
            if (pos > 0) cost_total += canvis[ordre_colors[pos - 1]][color];
            usats[color] = true;
            optimitza(pos + 1, millor, s, e);

            if (pos > 0) cost_total -= canvis[ordre_colors[pos - 1]][color];
            usats[color] = false;
        }
    }
}


int main(){
    Entrada e;
    auto& [colors, canvis, cotxes, cotxes_per_color] = e;
    while (cin >> colors){
        llegeix_canvis(e);
        cin >> cotxes;
        llegeix_cotxes(e);

        Solucio s, millor;
        auto& [ordre_colors, cost_total, usats] = s;
        cost_total = 0;
        ordre_colors = VI(colors, -1);
        usats = VB(colors, false);

        millor = s;
        millor.cost_total = 1e9;
        optimitza(0, millor, s, e);


        bool first = true;
        for (int i : millor.ordre_colors){
            for (int cotxe : cotxes_per_color[i]){
                if (not first) cout << ' ';
                cout << cotxe;
                first = false;
            }
        }
        cout << ", amb cost: " << millor.cost_total << endl;
    }
}