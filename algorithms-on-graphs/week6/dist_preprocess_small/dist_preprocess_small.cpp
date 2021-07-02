#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>
#include <map>
#include <set>

class Graph
{
    typedef int Distance;
    typedef int Vertex;
    typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int, int>>> pr_q;

    // Number of nodes
    int N;
    // Source and target
    int s, t;
    // Estimate of the distance from s to t
    int estimate = INFINITY;
    // Lists of edges outgoing from each node
    std::vector<std::vector<std::pair<int, int>>> outgoing_edges;
    // Lists of edges incoming to each node
    std::vector<std::vector<std::pair<int, int>>> incoming_edges;

    int INFINITY = std::numeric_limits<int>::max() / 4;
    // Levels of nodes for node ordering
//    std::vector<int> level;
    // Ranks of nodes - positions in the node ordering
    std::vector<int> rank,neighbours,level;

    // Distance to node v, bidistance[0][v] - from source in the forward search, bidistance[1][v] - from target
    // in the backward search.
    std::vector<std::vector<Distance>> bidistance;

public:
    Graph() {
        read_stdin();
        bidistance.resize(2, std::vector<int>(N, INFINITY));

    }

    int get_n() { return N;}

    std::vector<std::pair<int, int>>& get_adjacent(int v, bool forward = true) {
        if (forward) {
            return outgoing_edges[v];
        } else {
            return incoming_edges[v];
        }
    }

    void preprocess() {
         pr_q queue;
        for(int i = 0; i < N; ++i){
            if(outgoing_edges[i].size() || incoming_edges[i].size()){
                queue.push(std::make_pair(get_importance(i),i));
            }
        }

        while(queue.size()){
            std::pair<int,int> to_contract = next_v(queue); /// ( importance , v  )
            update_rank(to_contract.second);
            std::vector<Shortcut> SC = shortcuts(to_contract.second);
            do_shortcut(to_contract.second,SC);
            update_neighbour(to_contract.second);
            update_level(to_contract.second);
        }

    }

    void print_graph(){
        for(int i = 0; i < N ; ++i){
            std::cout << i+1 << " " <<  rank[i] << " : \n";
            for(std::pair<int,int> p : outgoing_edges[i]) std::cout << i+1 << " -> " << p.first +1  << " "  << p.second << "\n";

        }
    }


    int query(int u, int w) {

        estimate = INFINITY;
        pr_q pq[2];

        pq[1].push({0,u});
        pq[0].push({0,w});

        bidistance[1][u] = 0;
        bidistance[0][w] = 0;

        query_vst[0].insert(w);
        query_vst[1].insert(u);

        while(pq[0].empty()==false || pq[1].empty()==false){
            if(!pq[1].empty()){
                std::pair<int,int> v = pq[1].top();
                pq[1].pop();
//                if(bidistance[1][v.second]!= v.first) continue;
                if(v.first <= estimate){
                    for(std::pair<int,int> &p : outgoing_edges[v.second]) if(rank[v.second] < rank[p.first]){
                        if( bidistance[1][p.first] > v.first + p.second){
                            bidistance[1][p.first] = v.first + p.second;
                            pq[1].push({v.first + p.second,p.first});
                            query_vst[1].insert(p.first);
                        }
                    }
                }
                estimate = std::min(estimate,bidistance[0][v.second]+bidistance[1][v.second]);
            }
            if(!pq[0].empty()){
                std::pair<int,int> v = pq[0].top();
                pq[0].pop();
                if(v.first <= estimate){
                    for(std::pair<int,int> &p : incoming_edges[v.second])if(rank[v.second] < rank[p.first]){
                        if( bidistance[0][p.first] > v.first + p.second){
                            bidistance[0][p.first] = v.first + p.second;
                            pq[0].push({v.first + p.second,p.first});
                            query_vst[0].insert(p.first);
                        }
                    }
                }
                estimate = std::min(estimate,bidistance[0][v.second]+bidistance[1][v.second]);
            }
        }

        clear_query();

        if(estimate < INFINITY) return estimate;

        return -1;
    }

private:
    /// -------------------------- preprocessing -------------------------------///
    struct Shortcut {
        int from;
        int to;
        int cost;
        Shortcut(int from, int to, int cost):from(from),to(to),cost(cost){}
    };

    int get_importance (int v){
        return ( outgoing_edges[v].size() * incoming_edges[v].size() - outgoing_edges[v].size() - incoming_edges[v].size())
        + (outgoing_edges[v].size() + incoming_edges[v].size())
        +  neighbours[v]
        + level[v];
    }

    std::pair<int,int> next_v(pr_q &queue){
        std::pair<int,int> to_contract = queue.top();
        while(true){
            queue.pop();
            to_contract.first = get_importance(to_contract.second);

            if(queue.empty() ||to_contract.first <= queue.top().first){
                break;
            }
            queue.push(to_contract);
            to_contract = queue.top();
        }
        return to_contract;
    }

    int rnk = 1;
    void update_rank(int v){
        rank[v] = rnk++;
    }

    void update_level(int v){
        for(std::pair<int,int> &before : incoming_edges[v]) level[before.first] = std::max(level[before.first],level[v]+1);
        for(std::pair<int,int> &nxt : outgoing_edges[v]) level[nxt.first] = std::max(level[nxt.first],level[v]+1);
    }

    void update_neighbour(int v){
        for(std::pair<int,int> &before : incoming_edges[v]) ++neighbours[before.first];
        for(std::pair<int,int> &nxt : outgoing_edges[v]) ++neighbours[nxt.first];
    }

    std::vector<Shortcut> shortcuts(int v){
        std::vector<Shortcut> shorts;
        int mxb = 0 , mxn = 0;
        for(std::pair<int,int> &before : incoming_edges[v]) if(rank[before.first] == INFINITY) mxb = std::max(mxb,before.second);
        for(std::pair<int,int> &nxt : outgoing_edges[v]) if(rank[nxt.first] == INFINITY) mxn = std::max(mxn,nxt.second);
        int mx = mxb + mxn;

        for(std::pair<int,int> &before : incoming_edges[v]){
            if(rank[before.first]  != INFINITY) continue;
            dijkstra(before.first,v,mx,5000);
            for(std::pair<int,int> &nxt : outgoing_edges[v])if(before.first!=nxt.first){
                if(rank[nxt.first] != INFINITY) continue;

                if(dist[nxt.first] > before.second+nxt.second){
                    shorts.push_back( Shortcut(before.first,nxt.first,before.second+nxt.second));
                }
            }
            clear_done();
        }
        return shorts;
    }

    std::vector<int> dist;
    std::set<int> done;

    void dijkstra(int from , int v, int mx, int hops){
        using T =  std::pair<std::pair<int,int>,int>; /// ( (dist ,hops) , v)
        std::priority_queue<T,std::vector<T>,std::greater<T>> pq;
        dist[from] = 0 ;
        done.insert(from);
        pq.push(std::make_pair(std::make_pair(0,0),from));
        while(pq.size()){
            int cur = pq.top().second, cost = pq.top().first.first,hps =pq.top().first.second ;
            pq.pop();
            if(cost != dist[cur]) continue;
            if(cost >= mx ) return ; /// ||hps> hops
            for(std::pair<int,int> &nxt : outgoing_edges[cur]){
                if( rank[nxt.first] == INFINITY && nxt.first != v &&  dist[nxt.first] > cost + nxt.second ){
                    dist[nxt.first] = cost+nxt.second;
                    pq.push( std::make_pair(std::make_pair(cost+nxt.second,hps+1),nxt.first) );
                    done.insert(nxt.first);
                }
            }
        }
    }

    void clear_done(){
        for(int x : done) dist[x] = INFINITY;
        done.clear();
    }

    void do_shortcut(int v, std::vector<Shortcut>& shortcuts) {
        for(Shortcut &sc : shortcuts){
            add_edge(sc.from,sc.to,sc.cost);
        }

    }

    ///  ---------------------------------- queries ------------------------------------------------------///

    std::set<int> query_vst[2];
    void clear_query(){
        for(int i =0; i < 2; ++i)
            for(int node : query_vst[i])
                bidistance[i][node] = INFINITY;
        query_vst[0].clear();
        query_vst[1].clear();
    }

    /// -------------------------------------  input --------------------------------------------///
    void set_n(int n) {
        N = n;
        outgoing_edges.resize(n);
        incoming_edges.resize(n);
        rank.assign(n,INFINITY);
        level.assign(n,0);
        neighbours.assign(n,0);
        dist.assign(n,INFINITY);
    }

    void add_edge_to_list(std::vector<std::pair<int,int>>& list, int w, int c) {
        for (int i = 0; i < list.size(); ++i) {
            std::pair<int, int>& p = list[i];
            if (p.first == w) {
                if (p.second > c) {
                    p.second = c;
                }
                return;
            }
        }
        list.push_back(std::make_pair(w, c));
    }

    void add_directed_edge(int u, int v, int c) {
        add_edge_to_list(outgoing_edges[u], v, c);
        add_edge_to_list(incoming_edges[v], u, c);
    }

    void add_edge(int u, int v, int c) {
        add_directed_edge(u, v, c);
    }

    bool read_stdin() {
        int u,v,c,n,m;
        assert(scanf("%d %d", &n, &m) == 2);
        set_n(n);
        for (int i = 0; i < m; ++i) {
            assert(scanf("%d %d %d", &u, &v, &c) == 3);
            add_edge(u-1, v-1, c);
        }
        return true;
    }
};

int main() {



    Graph g;
    g.preprocess();
    std::cout << "Ready" << std::endl;
//    g.print_graph();
    int t;
    assert(scanf("%d", &t) == 1);
    for (int i = 0; i < t; ++i) {
        int u, v;
        assert(scanf("%d %d", &u, &v) == 2);
        printf("%d\n", g.query(u-1, v-1));
    }
}
