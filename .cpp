#include <bits/stdc++.h>

using namespace std;

int row, col;
char a[105][105];

void solve(string s)
{
    int n = s.size();
    for(int i = 0; i < n; i++)
        if(s[i] < 'a' || s[i] > 'z')
        {
            cout << "input error\n";
            return;
        }
    bool ok = false;
    pair < int, int > pos1, pos2;
    /// ngang
    for(int id = 0; id <= row; id++)
        for(int i = 0; i <= col - n + 1; i++)
        {
            string str = "";
            for(int j = i; j <= i + n - 1; j++)
                str += a[id][j];
            if(str == s)
            {
                ok = true;
                pos1 = {id, i};
                pos2 = {id, i + n - 1};
            }
            reverse(str.begin(), str.end());
            if(str == s)
            {
                ok = true;
                pos2 = {id, i};
                pos1 = {id, i + n - 1};
            }
        }
    /// doc
    for(int i = 0; i <= row - n + 1; i++)
        for(int j = 0; j <= col; j++)
        {
            string str = "";
            for(int id = i; id <= i + n - 1; id++)
                str += a[id][j];
            if(str == s)
            {
                ok = true;
                pos1 = {i, j};
                pos2 = {i + n - 1, j};
            }
            reverse(str.begin(), str.end());
            if(str == s)
            {
                ok = true;
                pos2 = {i, j};
                pos1 = {i + n - 1, j};
            }
        }
    /// cheo 45
    for(int i = n - 1; i <= row; i++)
        for(int j = 0; j <= col - n + 1; j++)
        {
            string str = "";
            for(int id = 0; id <= n - 1; id++)
                str += a[i - id][j + id];
            if(str == s)
            {
                ok = true;
                pos1 = {i, j};
                pos2 = {i - n + 1, j + n - 1};
            }
            reverse(str.begin(), str.end());
            if(str == s)
            {
                ok = true;
                pos2 = {i, j};
                pos1 = {i - n + 1, j + n - 1};
            }
        }
    /// cheo 135
    for(int i = 0; i <= row - n + 1; i++)
        for(int j = 0; j <= col - n + 1; j++)
        {
            string str = "";
            for(int id = 0; id <= n - 1; id++)
                str += a[i + id][j + id];
            if(str == s)
            {
                ok = true;
                pos1 = {i, j};
                pos2 = {i + n - 1, j + n - 1};
            }
            reverse(str.begin(), str.end());
            if(str == s)
            {
                ok = true;
                pos1 = {i, j};
                pos2 = {i + n - 1, j + n - 1};
            }
        }
    if(!ok) cout << "not found\n";
    else
    {
        cout << pos1.first << ' ' << pos1.second << ' ';
        cout << pos2.first << ' ' << pos2.second << '\n';
    }
}
int main()
{
    freopen(".inp", "r", stdin);
    cin >> row >> col;
    for(int i = 1; i <= row; i++)
        for(int j = 1; j <= col; j++)
        {
            cin >> a[i][j];
        }
    int numtest;
    cin >> numtest;
    while(numtest--)
    {
        string s;
        cin >> s;
        solve(s);
    }
    return 0;
}
