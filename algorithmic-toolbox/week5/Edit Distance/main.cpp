#include <bits/stdc++.h>

using namespace std;
int board[1002][1002];


int main()
{
    string s1 , s2;
    cin >> s1 >> s2;
    int n1 = s1.length() , n2 = s2.length();

    for(int i = 0 ; i <= n1 ; ++i)
        board[0][i]= i;
    for(int i = 0 ; i <= n2 ; ++i)
        board[i][0]= i;
    for(int i = 1 ; i <= n2 ; ++i) {
        for(int j = 1 ; j <= n1 ; ++j) {
            board[i][j] = min(board[i-1][j],board[i][j-1] ) +1 ;
            if(s2[i-1]==s1[j-1]) board[i][j] = min(board[i][j],board[i-1][j-1]);
            else board[i][j] = min(board[i][j],board[i-1][j-1]+1);
        }
    }
    cout << board[n2][n1];
    return 0;
}
