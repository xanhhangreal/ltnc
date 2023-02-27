#include <iostream>

using namespace std;
bool check(int x){
    int savx = x, y = 0;
    while(x > 0) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return (savx == y);
}
int main(){
    int T; cin >> T;
    while(T--){
        int A, B, ans = 0;
        cin >> A >> B;
        for(int i = A; i <= B; i++) if(check(i)) ans++;
        cout << ans << '\n';
    }
    return 0;
}
