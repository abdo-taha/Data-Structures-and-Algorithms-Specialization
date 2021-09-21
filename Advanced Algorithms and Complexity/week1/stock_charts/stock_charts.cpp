#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::vector;
using std::cin;
using std::cout;

class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    vector<vector<bool>> cross = build_adj(stock_data);
    vector<vector<bool>> adj_matrix = connect(cross);
    int ans = count_connected(adj_matrix);
    WriteResponse(ans);
  }

 private:
  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  vector<vector<bool>> build_adj(const vector<vector<int>>& stock_data) {

    int num_stocks = stock_data.size();
    vector<vector<bool>> adj_matrix(num_stocks,vector<bool>(num_stocks,false));
    for (int i = 0; i < num_stocks; ++i) {
      for (int j = 0; j < num_stocks; j++)
      {
        if (compare(stock_data[i], stock_data[j])) adj_matrix[i][j]  = true;
      }
    }

    return adj_matrix;    
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] >= stock2[i])
        return false;
    return true;
  }

  vector<vector<bool>> connect(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();
    vector<int> matching_left(num_left, -1),matching_right(num_right,-1);
    vector<bool> vis;
    for (int i = 0; i < num_left; i++)
    {
      vis.assign(num_right,false);
      match(i,adj_matrix,vis,matching_right,matching_left);
      vis.clear();
    }
    vector<vector<bool>> ans(num_left,vector<bool>(num_right,false));
    for (int i = 0; i < num_left; i++) if(matching_left[i] != -1)
    {
      ans[i][matching_left[i]] = ans[matching_left[i]][i] =  true;
    }
    
    for (int i = 0; i < num_right; i++) if(matching_right[i] != -1)
    {
      ans[i][matching_right[i]] = ans[matching_right[i]][i] =  true;
    }
    return ans;
  }

  bool match(int left,const vector<vector<bool>>& adj_matrix, vector<bool> &vis, vector<int> &matching_right,vector<int> &matching_left){
    for (int j = 0; j < adj_matrix[0].size(); j++) if(adj_matrix[left][j] && !vis[j] )
    {
      vis[j] = true;
      if(matching_right[j] == -1 || match(matching_right[j],adj_matrix,vis,matching_right,matching_left)){
        matching_left[left] = j;
        matching_right[j] = left;
        return true;
      }
    }
    return false;
}

  int count_connected(vector<vector<bool>> &adj){
    int n = adj.size(),ans = 0;
    vector<bool> vstd(n,false);
    for (int i = 0; i < n; i++) if(!vstd[i])
    {
      ++ans;
      dfs(i,adj,vstd);
    }
    return ans;
    
  }

  void dfs(int pos, vector<vector<bool>> &adj,vector<bool> &vstd){
    vstd[pos] = true;
    for (int i = 0; i < adj.size(); i++) if(adj[pos][i] && !vstd[i]) dfs(i,adj,vstd);
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
