#include <iostream>
#include <map>
using namespace std;
map < long long, int > mp;
int main()
{
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        long long x; cin >> x;
        mp[x]++;
        if(mp[x] >= 2) {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";
    return 0;
}
