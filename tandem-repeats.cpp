#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, test;
    cin >> n >> test;
    char s[n + 1];
    for(int i = 1; i <= n; i++) cin >> s[i];
    while(test--)
    {
        int u, v, ans = 0;
        cin >> u >> v;
        string tandem = "";
        for(int i = u; i <= v; i++) tandem += s[i];   /// 1 3  10
        string str = "";
        for(int i = u; i <= n; i++)
        {
            str += s[i];
            if(str.size() == v - u + 1)
            {
                if(str == tandem) ans++, str = "";
                else break;
            }
        }
        cout << ans << '\n';
    }
}
