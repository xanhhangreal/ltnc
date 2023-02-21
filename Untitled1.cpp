#include <bits/stdc++.h>

using namespace std;

int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= k; i++) s[1] += a[i];
    for(int i = k + 1; i <= n; i++) s[i - k + 1] = s[i - k] - a[i - k] + a[i - k + 1];
    n = n - k + 1;
    for(int i = 1; i <= n; i++) s[i] += s[i - 1];
    for(int i = 1; i <= n; i++)
}
