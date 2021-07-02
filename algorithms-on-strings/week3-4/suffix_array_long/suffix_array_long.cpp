#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.




void count_sort(vector<int> & p, vector<int>& c){
    /**
        takes string sorted base of second half (as an optimization)
        count first number <= n
        for every number calculate first pos of it
        for every pair put it in it's pos and update pos
    **/
    int n = p.size();
    vector<int> cnt(n,0);
    for(int x:c) ++cnt[x];
    vector<int> pos(n,0);
    for(int i= 1; i < n ; ++i){
        pos[i] = pos[i-1] + cnt[i-1];
    }

    vector<int> np(n);
    for(int x:p){
        np[pos[c[x]]] = x;
        ++pos[c[x]];
    }
    p = np;

}


vector<vector<int>> suff(const string &s){
    /// add smaller ch
//    s += "$";
    int n = s.size();

    vector<int> p(n),c(n); /// pos compare
    /// sort strings of size 1
    /// p is the original pos but sorted lexo..
    /// c is for comparing starts from 0 and ++ for next char
    {
        vector<pair<char,int>> tmp(n);
        for(int i = 0; i < n; ++i) tmp[i] = {s[i],i};
        sort(tmp.begin(),tmp.end());
        for(int i = 0; i < n; ++i) p[i] = tmp[i].second;
        c[p[0]] = 0;
        for(int i = 1; i < n; ++i){
            if(tmp[i].first == tmp[i-1].first) c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]] + 1;
        }
    }

    /// binary
    /// each level we know sorting of /2 so just compare order of two halfs
    int k = 0;

    while((1<<k) < n){
        for(int &x:p ) x = (x - (1<<k) + n ) %n;
        /// it's sorted by first pos so if we shift that pos with same length it's double string sorted by second half
        /// optimization for count sort
        count_sort(p,c);

        vector<int> nc(n,0);
        /**
            p is computed
            same as computing c above but to compare which is smaller we use the old order of it's two halfs
            same order means same string
        **/
        for(int i = 1; i < n; ++i){
            pair<int,int> p1 = { c[ p[i] ] , c[ (p[i] + (1<<k) ) %n ] }  , p0 = {c[ p[i-1] ],c[ (p[i-1] + (1<<k) ) %n]};
            if(p0==p1) nc[p[i]] = nc[p[i-1]];
            else nc[p[i]] = nc[p[i-1]] + 1;
        }
        c = nc;

        ++k;
    }

    vector<vector<int>> ans;
    ans.push_back(p);
    ans.push_back(c);
    return ans;

}





vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  // Implement this function yourself
  result = suff(text)[0];
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
