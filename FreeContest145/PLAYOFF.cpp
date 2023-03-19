#include <bits/stdc++.h>
#define ll long long
/// Nhìn đồ thì từ phải qua trái rồi seg

using namespace std;
const int maxn = 2e6 + 5;
int k, tree[maxn], n;
string s;
void Build(const int &id, const int &l, const int &r){
    if(l > r) return;
    if(l == r) {
        tree[id] = 1;
        if(s[n - id] == '?') tree[id]++;
        return;
    }

    int m = (l + r) >> 1;
    Build(id * 2, l, m);
    Build(id * 2 + 1, m + 1, r);

    if(s[n - id] == '1') tree[id] = tree[id * 2];
    else if(s[n - id] == '0') tree[id] = tree[id * 2 + 1];
    else tree[id] = tree[id * 2] + tree[id * 2 + 1];
}
void update(const int &id, const int &l, const int &r, const int &p, const char &c){
    if(l == r) {
        tree[id] = 1;
        if(c == '?') tree[id]++;
    }
    else {
        int m = (l + r) >> 1;
        if(n - id < p) update(id * 2, l, m, p, c);
        else if(n - id > p) update(id * 2 + 1, m + 1, r, p, c);
        else {
            if(c == '1') tree[id] = tree[id * 2];
            else if(c == '0') tree[id] = tree[id * 2 + 1];
            else tree[id] = tree[id * 2] + tree[id * 2 + 1];

        }
        if(s[n - id] == '1') tree[id] = tree[id * 2];
        else if(s[n - id] == '0') tree[id] = tree[id * 2 + 1];
        else tree[id] = tree[id * 2] + tree[id * 2 + 1];
            //cout << tree[1];
    }
}
void prepare(){
    freopen(".inp", "r", stdin);

    cin >> k >> s;
    s = " " + s;
    n = s.size();
    Build(1, 1, n);
    //for(int i = 1; i <= n; i++) cout << tree[i] << ' ';
}
int main(){
    prepare();
    int q;
    cin >> q;
    while(q--){
        int p;
        char c;
        cin >> p >> c;
        update(1, 1, n, p, c);
        //for(int i = 1; i <= n; i++) cout << tree[i] << ' ';
        //cout << '\n';
        cout << tree[1] << '\n';
    }
    return 0;
}
