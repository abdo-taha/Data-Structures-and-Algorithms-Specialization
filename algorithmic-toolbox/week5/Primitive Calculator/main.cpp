#include <bits/stdc++.h>

using namespace std;
int numbers[1000005] = {0,0,1,1};
int backtrack[1000005] = {0, 0 , 1 , 1};
vector<int> print ;

void solve(int i) {
    int c = 1 , a = 0, b  = 0;
    vector<int> t ;
    t.push_back(numbers[i-1]+1);
    if(i %3 == 0) {
        ++c;
        t.push_back(numbers[i/3]+1);
        b = numbers[i/3]+1 ;
    }
    if(i %2 == 0) {
        ++c;
        t.push_back(numbers[i/2]+1);
        a = numbers[i/2]+1;
    }
    int  mn = t[0];

    for(int j = 1 ; j < c ; ++j) {
        if(t[j] < mn) {
            mn = t[j] ;
        }
    }
    numbers[i] = mn;

    if(mn == a ) backtrack[i] = i/2;
    else if( mn == b ) backtrack[i] = i/3;
    else backtrack[i] = i-1;



}


void moveback(int i) {
        print.push_back(i);5
        while(i>1) {
            print.push_back(backtrack[i]);
            i = backtrack[i];
        }


}


int main()
{
    int n;
    cin >> n;
    for(int i = 4 ; i < n+3 ; ++i) {
        solve(i);
    }
    moveback(n);
    cout << numbers[n] << endl ;

    for(int i = (int)print.size()-1 ; i >= 0 ; --i ) {

        cout << print[i] << ' ';
    }
    cout << endl;

    return 0;
}
