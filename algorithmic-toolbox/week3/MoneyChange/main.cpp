#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);

    int n  , c;
    cin >> n ;
    c = n / 10 ;
    n %=  10 ;
    c += n /5 ;
    n %= 5 ;
    c += n ;
    cout << c ;

    return 0;
}
