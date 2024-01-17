#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

using Game = vector<int>;
using Games = map<Game, bool>;

Games winning;

bool winnable(const Game& now){
    if (winning.find(now) != winning.end()) return winning[now];

    Game next;
    for (int pos = 0; pos < 6; ++pos){
        next = now;
        for (int balls = now[pos] - 1; balls >= 0; --balls){
            next[pos] = balls;
            if (not winnable(next)) {
                return winning[now] = true;
            }
        }
    }
    return winning[now] = false;
}


int main(){
    Game base(6, 0);
    winning[base] = false;

    int n; cin >> n;
    string a, b, winner;
    Game game(6);
    for (int game_no = 0; game_no < n; ++game_no){
        cin >> a >> b;
        for (int& set : game) cin >> set;
        winner = b;
        if (winnable(game)) winner = a;

        cout << "Game #" << game_no + 1 << ": " << winner << endl;
    }


}