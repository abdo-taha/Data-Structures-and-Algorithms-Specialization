#include <bits/stdc++.h>

using namespace std;

vector<long long> numbers ;
long long n ,m, t;
long long binary(long long number ,long long mm , long long nn )
{

    while(1){

    if(nn-mm<=0 && numbers[mm]!=number)
    {
        return -1;
    }


    long long index = (nn + mm ) / 2;

    if(numbers[index]==number) return index ;
    else if( numbers[index] > number )
        nn = index -1 ;
    else
        mm = index +1 ;
    }

}
int main()
{
    cin >> n;
    for(long long i = 0 ; i<n ; ++i)
    {
        cin >> t;
        numbers.push_back(t);
    }

    cin >> m;
    for(long long i =0;i<m;++i )
    {
        cin >> t ;
        t = binary(t,0,n-1);
        cout << t << ' ';

    }
    return 0;
}
