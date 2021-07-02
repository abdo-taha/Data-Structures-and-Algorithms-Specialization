#include <bits/stdc++.h>

using namespace std;

long long gc( long long a , long long b )
{
    if( a % b  == 0 ) return b ;
    return gc( b , a % b ) ;

}
int main()
{

    long long a , b  ;
    cin >> a >> b ;
    cout << a * b / gc(max(a,b) , min(a,b));


    return 0;
}
