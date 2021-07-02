#include <bits/stdc++.h>
#define ll long long
#define lp(i,a,n) for(int i = a , i < n ; ++i )
using namespace std;
int wm , n , t ;
vector <int> numbers ;
int mmry[10005][305];

int main()
{
    ios::sync_with_stdio(0);
    cin >> wm >> n ;
    lp(i,0,n) {
        cin >> t;
        numbers.push_back(t);

    }
    lp(i,1,n+1)
        lp(j,i,wm+1) {
            mmry[i][j] = max(mmry[i][j-] )
    }

    return 0;
}
