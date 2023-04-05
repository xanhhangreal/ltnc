#include <iostream>

using namespace std;

int main()
{
    //freopen(".inp", "r", stdin);
    int rong, cao, n;
    cin >> rong >> cao >> n;
    int cnt = 0;
    while(n--)
    {
        int x, y, w, h;
        cin >> x >> y >> w >> h;
        if(x > rong || x < 0 || y < 0 || y > cao ||
            (x == rong && w > 0) || (y == cao  && h > 0)) cnt++;


    }
    cout << cnt;
    return 0;
}
