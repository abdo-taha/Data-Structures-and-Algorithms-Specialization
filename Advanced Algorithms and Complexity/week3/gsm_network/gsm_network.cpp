#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;
    vector<vector<int>> clauses;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    int getId(int pos, int color){
       return (pos-1) * 3 + color;
    }

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

    void printEquisatisfiableSatFormula() {
        
        for (int i = 0; i < numVertices; i++)
        {
            vector<int> tmp;
            for (int j = 1; j < 4; j++)
            {
                tmp.push_back(getId(i+1,j));
            }
            
            for (vector<int> v : oneOf(tmp))
            {
                clauses.push_back(v);
            }
            
        }
        
        for (Edge e : edges)
        {
            for (int j = 1; j < 4; j++)
            {
                clauses.push_back({-getId(e.from,j),-getId(e.to,j)});
            }
            
            
        }

        std::cout << clauses.size() << " " <<  3 * numVertices<<"\n";
        for (vector<int> v: clauses)
        {
            for (int x : v) std::cout << x << " ";
            std::cout << "0\n"; 
        }
          
        
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
