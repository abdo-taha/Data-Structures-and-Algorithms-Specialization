#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    int d , m , n , lastfuel = 0 , currentd = 0 , lastd = 0 , c = 0 ;
    bool achieve = 1 ;
    cin >> d >> m >> n ;
    for(int i = 0 ; i <= n ;++i )
    {
        if(i < n)cin >> currentd ;
        else currentd = d ;
    //cout << lastfuel << ' '<<  lastd << ' ' << currentd << endl ;
        if( currentd - lastd  > m )
        {
            achieve = 0 ;

        }
        else
        {
            if( currentd - lastfuel  <= m )
                {

                }
            else
            {
                lastfuel = lastd;
                ++c;
            }
        }

    lastd = currentd ;

    }

    if(achieve)cout << c ;
    else cout << -1 ;
    return 0;
}
