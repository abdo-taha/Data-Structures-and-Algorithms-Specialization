#include <bits/stdc++.h>

using namespace std;


map<double , pair<int,int> > values;
vector<double> a ;
int main()
{
    ios::sync_with_stdio(0);
    int n , w , t1 , t2 ;
    double t , c = 0;
    cin >> n >> w ;
    for(int i = 0 ; i < n;++i)
    {
        cin >> t1 >> t2 ;
        t =( (double) t1) / t2 ;
        values[t].first += t1 ;
        values[t].second += t2 ;
        a.push_back(t) ;

    }

    sort(a.begin(),a.end());
    vector<double>::iterator it = a.end() ;
    --it ;
    int tt ;
    for(;it >= a.begin();--it)
    {
        tt = values[*it].second ;
        if( tt <= w )
        {
            c += values[*it].first ;
            w -= tt ;
        }
        else
        {
            c +=  (  (double) values[*it].first )/ values[*it].second * w ;
            w = 0 ;
        }
    }

    printf("%.3f",c);

    return 0;
}
