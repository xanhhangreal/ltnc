#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        int a[n + 5], b[n + 5];
        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= n; i++) cin >> b[i];
        if(n == 1) cout << "Yes\n";
        else
        {
            int ok = true;
            for(int i = 1; i <= n - 1; i++) if(a[i] > a[n]) swap(a[i], b[i]);
            for(int i = 1; i <= n - 1; i++) if(b[i] > b[n]) swap(a[i], b[i]);
            for(int i = 1; i <= n; i++)
            {
                if(a[i] > a[n] || b[i] > b[n])
                {
                    ok = false;
                    break;
                }
            }
            cout << (ok == true ? "Yes\n" : "No\n");
        }
    }
}
