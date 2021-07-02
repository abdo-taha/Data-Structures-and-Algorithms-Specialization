#include <bits/stdc++.h>

using namespace std;
int cost[1005] = {0,1,2,1,1};

int main()
{
    int n ;
    cin >> n;
    for(int i = 5; i <= n +3 ; ++i) {
        cost[i] = min( cost[i-1]+1,min( cost[i-3]+1,cost[i-4]+1 ) );

    }
     cout << cost[n]<<endl;
    return 0;
}
