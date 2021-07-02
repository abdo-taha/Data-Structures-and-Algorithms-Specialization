#include <bits/stdc++.h>

using namespace std;
vector< pair<int,int> > f ;
map<int,int> counter ;
vector<int> solution ;
vector<bool> used ;
int main()
{
    ios::sync_with_stdio(0);
    int n,nn , a , b , mn =1000000005 , mx = 0;
    cin >> n ;
    nn = n ;
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> a >> b ;
        mn = min(a,mn);
        mx = max(b,mx);

        f.push_back( make_pair(a,b) );
        used.push_back(0);
        for(int j = a ; j <= b ;++j)
        {
            ++counter[j];
        }
    }
    int m = 0 , c = 0 , p;
    while(n > 0){
            m = 0 ;
        for(int i = mn ; i <= mx ;++i){
            if(counter[i] > m )
            {
                m = counter[i];
                p = i ;
            }
        }
        solution.push_back(p);
        for(int i = 0 ; i < nn ; ++i)
        {

            a = f[i].first;
            b = f[i].second;
            if(p >= a && p <= b){

                if(!used[i]) {
                    --n;
                    used[i] = 1;
                }

                for(int j = a ; j <= b ; ++j)
                {
                    --counter[j];
                }
            }
        }
        ++c;
    }

    cout << c<<endl;
    for(vector<int>::iterator it = solution.begin() ; it != solution.end() ; ++it)
        cout << *it <<' ' ;
    return 0;
}
