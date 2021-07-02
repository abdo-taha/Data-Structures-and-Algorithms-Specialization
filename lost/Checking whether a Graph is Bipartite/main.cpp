#include <bits/stdc++.h>
using namespace std;
const int OO = (int) 1e9;
#define lp(i,a,n) for(long long i = a ; i < n ; ++i)
typedef vector<int> vi ;
typedef long long ll;

int n , m , a,b ;
vector<vi> vs ;
map<int,bool> visited , cols ;
bool good = 1 ;


void bfs( int x  ){
    visited[x] = 1 ;
    queue< int > q ;
    cols[x] = 0 ;
    q.push(x) ;

    int tx  ;
    bool c ;

    while(!q.empty()){

        tx = q.front() ;
        c = cols[tx] ;
        q.pop();

        lp(i,0, vs[tx].size() ){

            int nx =  vs[tx][i] ;
            if(!visited[ nx ]){
                visited[nx] = 1 ;
                cols[nx] = !c;
                q.push( nx );

            }
            else {
                if( cols[nx] == c ) {
                    good = 0 ;
                    return ;
                }
            }
        }
    }



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

    lp(i,1,n+1){
        if(!visited[i]){
            bfs(i) ;
        }
    }
    cout << good ;









    return 0;
}
