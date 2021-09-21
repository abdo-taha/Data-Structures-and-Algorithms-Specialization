#include <bits/stdc++.h>
using namespace std;

// struct Edge {
//     int from;
//     int to;
// };

#define Edge pair<int,int>
#define from first
#define to second


struct ConvertHampathToSat {
    int numVertices;
    set<Edge> edges;
    vector<vector<int>> clauses;
    map<pair<int,int>,int> mp;

    ConvertHampathToSat(int n, int m) :
        numVertices(n)
    {  }

    
    vector<vector<int>> oneOf(vector<int> v){
        vector<vector<int>> ans;
        ans.push_back(v);
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = i+1; j < v.size(); j++)
            {
                ans.push_back({-v[i],-v[j]});
            }
            
        }
        return ans;
    }

    vector<vector<int>> same(int a, int b){
        vector<vector<int>> v(2);
        v[0].push_back(a);
        v[0].push_back(-b);
        v[1].push_back(-a);
        v[1].push_back(b);
        return v;
    }

    int id(int i, int pos){
        int &x = mp[{i,pos}];
        if(!x) x = mp.size();
        return x;
    }

    void printEquisatisfiableSatFormula() {

        for (int i = 0; i < numVertices; i++){
            vector<int> tmp;
            for (int j = 0; j < numVertices; j++) 
            {
                tmp.push_back(id(i,j));
            }
            for (vector<int> &v : oneOf(tmp))
            {
                clauses.push_back(v);
            }
            
        }
        
        
        for (int i = 0; i < numVertices; i++){
            vector<int> tmp;
            for (int j = 0; j < numVertices; j++) 
            {
                tmp.push_back(id(j,i));
            }
            for (vector<int> &v : oneOf(tmp))
            {
                clauses.push_back(v);
            }
            
        }

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = i+1; j < numVertices; j++)
            {
                if( (!edges.count({i+1,j+1})) && (!edges.count({j+1,i+1})) ) for (int k = 0; k < numVertices-1; k++)
                {
                    int a = id(i,k), b = id(j,k+1);
                    int c = id(i,k+1), d = id(j,k);
                    clauses.push_back({-a,-b});
                    clauses.push_back({-c,-d});
                    
                }
                
            }
            
        }
        

        cout << clauses.size() << " " <<  mp.size()+1<<"\n";
        for (vector<int> v: clauses)
        {
            for (int x : v) cout << x << " ";
            cout << "0\n"; 
        }
        
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        Edge e;
        cin >> e.from >> e.to;
        converter.edges.insert(e);
    }

    converter.printEquisatisfiableSatFormula();


    
    return 0;
}
