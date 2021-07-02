#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}


typedef map<char, int> edges;
typedef map<int,edges> trie;
map<int,bool> isLeaf;

trie ourTrie;

void build_trie(const vector<string> & patterns) {

  int cnt = 1;
  for(const auto & pattern : patterns){
    int current = 0;
    for(auto &ch: pattern ){
        bool found = 0;
        for(auto& p: ourTrie[current]){
            if(p.first==ch){
                found = 1;
                current = p.second;
                break;
            }
        }
        if(!found){
            ourTrie[current][ch] = cnt;
            current = cnt++;
        }
    }
        isLeaf[current] = 1;
  }

}



vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
    build_trie(patterns);
    for(int i = 0; i < (int) text.size(); ++i){
        int j = i, current = 0;
        while(j < (int) text.size()){
            bool found = 0;
            for(auto& pr: ourTrie[current] )if(pr.first == text[j]){
                ++j; current = pr.second; found = 1; break;
            }
            if(isLeaf[current] || ourTrie[current].size()==0){
                result.push_back(i);
                break;
            }
            if(!found) break;
        }
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
