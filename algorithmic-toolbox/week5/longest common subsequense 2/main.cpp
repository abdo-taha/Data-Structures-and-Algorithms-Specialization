#include <bits/stdc++.h>

using namespace std;
int board[1002][1002];
vector<int> a ,b;

int main()
{
    int n1 , n2 ,t;
    cin >> n1 ;
    for(int i = 0 ; i < n1; ++i) {
        cin >> t;
        a.push_back(t);
    }
    cin >> n2 ;
    for(int i = 0 ; i < n2 ; ++i) {
        cin >> t;
        b.push_back(t);
    }
//    for(int i = 1 ; i <= n1 ; ++i)
//        if(a[i-1] == b[0] ) board[0][i] = 1 ;
//    for(int i = 1 ; i <= n2 ; ++i)
//        if(a[0] == b[i-1]) board[i][0] = 1 ;


    for(int i = 1 ; i <= n2 ; ++i)
        for(int j = 1 ; j <= n1 ; ++j) {
        board[i][j] = max(board[i-1][j],board[i][j-1]);
        if(b[i-1]==a[j-1]) board[i][j] = max(board[i-1][j-1]+1,board[i][j]);
        else board[i][j] = max(board[i-1][j-1],board[i][j]);
    }
    cout << board[n2][n1];



    return 0;
}
