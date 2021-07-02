#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

bool relax(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<int> &dist){
    bool relaxed = 0;
    for(int i = 0 ; i < adj.size(); ++i) for(int j = 0 ;j < adj[i].size();++j){
        if(dist[adj[i][j]] > dist[i] + cost[i][j]){
           dist[adj[i][j]] = dist[i] + cost[i][j];
           relaxed = 1;
        }
    }
    return relaxed;
}


int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    int n = adj.size();
    vector<int> dist(n,100000000);
    for(int i = 0 ; i < n ; ++i) if(dist[i]==100000000){
        dist[i] = 0;
        bool relaxed = 0;
        for(int j = 0; j < n ;++j){
            relaxed = relax(adj,cost,dist);
        }
        if(relaxed) return 1;
    }
  return 0;
}

int main() {
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
  std::cout << negative_cycle(adj, cost);
}
