#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

using PII = pair<int, int>;
using VP = vector<PII>;


// NOTE: using a queue would be quite better


bool sortCondition(const PII& a, const PII& b)
{
    return (a.second < b.second);
}


int main(){
    int n;
    while (cin >> n){
        VP episodes(n);
        for (PII& episode : episodes) cin >> episode.first >> episode.second;
        sort(episodes.begin(), episodes.end(), sortCondition);

        int prev = -1;
        int recordable = 0;
        for (PII& episode : episodes) if (episode.first > prev){
            prev = episode.second;
            recordable++;
        }

        cout << recordable << endl;

    }
}