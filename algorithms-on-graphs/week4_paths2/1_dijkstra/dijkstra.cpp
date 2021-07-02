#include <iostream>
#include <vector>
#include <queue>


using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::make_pair;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  int n = cost.size();
  vector<int> mn(n,100000000);
  mn[s] = 0;
  priority_queue<pair<int,int>> pq;
  pq.push(make_pair(0,s));
  while(pq.size()){
    int cur = pq.top().second;
    int cst = pq.top().first;
    pq.pop();
    for(int j = 0; j < adj[cur].size();++j){
        int nxt = adj[cur][j];
        if(mn[nxt] > cst + cost[cur][j]){
            mn[nxt] = cst + cost[cur][j];
            pq.push(make_pair(cst + cost[cur][j],nxt));
        }
    }
  }
  if(mn[t]!=100000000) return mn[t];
  return -1;
}

int main() {

    freopen( "ans.txt" , "w" , stdout ) ;
    freopen( "output.txt" , "r" , stdin ) ;

  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  /** for test another code **/
  int tmp; std::cin >> tmp;
  while(tmp--){
      std::cin >> s >> t;
      s--, t--;
      std::cout << distance(adj, cost, s, t) <<"\n";

  }
}
