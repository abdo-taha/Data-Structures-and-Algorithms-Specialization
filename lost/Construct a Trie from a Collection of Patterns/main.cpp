#include <bits/stdc++.h>

using namespace std;

typedef map<char, int> edges;
typedef map<int,edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  int cnt = 1;
  for(const auto & pattern : patterns){
    int current = 0;
    for(auto &ch: pattern ){
        bool found = 0;
        for(auto& p: t[current]){
            if(p.first==ch){
                found = 1;
                current = p.second;
                break;
            }
        }
        if(!found){
            t[current][ch] = cnt;
            current = cnt++;
        }
    }
  }
  return t;
}


int main()
{

    size_t n;
    cin >> n;
    vector<string> patterns;
    for (size_t i = 0; i < n; i++) {
        string s;
        cin >> s;
        patterns.push_back(s);
    }

    trie t = build_trie(patterns);
    for (size_t i = 0; i < t.size(); ++i) {
        for (const auto & j : t[i]) {
          cout << i << "->" << j.second << ":" << j.first << "\n";
        }
    }

    return 0;
}
