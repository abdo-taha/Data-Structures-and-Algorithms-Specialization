#include <bits/stdc++.h>

using namespace std;

struct Vertex {
    int weight;
    vector <int> children;
};
typedef vector<Vertex> Graph;
typedef vector<int> Sum;


Graph ReadTree() {
    int vertices_count;
    cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

pair<int,int> dfs(const Graph &tree, int vertex, int parent) {
    pair<int,int> ret = {tree[vertex].weight,0};
    for (int child : tree[vertex].children)
        if (child != parent){
            pair<int,int> tmp = dfs(tree,child,vertex);
            ret.first += tmp.second;
            ret.second += tmp.first;
        }
    ret.first = max(ret.first,ret.second);
    return ret;
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    pair<int,int> p = dfs(tree, 0, -1);
    // You must decide what to return.
    return max(p.first,p.second);
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    // const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    // struct rlimit rl;
    // int result;
    // result = getrlimit(RLIMIT_STACK, &rl);
    // if (result == 0)
    // {
    //     if (rl.rlim_cur < kStackSize)
    //     {
    //         rl.rlim_cur = kStackSize;
    //         result = setrlimit(RLIMIT_STACK, &rl);
    //         if (result != 0)
    //         {
    //             fprintf(stderr, "setrlimit returned result = %d\n", result);
    //         }
    //     }
    // }

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    cout << weight << endl;
    return 0;
}
