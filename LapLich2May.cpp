#include <bits/stdc++.h>

using namespace std;
struct ii {
    int fi, sc, id;
};
int n;
ii a[10005];
vector < ii > I, II;
bool cmpI(ii x, ii y)
{

    return x.fi < y.fi;
}
bool cmpII(ii x, ii y)
{
    if(x.sc == y.sc) return x.fi > y.fi;
    return x.sc > y.sc;
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i].fi;
    for(int i = 1; i <= n; ++i) cin >> a[i].sc, a[i].id = i;
    for(int i = 1; i <= n; ++i)
    {
        if(a[i].fi < a[i].sc) I.push_back(a[i]);
        else II.push_back(a[i]);
    }
    int m1 = 0, m2 = 0;
    sort(I.begin(), I.end(), cmpI);
    sort(II.begin(), II.end(), cmpII);
    for(int i = 0; i < I.size(); ++i)
    {
        m1 += I[i].fi;
        if(m1 > m2) m2 = m1 + I[i].sc;
        else m2 += I[i].sc;
    }
    for(int i = 0; i < II.size(); ++i)
    {
        m1 += II[i].fi;
        if(m1 > m2) m2 = m1 + II[i].sc;
        else m2 += II[i].sc;
    }
    cout << m2 << '\n';
    for(int i = 0; i < I.size(); ++i) cout << I[i].id << " ";
    for(int i = 0; i < II.size(); ++i) cout << II[i].id << " ";
}
