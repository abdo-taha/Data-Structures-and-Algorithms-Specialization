#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef map<char, int> edges;
typedef map<int,edges> trie;
map<int,bool> isLeaf;
map<int,int> bgn;
trie ourTrie;

void build_trie(const string& text) {

  int cnt = 1;
  int i = 0;
  for(;i<text.size();++i){
    int j = i;
    int current = 0;
    for(;j<text.size();++j ){
        char ch = text[j];
        bool found = 0;
        for(auto& p: ourTrie[current]){
            if(p.first==ch){
                found = 1;
                current = p.second;
                break;
            }
        }
        if(!found){
            bgn[cnt] = i;
            ourTrie[current][ch] = cnt;
            current = cnt++;
        }
    }
        isLeaf[current] = 1;
  }

}



// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<pair<int,int>> blabla;
int lst = 0;

void dfs(int pos){
    if( ourTrie[pos].size()==0 || ourTrie[pos].size()> 1 ){
        if(lst!=0){
            blabla.push_back({lst,bgn[pos]-lst});
            lst=bgn[pos];
        }
    }
    for(auto&p:ourTrie[pos]){
        if( ourTrie[pos].size()> 1)lst = bgn[pos];
        dfs(p.second);
    }
}

void ComputeSuffixTreeEdges(const string& text) {

  build_trie(text);
  dfs(0);

}

int main() {
  string text;
  cin >> text;
  ComputeSuffixTreeEdges(text);
  for (int i = 0; i < blabla.size(); ++i) {
    cout << blabla[i].first << " " << blabla[i].second << endl;
  }
//  for (size_t i = 0; i < ourTrie.size(); ++i) {
//        for (const auto & j : ourTrie[i]) {
//          cout << i << "->" << j.second << ":" << j.first << "\n";
//        }
//    }

  return 0;
}
