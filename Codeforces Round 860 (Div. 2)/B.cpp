#include <bits/stdc++.h>

using namespace std;
const int maxn = 5e4 + 5;
int Tic[maxn], p[maxn];
vector < int > People[maxn];
int main()
{
    freopen(".inp", "r", stdin);
    int t;
    cin >> t;
    while(t--)
    {
        int m;
        cin >> m;
        for(int i = 1; i <= m; i++)
        {
            int n;
            cin >> n;
            for(int j = 1; j <= n; j++)
            {
                int val;
                cin >> val;
                People[i].push_back(val);
                Tic[val]++;
            }
        }
        bool ok = true;
        for(int i = m; i >= 1; i--)
        {
            p[i] = -1;
            for(auto val : People[i])
            {
                //if(i == 1) cout << val << '\n';
                if(Tic[val] == 0) continue;
                if(p[i] == -1)
                {
                    p[i] = val;
                }
                Tic[val] = 0;
            }
            if(p[i] == -1)
            {
                ok = false;
                break;
            }
        }
        if(!ok) cout << "-1\n";
        else
        {
            for(int i = 1; i <= m; i++) cout << p[i] << ' ';
            cout << '\n';
        }
        for(int i = 1; i <= m; i++) People[i].clear();
        memset(People, 0, sizeof People);
    }
}
