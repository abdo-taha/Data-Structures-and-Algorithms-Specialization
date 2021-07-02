#include <bits/stdc++.h>
using namespace std;
const int OO = (int) 1e9;
#define lp(i,a,n) for(long long i = a ; i < n ; ++i)
typedef vector<int> vi ;
typedef long long ll;

int n , m , a,b ;
vector<vi> vs ;
map<int,bool> visited ;

int bfs( int x  ){
    visited[x] = 1 ;
    queue< pair<int,int> > q ;
    q.push({x,0}) ;
    pair<int,int> p ;
    int tx , tc ;

    while(!q.empty()){

        p = q.front();
        q.pop();
        tx = p.first ;
        tc = p.second ;

        if(tx == b) return tc ;

        lp(i,0, vs[tx].size() ){
            int nx =  vs[tx][i] ;
            if(!visited[ nx ]){
                visited[ nx ] = 1 ;
                q.push( { nx , tc +1  } ) ;
            }
        }
    }
    return -1 ;


}


int main()
{
    ios::sync_with_stdio(0);
    //freopen( "output.txt" , "w" , stdout ) ;
    cin >> n >> m ;


    vs = vector<vi>(n+3);


    lp(i,0,m){
        cin >> a >> b ;
        vs[a].push_back(b);
        vs[b].push_back(a);
    }

    cin >> a >> b ;
    cout << bfs(a);









    return 0;
}
