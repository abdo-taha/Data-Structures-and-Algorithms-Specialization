#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::max;
using std::min;
using std::make_pair;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

vector<pair<int,int>> mem;
vector<bool> vst;

pair<int,int> max_min(int index,const vector<Node>& tree){
    if(vst[index]) return mem[index];
    int mx = tree[index].key, mn = mx;
    if(tree[index].left != -1){
        pair<int,int> l = max_min(tree[index].left,tree);
        mx = max(mx,l.first);
        mn = min(mn,l.second);
    }
    if(tree[index].right != -1){
        pair<int,int> r = max_min(tree[index].right,tree);
        mn = min(mn,r.second);
        mx = max(mx,r.first);
    }
    vst[index] = 1;

    return mem[index] = make_pair(mx,mn);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    for(int i = 0; i < tree.size(); ++i){
        pair<int,int> p;
        if(tree[i].left!=-1){
            p = max_min(tree[i].left,tree);
            if(p.first >= tree[i].key) return false;
        }
        if(tree[i].right!=-1){
            p=max_min(tree[i].right,tree);
            if(p.second <= tree[i].key) return false;
        }

    }
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  mem.resize(nodes);
  vst.resize(nodes,0);
  if (IsBinarySearchTree(tree) ) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
