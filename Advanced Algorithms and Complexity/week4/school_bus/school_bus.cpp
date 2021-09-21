#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int> > Matrix;

const int INF = 1e9;

Matrix read_data() {
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

void comb(int x,int pos, int rem, vector<int>&ans){
    if(pos == 0){
        if(!rem) ans.push_back(x);
        return;
    }
    if(rem > 0) {
        comb(x,pos-1,rem,ans);
        if( ( x&(1<<pos) ) == 0 ) comb(x|(1<<pos),pos-1,rem-1,ans);
    }else ans.push_back(x);
}

pair<int, vector<int> > optimal_path(const Matrix& graph) {
    // This solution tries all the possible sequences of stops.
    // It is too slow to pass the problem.
    // Implement a more efficient algorithm here.
    size_t n = graph.size();
    int best_ans = INF;
    vector<int> best_path;
    vector<vector<int>> mem( (1<<n)+5,vector<int>(20,INF) );
    
    mem[1][0] = 0;
    vector<int> v;
    for (int i = 1; i < n; i++)
    {
        v.clear();
        comb(1,n-1,i,v);

        for (int x : v)
        {
            for (int i = 1; i < n; i++) if(x & (1<<i))
            {
                for (int j = 0; j < n; j++) if( ( x & (1<<j) ) && i != j)
                {
                    
                    mem[x][i] = min(mem[x][i],mem[x^(1<<i)][j]+graph[i][j]);
                }
                
            }
            
        }
        
        
    }
    
    int all = (1<<n)-1,last = 1;
    for (int i = 1; i < n; i++)
    {
        if(mem[all][i] + graph[0][i] < best_ans){
            best_ans = mem[all][i] + graph[0][i];
            last = i;
        }
    }

    if(best_ans != INF){
        best_ans -= graph[0][last];
        while (last != 0)
        {
            best_path.push_back(last);
            for (int i = 0; i < n; i++) if( (all&(1<<i)) && last != i )
            {
                if(mem[all][last] == mem[all^(1<<last)][i] + graph[last][i]){
                    all ^= (1<<last);
                    last = i;
                    break;
                }
            }
            
        }
        best_path.push_back(0);
        best_ans += graph[0][best_path[0]];
        reverse(best_path.begin(),best_path.end());
    }


    if (best_ans == INF)
        best_ans = -1;
    for (size_t i = 0; i < best_path.size(); ++i)
        ++best_path[i];
    return make_pair(best_ans, best_path);
}

void print_answer(const pair<int, vector<int> >& answer) {
    cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        cout << path[i] << " ";
    cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}
