#include <bits/stdc++.h>
using namespace std;
const int OO = (int) 1e9;
#define lp(i,a,n) for(long long i = a ; i < n ; ++i)
#define rep(i,vec) for(ll i = 0 ; i < vec.size() ; ++i)
#define reprv(i,vec) for(ll i = vec.size()-1; i >=0 ; --i)
#define eps (1e-5)
#define pb(i) push_back(i)
typedef vector<int> vi ;
typedef   long long ll;
typedef vector<ll> vll ;
typedef pair<int,int> pii ;
typedef vector< pair<int,int> >  vpii;

int n , m , fr , to , w ,  a , b;
vi costs ;
vector<vpii> edges ;
bool change ;

void nvecycle(  ){

    lp(j,0,n){
       change = 0 ;
       lp(i,1,n+1){
            rep( k , edges[ i ] ) {
                to = edges[i][k].first ;
                w = edges[i][k].second;
                if( costs[to] > costs[i] + w  ){
                    costs[to] = w + costs[i];
                    change = 1 ;

                }

            }

       }


    }


}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m ;

    edges.resize(n+1);
    costs = vi(n+1,OO);

    lp(i,0,m){
        cin >> fr >> to >> w ;
        edges[fr].push_back({to,w});

    }

    costs[1] = 0 ;
    nvecycle();
    cout << change ;







    return 0;
}

