#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

vector<int> prefix(const string &p){
    vector<int> s(p.size());
    int border = 0;
    s[0] = 0;
    for(int i = 1; i < p.size(); ++i){
        while(border > 0 && p[i] != p[border]){
            border = s[border-1];
        }
        if(p[i] == p[border]) border++;
        else border = 0;
        s[i] = border;
    }
    return s;
}


// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  vector<int> tmp = prefix(pattern + "$" + text);
  int ln = pattern.size();
  for(int i = ln+1; i < tmp.size();++i){
    if(tmp[i]==ln) result.push_back(i-2*ln);
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
