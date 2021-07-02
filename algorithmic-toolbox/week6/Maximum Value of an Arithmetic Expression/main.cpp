#include <bits/stdc++.h>
#define ll  long long
using namespace std;
vector<ll> numbers ;
vector<char> op ;
ll t ;
char c;

ll mx [35][35] , mn [35][35];
bool visited[35][35];
ll sol( ll a , ll b , char c ) {
    if(c == '+') return a + b;
    if(c == '-') return a - b;
    else return a * b ;

}

void solve( ll first , ll last ) {
    //cout << first << ' ' << last << endl;
    if(first==last) {
        mx[first][first] = numbers[first];
        mn[first][first] = numbers[first];
        return;
    }
    mx[first][last] = -100000000;
    mn[first][last] =  100000000;
    for(ll i = first ; i < last ; ++i ) {

       if(!visited[first][i]) solve(first,i) ;
       if(!visited[i+1][last]) solve(i+1,last);
       ll n1 = sol( mx[first][i] , mx[i+1][last] , op[i] ) ;
       ll n2 = sol( mx[first][i] , mn[i+1][last] , op[i] ) ;
       ll n3 = sol( mn[first][i] , mn[i+1][last] , op[i] ) ;
       ll n4 = sol( mn[first][i] , mx[i+1][last] , op[i] ) ;
       mx[first][last] = max(mx[first][last]  , max( n1 , max( n2 ,max( n3 , n4) ) ) );
       mn[first][last] = min(mn[first][last]  , min( n1 , min( n2 ,min( n3 , n4) ) ) );



    }
    visited[first][last] = 1;


}



int main()
{

    string s;
    cin >> s;
    ll n = s.size();
    istringstream iss (s) ;
    for(ll i = 0 ; i < n /2 ; ++i) {
        iss >> t >> c;
        numbers.push_back(t);
        op.push_back(c);
    }
    iss >> t ;
    numbers.push_back(t);



    solve(0,op.size());
//    for(int i = 0 ; i <6 ; ++i) {
//        for(int j = 0 ; j < 6 ; ++j){
//            cout << mx[i][j] << ' ' ;
//        }
//        cout << endl;
//    }
//    cout << endl;
//    for(int i = 0 ; i <6 ; ++i) {
//        for(int j = 0 ; j < 6; ++j){
//            cout << mn[i][j] << ' ' ;
//        }
//        cout << endl;
//    }
cout << mx[0][op.size()];



    return 0;
}
