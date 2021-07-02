#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <map>
#include <queue>


using std::vector;
using std::pair;
using std::map;
using std::make_pair;
using std::priority_queue;
using std::greater;

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  int n = x.size();
  vector<vector<pair<int,double>>> adj(n);
  map<int,bool> done;
  for(int i = 0; i < n; ++i)
  for(int j = i+1; j < n; ++j){
    double d = sqrt( pow(x[i]-x[j],2) + pow(y[i]-y[j],2) );
    adj[i].push_back(make_pair(j,d));
    adj[j].push_back(make_pair(i,d));
  }
  priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> pq;
  pq.push(make_pair(0,0));
  for(int i = 0; i < n ; ++i){
    result += pq.top().first;
    done[pq.top().second] = 1;
    for(auto &nxt : adj[pq.top().second]) if(!done[nxt.first]){
        pq.push(make_pair(nxt.second,nxt.first));
    }
    while(pq.size() && done[pq.top().second]) pq.pop();
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
