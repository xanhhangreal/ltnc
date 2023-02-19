#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 5;
pair < long long, long long > a[maxn];
int n, ans;
long long c;
int main(){
    cin >> n >> c;
    for(int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++) {
        if(c >= a[i].first) c += a[i].second, ans++;
        else break;
    }
    cout << ans;
}
