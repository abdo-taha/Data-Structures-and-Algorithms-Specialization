#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::vector;
using std::cin;
using std::cout;

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
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
    
    return matching_left;
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

};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
