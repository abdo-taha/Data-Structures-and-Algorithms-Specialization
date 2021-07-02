#include <bits/stdc++.h>

using namespace std;

map<int,int> c ;

int main()
{
    int n , t;
    cin >> n ;
    bool yes = 0;
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> t ;
        ++c[t];
        if(c[t] > n / 2) yes = 1;
    }
    cout << yes;

    return 0;
}
