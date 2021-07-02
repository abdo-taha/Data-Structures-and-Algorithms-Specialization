#include <bits/stdc++.h>

using namespace std;

vector<int> a , b ;

int main()
{
    ios::sync_with_stdio(0);
    int n , t ;
    unsigned long long c = 0 ;
    cin >> n ;
    for(int i = 0 ; i < n ;++i)
    {
        cin >> t ;
        a.push_back(t);
    }
    for(int i = 0 ; i < n ;++i)
    {
        cin >> t ;
        b.push_back(t);
    }
    sort(a.begin(),a.end() ) ;
    sort(b.begin(),b.end()) ;
    vector<int>::iterator it1 = a.begin() , it2 = b.begin() ;
    for(int i = 0 ; i < n ; ++i)
    {
        c += 1ll**it1 * *it2 ;
        ++it1;
        ++it2;
    }

    cout << c;

    return 0;
}
