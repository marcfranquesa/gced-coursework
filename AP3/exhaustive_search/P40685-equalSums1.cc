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


void find(int carry, int i){
    if (carry == s){
        show();
    }
    
    for(int j = i + 1; j < numbers.size(); ++j){
        use[j] = 1;
        find(carry + numbers[j], j);
        use[j] = 0;
    }

}


int main(){
    cin >> s >> n;
    numbers = VI(n);
    use = VI(n, 0);

    for (int& number : numbers) cin >> number;
    find(0, -1);
}