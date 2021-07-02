#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::pair;
using std::cout;

#define debugVec(vec) cout<<(#vec)<<": "; for (auto& i: vec) cout<<i<<" "; cout<<"\n"

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


vector<int> LCP(vector<vector<int>> &pc, string s){
    /// O(n)
    int n = s.size();
    vector<int> lcp(n); /// longest common prefix
    int k = 0;
    for(int i = 0; i < n - 1 ; ++i){
        int pi = pc[1][i]; /// c[i] = order of pos i in p (will be unique as all sub are now unique)
        if(pi == 0) continue;
        int j = pc[0][pi-1]; /// pos of the previous suff
        /// common pre in pos i and previous suff in suff-array
        while( i + k < n && j + k < n &&  s[i+k] == s[j+k]) ++k;
        lcp[pi] = k;
        /// i+1 can have at least k-1 common pre
        k = std::max(0,k-1);
    }
    return lcp;

}




int cmp(const string &pattern , int pos, const string &text){ /// (pattern < text) -1  == 0  (pattern>text)  1
    int p1 = 0;
    while(p1 < pattern.size() && pos < text.size()){
        if(pattern[p1]==text[pos]){
            ++pos;
            ++p1;
        }
        else if(pattern[p1] < text[pos]){
            return -1;
        }else{
            return 1;
        }
    }
    if(p1 == pattern.size() ) return 0;
    return 1;
}



vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array, vector<int>&lcp) {
  vector<int> result;

  // write your code here
  int l = 0,r = suffix_array.size()-1,md;
  while(l <= r){
    md = (l+r)/2;
//    printf("%d %d\n",suffix_array[md], cmp(pattern,suffix_array[md],text));
    if(cmp(pattern,suffix_array[md],text) <= 0) r = md-1;
    else l = md+1;
  }
  if(cmp(pattern,suffix_array[l],text) == 0) {
//    cout << l << "\n";
    while( lcp[l+1] >= pattern.size()){
        result.push_back(suffix_array[l]);
        ++l;
    }
    result.push_back(suffix_array[l]);
  }
  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<vector<int>> pc = suff(text);
  vector<int> &suffix_array = pc[0], lcp = LCP(pc,text);
//  debugVec(suffix_array);
//  debugVec(lcp);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);

  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array,lcp);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
