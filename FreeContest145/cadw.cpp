#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn = 1e5 + 5;
int n, k;
ll a[maxn], Sum[maxn], Left[maxn], Right[maxn];
int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if(i < k) Sum[i] += Sum[i - 1] + a[i];
        else
        {
            Sum[i] = Sum[i - 1] + a[i] - a[i - k];
            Left[]
        }
    }
    for(int i = k; i <= n; i++) Sum[i] = s[i] - s[i - k];

    return 0;
}


