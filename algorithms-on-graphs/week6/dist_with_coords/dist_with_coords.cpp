
#include<bits/stdc++.h>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif


using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef long long Len;
typedef vector<vector<vector<Len>>> Adj;
typedef vector<priority_queue<pair<Len, Len>,vector<pair<Len,Len>>,greater<pair<Len,Len>>>> Queue;

const Len OO = numeric_limits<Len>::max() / 4;

class AStar {
    // See the descriptions of these fields in the starter for friend_suggestion
    Len n_,from,to;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    vector<Len> workset_;
    vector<vector<bool>> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;

    Len best;

    Len pi_f(Len v){
        return  sqrt(  pow(xy_[v].first-xy_[to].first, 2)+ pow(xy_[v].second-xy_[to].second,2));
    }
    Len pi_r(Len v){
        return  sqrt(pow(xy_[v].first-xy_[from].first,2)+pow(xy_[v].second-xy_[from].second,2));
    }
    Len ptn_f(Len v){
        return (pi_f(v)-pi_r(v)) / 2;
    }
    Len ptn_r(Len v){
        return  -1 * ptn_f(v);
    }
    Len potential(Len v, Len side){
        return side ? ptn_r(v) : ptn_f(v);
    }
    Len real_dist(Len v, Len side){
        return distance_[side][v] - potential(v,side);
    }


public:
    AStar(Len n, Adj &adj, Adj &cost, std::vector<std::pair<Len,Len>> &xy)
        : n_(n), distance_(2, vector<Len>(n_, OO)), visited_(2,vector<bool>(n,false))
    {
        workset_.reserve(n);
        cost_ = cost;
        adj_ = adj;
        xy_ = xy;
    }

    // See the description of this method in the starter for friend_suggestion
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = OO;
            visited_[0][v]= visited_[1][v] = false;
        }
        workset_.clear();
        best = OO;

    }

    // See the description of this method in the starter for friend_suggestion
    void visit(Queue& q, Len side, Len v, Len dist ) {
        // Implement this method yourself
        if(distance_[side][v] != dist) return;
        if(visited_[side][v]) return;
        for(int i = 0; i < adj_[side][v].size(); ++i){
            Len nxt = adj_[side][v][i];
            Len cst = cost_[side][v][i] - potential(v,side) + potential(nxt,side);
            Len edge = cost_[side][v][i];
            if(distance_[side][nxt] > dist + cst ){
                if(distance_[side][nxt] == OO && distance_[!side][nxt] == OO) workset_.push_back(nxt);
                q[side].push(make_pair(dist+cst,nxt));
                distance_[side][nxt] = dist + cst;
                best = min(best, real_dist(v,side) + edge + real_dist(nxt,!side));
            }
        }
        visited_[side][v] = true;
    }

    // Returns the distance from s to t in the graph
    Len query(Len s, Len t) {
        clear();
        from = s;
        to =t;
        Queue q(2);
        distance_[0][s] = potential(s,0);
        distance_[1][t] = potential(t,1);
        visit(q, 0, s,potential(s,0));
        visit(q, 1, t, potential(t,1));
        workset_.push_back(s);
        workset_.push_back(t);
        // Implement the rest of the algorithm yourself
        while(q[0].size()||q[1].size()){
            if(q[0].size()){
                Len v1 = q[0].top().second;
                Len cst1 = q[0].top().first;
                q[0].pop();
                if(visited_[1][v1]) break;
                visit(q,0,v1,cst1);
            }
            if(q[1].size()){
                Len v2 = q[1].top().second;
                Len cst2 = q[1].top().first;
                q[1].pop();
                if(visited_[0][v2]) break;
                visit(q,1,v2,cst2);
            }
        }
        for(Len v : workset_) best = min(best,real_dist(v,0) + real_dist(v,1));
        if(best != OO) return best;
        return -1;
    }
};



int main(int argc, char **argv) {
//    freopen( "output.txt" , "w" , stdout ) ;
//    freopen( "03" , "r" , stdin ) ;

    #if defined(__unix__) || defined(__APPLE__)
      // Allow larger stack space
      const rlim_t kStackSize = 2 * 1024 * 1024 * 1024;   // min stack size = 16 MB
      struct rlimit rl;
      int result;

      result = getrlimit(RLIMIT_STACK, &rl);
      if (result == 0)
      {
          if (rl.rlim_cur < kStackSize)
          {
              rl.rlim_cur = kStackSize;
              result = setrlimit(RLIMIT_STACK, &rl);
              if (result != 0)
              {
                  std::cerr << "setrlimit returned result = " << result << std::endl;
              }
          }
      }

    #endif

    ios::sync_with_stdio(0);
    Len n, m;
//    scanf("%d%d", &n, &m);
    cin >> n >> m;
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        Len a, b;
//        scanf("%d%d", &a, &b);
        cin >> a >> b;
        xy[i] = make_pair(a,b);
    }
    Adj adj(2, vector<vector<Len>>(n));
    Adj cost(2, vector<vector<Len>>(n));
    for (int i=0; i<m; ++i) {
        Len u, v, c;
        cin >> u >> v >> c;
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    cin >> t;
    for (int i=0; i<t; ++i) {
        Len u, v;
        cin >> u >> v;
        cout << astar.query(u-1, v-1) << "\n";
    }
}

