#include <iostream>

using namespace std;
int n, k, sav[30];
bool check(){
    int d[30];
    for(int i = 1; i <= 29; i++) d[i] = 0;
    for(int i = 1; i <= k; i++) {
        d[sav[i]]++;
        if(d[sav[i]] == 2) return true;
    }
    return false;
}
void xuli(){
    if(check()) return;
    for(int i = 1; i <= k; i++) {
        cout << (char)(sav[i] + 'a' - 1);
    }
    cout << '\n';
}
void dequi(int i){
    if(i > k) return;
    for(int j = 1; j <= n; j++){
        sav[i] = j;
        if(i == k) xuli();
        else dequi(i + 1);
    }
}
int main(){
    cin >> n >> k;
    dequi(1);
    return 0;
}
y
