#include <bits/stdc++.h>

using namespace std;
pair < int, int > a[105];
int main(){
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a + 1, a + n + 1);
    cout << a[1].second;
    return 0;
}

