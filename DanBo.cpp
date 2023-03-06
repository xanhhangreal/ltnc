#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 5;
int n, m, k, List[maxn];
vector < int > a[maxn];
bool tic[maxn];
void dfs(int u){
    tic[u] = true;
    for(int i = 0; i < a[u].size(); i++){
        int v = a[u][i];
        if(!tic[v]) dfs(v);
    }
}
int main(){
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i = 1; i <= k; i++) cin >> List[i];
    for(int i = 1; i < k; i++){
        int u = List[i], v = List[i + 1];
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(List[1]);
    int ans = 0;
    for(int i = 1; i <= n; i++) if(tic[i]) ans++;
    cout << n - ans;
    return 0;
}
