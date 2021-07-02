#include <bits/stdc++.h>

using namespace std;
vector<int> numbers ;
map<int,bool> taken;

int main()
{

    int n , m = 1 , t;
    cin >> n;
    while( m <= n )
    {
        //cout << n << ' ' << m << endl ;
        if( n - m == m ||n-m >= 0 && taken[n-m]  ||  taken[m] )
        {
            ++m;
        }
        else
        {
            numbers.push_back(m) ;

            n -= m ;
            taken[m] = 1 ;
            ++m;
        }


    }
    cout << numbers.size()<<endl;
    for(vector<int>::iterator it = numbers.begin() ; it != numbers.end() ;++it   )
        cout << *it << ' ';

    return 0;
}
