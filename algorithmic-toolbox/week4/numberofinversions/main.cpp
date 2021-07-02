#include <bits/stdc++.h>

using namespace std;
int c;
void Merge(vector<int> &a , vector<int> a1 , int n1 , vector<int>a2 , int n2) {

    int i = 0 , j = 0 , k = 0;
    while(i < n1 && j < n2) {
            //cout << a1[i] <<' ' <<a2[j] << ' ';
        if(a1[i] <= a2[j]) {
            a[k] = a1[i];
            ++i;
            ++k;
        }
        else {
            a[k] = a2[j];
            ++j;
            ++k;
            c += n1-i ;
        }
    //cout << c<<endl;
    }

    //c += (n1 - i) * (n2-1);
    while(i < n1){
        a[k] = a1[i];
        ++i;
        ++k;

        //cout << a1[i-1]  << ' ' << c << endl;
    }
    while(j < n2) {
        a[k] = a2[j];
        ++j;
        ++k;
    }
}


void mergesort( vector<int> &a, int n)
{
    if(n==1) return;
    int m = n / 2;
    vector<int> a1 , a2;
    for(int i = 0 ; i < m ; ++i)
        a1.push_back(a[i]) ;
    for(int i = m ; i < n ; ++i)
        a2.push_back(a[i]);
    mergesort(a1,m);
    mergesort(a2,n-m);
    Merge(a,a1,m,a2,n-m);
}


int main()
{
    vector<int> a ;
    int n , t;
    cin >> n;
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> t;
        a.push_back(t);
    }
    mergesort(a,n);
    cout << c;
    //for(int i = 0 ; i < n ; ++i)
      //  cout << a[i] << ' ';
    return 0;
}
