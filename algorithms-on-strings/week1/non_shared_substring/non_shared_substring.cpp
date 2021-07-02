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

using namespace std;

vector<map<char,int>> nodes(1);
vector<pair<int,int>> edges(1);
map<int,int> frst,nxt_;
int ln1;

int type(int pos){
    return pos < ln1 ? 1 : 2;
}


pair<int,int> dfs(int cur){
    int ty = 0,ln = ln1;
    if(nodes[cur].size()==0) ty = type(edges[cur].first);
    for(auto & p : nodes[cur]){
        if(p.first == '#') ty |= 1;
        if(p.first == '$') ty |= 2;
        if(p.first == '#' || p.first == '$') continue;
        pair<int,int> tmp = dfs(p.second);
        ty = ty | tmp.first;
        if(tmp.first==1){
           ln = 1;
            nxt_[cur] = p.second;
        }
        else if(tmp.first != 2){
            if(tmp.second < ln){
                ln = tmp.second;
                nxt_[cur] = p.second;
            }
        }

    }
    if(ty == 1){
        ln = 1;
    }else {
        ln += edges[cur].second;
    }
    return {ty,ln};
}



string get_ans(string &s , int ln , int cur){
    string ans = "";
    int curln = edges[cur].second , pos = edges[cur].first;
    if(ln <= curln){
        ans += s.substr(pos,ln);
        return ans;
    }
    ans += s.substr(pos,curln);
    ans += get_ans(s,ln-curln,nxt_[cur]);
    return ans;

}


string solve (string p, string q)
{
    /** creating suffix tree **/
    string text = p + "#" + q + "$";
    int cur = 0 , pos = 0, l, ln = text.size();
    ln1 = p.size()+1;

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
                    frst[nxt] = i;
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
                    frst[nxt] = frst[cur];

                    nxt = nodes.size();
                    nodes[cur][ text[j] ] = nxt;
                    nodes.push_back(map<char,int>());
                    edges.push_back({j,ln-j});
                    frst[nxt] = i;

                    cur = l = pos = k = 0;
                    break;

                }
            }
        }
      }

    ln = dfs(0).second;
    return  get_ans(text,ln,0);

}


void print_tree(string s){
    for(int i = 0 ; i < edges.size(); ++i) cout <<i <<  " " << s.substr(edges[i].first,edges[i].second) << "\n";
    cout << "...........................................\n";
    for(int i = 0; i < nodes.size(); ++i){
        cout << i << " : \n";
        for(auto &p : nodes[i]) cout << p.first << " " << p.second << "\n";
        cout << "\n";
    }
}


int main (void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p, q);


	cout << ans << endl;

	return 0;
}
