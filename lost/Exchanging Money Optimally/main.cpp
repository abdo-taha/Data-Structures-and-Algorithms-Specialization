#include <bits/stdc++.h>
using namespace std;
const long long OO = (long long) 1e18;
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

int n , m , fr , to , w ,  a , b, last;
vll costs ;
vector< vector< pair<ll,ll> > > edges ;
bool change ;
vll prv ;
vector<bool> nve;


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

    if(change){
        while(1){

            bool br = 1 ;
            lp(i,1,n+1){
                rep( k , edges[ i ] ) {
                    to = edges[i][k].first ;
                    w = edges[i][k].second;

                    if( costs[to] > costs[i] + w  ){
                        costs[to] = w + costs[i];
                        if(!nve[to]){
                            br = 0 ;
                            nve[to] = 1 ;
                        }
                    }

                }
            }
            if(br) break ;
        }
    }

}


void correct(){
    map<int,bool> vst ;
    queue<int> q ;
    q.push(a);
    while(!q.empty()){
        int x = q.front();
        q.pop();
        vst[x] = 1 ;
        rep(i,edges[x]){
            if(!vst[ edges[x][i].first ]){
                q.push( edges[x][i].first ) ;
                vst[  edges[x][i].first ] = 1 ;
            }
        }
    }
    lp(i,1,n+1) if(!vst[i]) costs[i] = OO;


}

void allnve(){
    while(1){
        bool br = 1 ;
        lp(i,1,n+1){
            if(nve[i]) rep(j,edges[i]) {
                if( nve[edges[i][j].first ] ==0 ) br =0 ;
                 nve[ edges[i][j].first ] = 1 ;
            }
        }
        if(br) break;
    }

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m ;

    edges.resize(n+1);
    prv.resize(n+1);
    costs = vll(n+1,OO);
    nve = vector<bool> (n+1,0) ;


    lp(i,0,m){
        cin >> fr >> to >> w ;
        edges[fr].push_back({to,w});

    }
    cin >> a ;

    costs[a] = 0 ;
    prv[a] =  -1 ;
    nvecycle();

    correct();
    allnve();

    lp(i,1,n+1){

        if( costs[i] == OO ) cout << "*\n";
        else if(nve[i]) cout << "-\n";
        else cout << costs[i] << "\n";
    }







    return 0;
}

