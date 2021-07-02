#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;


vector<int> relax(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<long long> &dist, vector<int> &parent){
    vector<int> relaxed;
    for(int i = 0 ; i < adj.size(); ++i) for(int j = 0 ;j < adj[i].size();++j){
        if(dist[i] !=std::numeric_limits<long long>::max() &&dist[adj[i][j]] > dist[i] + cost[i][j]){
           dist[adj[i][j]] = dist[i] + cost[i][j];
           relaxed.push_back(adj[i][j]);
           parent[adj[i][j]] = i;
        }
    }
    return relaxed;
}

void dfs(int node, vector<int> &shortest, vector<vector<int> > &adj){
    if(!shortest[node]) return;
    shortest[node] = 0;
    for(int nxt: adj[node]) dfs(nxt,shortest,adj);
}


void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
    int n = adj.size();
    distance[s] = 0;
    vector<int> relaxed,parent(n);
    for(int i = 0; i < n; ++i) parent[i] = i;

    for(int j = 0; j < n ;++j){
        relaxed = relax(adj,cost,distance,parent);
    }
    for(int &node : relaxed){
        if(!shortest[node]) continue;
        for(int i = 0; i < n; ++i) node = parent[node];
        dfs(node,shortest,adj);
    }
    for(int i = 0; i < n; ++i) if(distance[i] != std::numeric_limits<long long>::max()) reachable[i] = 1;

}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
