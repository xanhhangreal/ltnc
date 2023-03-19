#include <bits/stdc++.h>

using namespace std;

void xuli(string &ans, char c, int j){
    if(j == 6) return;
    if(c >= ans[j]) {
        xuli(ans, ans[j], j + 1);
        ans[j] = c;
    }
}
int main(){
    string s, News = "", ans = "";
    cin >> s;
    int n = s.size() - 1, id = 0;
    for(int i = 0; i <= n; i++)
        if(s[i] >= '0' && s[i] <= '9') {
            News[++id] = s[i];
        }
    for(int i = 1; i <= 5; i++) ans[5 - i + 1] = News[id - i + 1];
    for(int i = id - 5; i >= 1; i--) xuli(ans, News[i], 1);
    for(int i = 1; i <= 5; i++) cout << ans[i];
    return 0;
}

