#include <iostream>

using namespace std;
int d[10], ans;
int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        d[x]++;
        if(d[x] > ans) ans = d[x];
    }
    for(int i = 0; i <= 9; i++)
    if(d[i] == ans) {
        cout << i;
        break;
    }
}
