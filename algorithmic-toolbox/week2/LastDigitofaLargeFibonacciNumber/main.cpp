#include <bits/stdc++.h>
using namespace std;
vector<long long> numbers ;
int main()
{
    ios::sync_with_stdio(0) ;
    numbers.push_back(1) ;
    numbers.push_back(1) ;
    long long  n , t ;
    cin >> n ;
    for(int i = 2 ; i < n ; ++i)
    {
        t = numbers[i-1] % 100 + numbers [i -2]% 100 ;
        t %= 100 ;
        numbers.push_back(t) ;
    }
    --n ;
    cout << numbers[n]%10 ;
    return 0;
}
