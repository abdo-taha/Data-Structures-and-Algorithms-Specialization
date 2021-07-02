#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
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

class DisjSet {
    int *rank, *parent, n;

public:
    DisjSet(int n)
    {
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        makeSet();
    }
    void makeSet()
    {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void Union(int x, int y)
    {
        int xset = find(x);
        int yset = find(y);
        if (xset == yset)
            return;

        if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        }
        else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        }

        else {
            parent[yset] = xset;
            rank[xset] = rank[xset] + 1;
        }
    }
};

double clustering(vector<int> x, vector<int> y, int k) {
    int n = x.size();
    priority_queue<pair<double,pair<int,int>>,vector<pair<double,pair<int,int>>>,greater<pair<double,pair<int,int>>>> pq;
    DisjSet ds(n);
    for(int i = 0; i < n; ++i)
    for(int j = i+1; j < n; ++j){
        double d = sqrt( pow(x[i]-x[j],2) + pow(y[i]-y[j],2) );
        pq.push({d,{i,j}});
    }
    vector<double> ans;
    while(pq.size()){
        double d = pq.top().first;
        int i = pq.top().second.first, j = pq.top().second.second;
        if(ds.find(i)!=ds.find(j)){
            ds.Union(i,j);
            ans.push_back(d);
        }
        pq.pop();
    }
    sort(ans.begin(),ans.end(),greater<double>());
    return ans[k-2];
}

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
