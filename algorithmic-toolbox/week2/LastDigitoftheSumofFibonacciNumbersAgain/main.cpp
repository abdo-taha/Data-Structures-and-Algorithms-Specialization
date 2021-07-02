#include <bits/stdc++.h>
using namespace std;
vector<int> numbers ;

int solve( long long n )
{
    long long  t  , m = 10 ;
    int i = 3 ;
    numbers.push_back(0) ;
    numbers.push_back(1) ;
    numbers.push_back(1) ;
    while(1)
    {
      //  cout <<1;
        t = numbers[i-1] + numbers[i-2] ;
        t %= m ;
        if( t == 1 && numbers[i-1] == 1 && numbers[i-2] == 0 )
        {
            numbers.pop_back() ;
            numbers.pop_back() ;
            break ;
        }
        else
            numbers.push_back(t) ;
        ++i;


    }
    long long s = 0 , sum;
    vector<int>::iterator it = numbers.begin();
    for(;it != numbers.end(); ++it)
    {
        s += *it ;
        s%=10;
    }

    int l = numbers.size() ;
    sum = n / l * s ;
    s %=10;

    for(int j = 0 ; j <= n % l ; ++j)
    {
        sum += numbers[j] ;
    }
    numbers.clear() ;
    return sum %10;
}

int main()
{
    ios::sync_with_stdio(0) ;

    long long n , m ;
    cin >> n >> m ;
    --n ;

    cout <<  (solve(m) -solve(n)+10)%10 ;


    return 0;
}
