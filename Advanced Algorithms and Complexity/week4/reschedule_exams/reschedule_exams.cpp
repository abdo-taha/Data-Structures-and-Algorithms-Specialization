#include <bits/stdc++.h>
using namespace std;

struct Clause {
    int firstVar;
    int secondVar;
};


// one based
struct TwoSatisfiability {
    int numVars;
    vector<Clause> clauses;
    vector<vector<int>> graph;
    vector<vector<int>> graph2;
    vector<vector<int>> comps;

    TwoSatisfiability(int n, int m) :
        numVars(n),
        clauses(m),
        graph(2*n),
        graph2(n*2)
    {  }

    int id(int x, bool dash = 0){      
        if(x > 0){
            x--;
            x *= 2;
        }
        else{
            x *= -1;
            x--;
            x *= 2;
            ++x;
        }
        return x^dash;
    }

    void dfs(int x, vector<bool> &vst, stack<int> &st){
        vst[x] = 1;
        for (int nxt : graph[x] ) if(!vst[nxt])
        {
            dfs(nxt,vst,st);
        }
        st.push(x);
    }
    
    void dfs2(int x, vector<bool> &vst){
        vst[x] = 1;
        comps.back().push_back(x);
        for (int nxt : graph2[x]) if(!vst[nxt])
        {
            dfs2(nxt,vst);
        }
    }

    void dfs3(int x, int val, vector<int> &res){
        res[x] = val;
        res[x^1] = !val;
        for (int nxt : graph2[x]) if(res[nxt] == -1) dfs3(nxt,val,res);
    }

    bool isSatisfiable(vector<int>& result) {
        
        for (Clause &c : clauses)
        {
            // cout << c.firstVar << " " << c.secondVar << " 0\n";
            graph[id(c.firstVar,1)].push_back(id(c.secondVar)); 
            graph[id(c.secondVar,1)].push_back(id(c.firstVar));

            graph2[id(c.secondVar)].push_back(id(c.firstVar,1));
            graph2[id(c.firstVar)].push_back(id(c.secondVar,1));
        }
        stack<int> order;
        vector<bool> vst(2*numVars,0);
        for (int i = 0; i < 2*numVars; i++) if(!vst[i])
        {
            dfs(i,vst,order);
        }
        
        for (int i = 0; i < 2*numVars; i++) vst[i] = 0;

        while(!order.empty()){
            int cur = order.top();
            order.pop();
            if(vst[cur]) continue;
            comps.push_back(vector<int>());
            dfs2(cur,vst);
        }

        vector<int> ncomp(2*numVars,0);
        
        for (int i = 1; i < comps.size(); i++)
        {
            for (int x : comps[i])
            {
                ncomp[x] = i;
            }
            
        }

        for (int i = 0; i < 2*numVars; i+= 2)
        {
            if(ncomp[i] == ncomp[i+1]) return false;
        }

        vector<int> res(2*numVars,-1);

        for (vector<int> &comp : comps)
        {
            for (int x : comp)
            {
                if(res[x] == -1){
                    dfs3(x,1,res);

                }
            }
            
        }

        for (int i = 0; i < numVars; i++)
        {
            result[i] = res[i*2]; 
        }
        
                

        return true;
    }

};



/*
  Arguments:
    * `n` - the number of vertices.
    * `edges` - list of edges, each edge is a pair (u, v), 1 <= u, v <= n.
    * `colors` - string consisting of `n` characters, each belonging to the set {'R', 'G', 'B'}.
  Return value:
    * If there exists a proper recoloring, return value is a string containing new colors, similar to the `colors` argument.
    * Otherwise, return value is an empty string.
*/

int id(int x, int col){
    return x * 3 - col;
}

string assign_new_colors(int n, vector<pair<int, int>> edges, string colors) {
    // Insert your code here.
    TwoSatisfiability twosat(3*n,0);

    for (int i = 0; i < n; i++)
    {
        vector<int> ids;
        for (int j = 0; j < 3; j++) ids.push_back(id(i+1,j));
        twosat.clauses.push_back({-ids[0],-ids[1]});
        twosat.clauses.push_back({-ids[0],-ids[2]});
        twosat.clauses.push_back({-ids[2],-ids[1]});
        if(colors[i]=='R') twosat.clauses.push_back({ids[2],ids[1]});
        else if(colors[i]=='G') twosat.clauses.push_back({ids[0],ids[2]});
        else twosat.clauses.push_back({ids[0],ids[1]});
    }
    
    for (pair<int,int> p : edges)
    {
        for (int i = 0; i < 3; i++)
        {
            int a = id(p.first,i) , b = id(p.second,i);
            twosat.clauses.push_back({-a,-b});
        }
        
    }


    vector<int> result(3*n);
    string ans = "";
    if(twosat.isSatisfiable(result)){
        string rgb = "BGR";
        for (int i = 0; i < result.size(); i++) if(!result[i]) ans += rgb[i%3];
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    string colors;
    cin >> colors;
    vector<pair<int, int> > edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back(make_pair(u, v));
    }
    string new_colors = assign_new_colors(n, edges, colors);
    if (new_colors.empty()) {
        cout << "Impossible";
    } else {
        cout << new_colors << endl;
    }
}
