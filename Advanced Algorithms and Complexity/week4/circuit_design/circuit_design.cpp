#include <bits/stdc++.h>
using namespace std;

struct Clause {
    int firstVar;
    int secondVar;
};

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


int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
    }

    vector<int> result(n);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
