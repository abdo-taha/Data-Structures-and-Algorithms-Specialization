#include <bits/stdc++.h>
using namespace std;
vector<int> numbers ;
int main()
{
    ios::sync_with_stdio(0) ;

    long long n , t  , m = 10 ;
    cin >> n ;
    int i = 3 ;
    numbers.push_back(0) ;
    numbers.push_back(1) ;
    numbers.push_back(1) ;
    while(1)
    {
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
    unsigned long long s = 0 , sum;
    vector<int>::iterator it = numbers.begin();
    for(;it != numbers.end(); ++it)
    {
        s += (*it) * (*it) ;
    }

    int l = numbers.size() ;
    sum = n / l * s ;

    for(int j = 0 ; j <= n % l ; ++j)
    {
        sum += numbers[j] * numbers[j] ;
    }
    cout << sum % 10 ;


    return 0;
}
