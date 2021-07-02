#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using std::map;
using std::vector;
using std::string;



typedef map<char, int> edges;
typedef vector<edges> trie;


trie build_trie(const vector<string> & patterns) {
  trie t;
  t.resize(1);
  for(const string &pattern : patterns){
    int cur = 0;
    for(const char &ch : pattern){
        int nxt = t[cur][ch];
        if(nxt != 0) cur = nxt;
        else{
            t[cur][ch] = t.size();
            cur = t.size();
            t.push_back(edges());
        }
    }
  }


  return t;
}


vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	trie tr = build_trie(patterns);
    for(int i = 0 ; i < text.size();++i){
        int cur = 0,j = i;
        bool found = false;
        while(j < text.size()){
            int ch = text[j];
            int nxt = tr[cur][ch];
            if(nxt!=0){
                cur = nxt;
                if(tr[cur]['$']){
                    found = true;
                    break;
                }
                ++j;
            }
            else break;
        }
        if(found) result.push_back(i);


    }
    return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
		patterns[i] += '$';
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
