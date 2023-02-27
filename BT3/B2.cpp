#include <iostream>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size() - 1;
    for(int i = 0; i <= n; i++) {
        if(s[i] != s[n - i]) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    return 0;
}
