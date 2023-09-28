#include <iostream>
#include <vector>
using namespace std;


using VI = vector<int>;


int s, n;
VI use;
VI numbers;


void show(){
    cout << '{';
    bool first = true;
    for (int i = 0; i < use.size(); ++i){
        if (use[i]){
            if (not first) cout << ',';
            else first = false;
            cout << numbers[i];
        } 
    }
    cout << '}' << endl;
}


void find(int carry, int curr_pass, int total, bool first_time){
    if (carry > s) return;
    if (carry + total < s) return;
    if (carry == s && first_time) show();

    if (curr_pass < n){
        use[curr_pass] = 1;
        find(carry + numbers[curr_pass], curr_pass + 1, total - numbers[curr_pass], true);
        use[curr_pass] = 0;
        find(carry, curr_pass + 1, total - numbers[curr_pass], false); 
    }

    // NOTE: This complicates too much, we do slightly to much recursion
    // for(int j = i + 1; j < n; ++j){
    //     use[j] = 1;
    //     find(carry + numbers[j], j, total -= numbers[j]);
    //     use[j] = 0;
    // }
}


int main(){
    cin >> s >> n;
    numbers = VI(n);
    use = VI(n, 0);
    
    int total = 0;
    for (int& number : numbers){
        cin >> number;
        total += number;
    }

    find(0, 0, total, true);
}