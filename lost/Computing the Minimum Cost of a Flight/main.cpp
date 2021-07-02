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

void dikstra(  ){
    priority_queue<pii> q;
    q.push({0,a});
    while(!q.empty()){
        pii p = q.top();

        q.pop();

        rep(i, edges[ p.second ] ){
                int val = -p.first  + edges[p.second][i].second ;

                if( costs[ edges[p.second][i].first ] > val ){
                    costs[ edges[p.second][i].first ]  = val ;
                    q.push( { - val, edges[p.second][i].first } ) ;

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
    cin >> a >> b ;
    costs[a] = 0 ;
    dikstra();
    if(costs[b] != OO)cout << costs[b] ;
    else cout << -1 ;







    return 0;
}

