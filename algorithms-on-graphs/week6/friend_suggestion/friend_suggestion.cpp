#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <iostream>
using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    // Number of nodes
    int n_;
    Len best;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<bool> visited_;

public:
    Bidijkstra(int n, Adj adj, Adj cost)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(n)
    { workset_.reserve(n); }

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INFINITY;
            visited_[v] = false;
        }
        best = INFINITY;
        workset_.clear();
    }

    // Processes visit of either forward or backward search
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
    void visit(Queue& q, int side, int v, Len dist) {
        if(visited_[v]) return;
        for(int i = 0; i < adj_[side][v].size(); ++i){
            int nxt = adj_[side][v][i];
            int cst = cost_[side][v][i];
            if(distance_[side][nxt] > dist + cst ){
                if(distance_[side][nxt] == INFINITY && distance_[!side][nxt] == INFINITY) workset_.push_back(nxt);
                q[side].push(make_pair(dist+cst,nxt));
                distance_[side][nxt] = dist + cst;
                best = min(best,dist + cst + distance_[!side][nxt]);
            }
        }
        visited_[v] = true;
    }

    // Returns the distance from s to t in the graph.
    Len query(int s, int t) {
        clear();
        Queue q(2);
        distance_[0][s] = distance_[1][t] = 0;
        visit(q, 0, s, 0);
        visit(q, 1, t, 0);
        workset_.push_back(s);
        workset_.push_back(t);
        // Implement the rest of the algorithm yourself
        while(q[0].size()||q[1].size()){
            if(q[0].size()){
                int v1 = q[0].top().second;
                Len cst1 = q[0].top().first;
                q[0].pop();
                if(visited_[v1]) break;
                visit(q,0,v1,cst1);
            }
            if(q[1].size()){
                int v2 = q[1].top().second;
                Len cst2 = q[1].top().first;
                q[1].pop();
                if(visited_[v2]) break;
                visit(q,1,v2,cst2);
            }
        }
        for(int v : workset_) best = min(best,distance_[0][v]+distance_[1][v]);
        if(best != INFINITY) return best;
        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    Bidijkstra bidij(n, adj, cost);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", bidij.query(u-1, v-1));
    }
}
