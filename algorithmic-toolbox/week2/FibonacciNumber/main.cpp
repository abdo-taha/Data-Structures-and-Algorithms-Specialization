#include <bits/stdc++.h>
using namespace std;
vector<unsigned long long int> numbers ;
int main()
{
    ios::sync_with_stdio(0) ;
    numbers.push_back(1) ;
    numbers.push_back(1) ;
    unsigned long long int   n , t ;
    cin >> n ;
    for(unsigned long long int i = 2 ; i < n ; ++i)
    {
        t = numbers[i-1] + numbers [i -2] ;
        numbers.push_back(t) ;
    }
    --n ;
    if(n == -1) cout << 0 ;
    else cout << numbers[n] ;

    return 0;
}
