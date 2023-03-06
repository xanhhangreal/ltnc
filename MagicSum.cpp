#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 5;
long long a[maxn];
int main(){
    for(int i = 1; i <= 1e6; i++) a[i] = a[i - 1] + i;
    int n; cin >> n;
    long long sum = 0;
    while(n--){
        int l, r;
        cin >> l >> r;
        sum += a[r] - a[l - 1];
    }
    cout << sum;
}
