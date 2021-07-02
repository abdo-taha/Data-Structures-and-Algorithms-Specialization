#include <bits/stdc++.h>

using namespace std;
int n , m ,t1,t2;
vector<pair<int,int> > numbers;
//map<int,int> a;
bool s( pair<int,int> a ,pair<int,int> b  ) {
    return a.first < b.first ;
}
int last( int t) {
    int a = 0 , b = n-1;
    while(b>=a){
        int c = (a+b)/2;
        if((numbers[c].first<=t&&c+1 < n && numbers[c+1].first > t) || (numbers[c].first <= t && c == n-1))
            return c;
        else if (numbers[c].first > t&&c>0)
            b = c - 1 ;
        else if(c<n)
            a = c+1;
        if(b-a == 0 && numbers[a].first<=t) return a;
        if(b-a == 0 && numbers[a].first>t) return 0 ;
    }

}
int many ( int t  ) {
    int c = 0 ;
    int k = last(t);
    for(int i = 0 ; i <=  k ; ++i)
    {
        if(t>= numbers[i].first&& t<= numbers[i].second) ++c;
    }
    return c;

}

int main()
{

    cin >> n >> m;
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> t1 >> t2;
        numbers.push_back(make_pair(t1,t2));
        //for(int j = t1 ; j <= t2 ; ++j)
          //  ++a[j];
    }
    sort(numbers.begin(),numbers.end(),s);
    for(int i = 0 ; i < m ; ++i) {
        cin >> t1;
        cout << many(t1) << ' ' ;
    }


    return 0;
}
