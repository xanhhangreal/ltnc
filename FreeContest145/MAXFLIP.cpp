#include <bits/stdc++.h>

using namespace std;
int const maxn = 1e5 + 5;
int n, a[maxn], sum;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    int ans = sum - 2 * a[1] - 2 * a[2];
    for(int i = 2; i < n; i++) {
        ans = max(ans, sum - 2 * a[i] - 2 * a[i + 1]);
    }
    cout << ans;
    return 0;
}
