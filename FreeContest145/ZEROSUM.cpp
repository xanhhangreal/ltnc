#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn = 2e5 + 5;
ll s[maxn], ans;
int main(){
   // freopen("sumseq0.inp", "r", stdin);
   // freopen("sumseq0.out", "w", stdout);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        ll a; cin >> a;
        s[i] = s[i - 1] + a;
    }
    sort(s, s + n + 1);
    int id = 0;
    while(id < n){
        int i = id;
        while(i < n && s[i] == s[i + 1]) i = i + 1;
        ans += (ll)(i - id) * (i - id + 1) / 2;
        id = i + 1;
        //cout << id << ' ';//0 0 0 2 2 3

    }
    cout << ans;
}
