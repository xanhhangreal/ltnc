#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 5;
int num, day;
ll p[maxn];
void solve(int c, int k){

}
int main(){
    cin >> num >> day;
    for(int i = 1; i <= num; i++) cin >> p[i];
    sort(p + 1, p + num + 1, greater < ll > );
    while(day--){
        int c, k;
        cin >> c >> k;
        solve(c, k);
    }
    return 0;
}
