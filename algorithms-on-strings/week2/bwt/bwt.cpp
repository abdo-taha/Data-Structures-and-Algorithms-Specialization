#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
    string result = "";
    int len = text.size();
    vector<string> cycle;
    for(int i = 0; i < len; ++i){
        cycle.push_back(text.substr(i)+text.substr(0,i));
    }
    sort(cycle.begin(),cycle.end());
    for(string &s : cycle) result += s[len-1];
    return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
