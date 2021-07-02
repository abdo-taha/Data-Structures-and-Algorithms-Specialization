#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::pair;

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  int cur = 0 , pos = 0, l, ln = text.size();
  vector<map<char,int>> nodes(1);
  vector<pair<int,int>> edges(1);
  for(int i = 0; i < ln; ++i){
    cur = 0; /// current node
    l = 0; /// current edge lenght
    pos = 0; /// start position of edge
    int k = 0; /// index from 0 to l
    for(int j = i; j < ln; ++j){
        if(k >= l){ /// end of current edge
            int nxt = nodes[cur][text[j]];
            k = 0;
            if(nxt){
                cur = nxt;
                l = edges[cur].second;
                pos = edges[cur].first;
                --j;
            }
            else{
                nxt = nodes.size();
                nodes[cur][text[j]] = nxt;
                nodes.push_back(map<char,int>());
                edges.push_back({j,ln-j});
                break;
            }
        }
        else{
            if(text[j] == text[pos+k])++k;
            else{
                int nxt = nodes.size();
                nodes.push_back(map<char,int>());
                edges.push_back({pos+k,l-k});
                edges[cur].second = k;

                for(auto &p : nodes[cur]) nodes[nxt][p.first] = p.second;
                nodes[cur].clear();
                nodes[cur][text[pos+k]] = nxt;

                nxt = nodes.size();
                nodes[cur][ text[j] ] = nxt;
                nodes.push_back(map<char,int>());
                edges.push_back({j,ln-j});

                cur = l = pos = k = 0;
                break;

            }
        }
    }
  }

  for(pair<int,int> &p : edges){
    if(p.second) result.push_back(text.substr(p.first,p.second));
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
