#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct equ
{
  int x[3],c[3];
  int y,pos;
  equ(){
    for (int i = 0; i < 3; i++) x[i] = c[i] = 0;
    y = 0;
    pos = 0;
  }
  void add(int _x, int _c){
    x[pos] = _x;
    c[pos++] = _c;
  }
};



struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;
    vector<vector<int>> clauses;
    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n)
    {}

    void relations(equ eq){
      if((!eq.pos)){
        if(eq.y < 0){
          clauses.push_back({1});
          clauses.push_back({-1});
        }
      }
      else{
        for (int j = 0; j < (1<<eq.pos); j++)
        {
          int y = 0;
          for (int i = 0; i < eq.pos; i++)
          {
            if(j&(1<<i)){
              y += eq.c[i];
            } 
          }
          
          if(y > eq.y){
            vector<int> v;
            for (int i = 0; i < eq.pos; i++){
              if(j&(1<<i)){
                v.push_back(-eq.x[i]);
              }else{
                v.push_back(eq.x[i]);
              }
            }
            clauses.push_back(v);
          }

        }
      }
    }

    void printEquisatisfiableSatFormula() {
        
      for (int i = 0; i < b.size(); i++)
      {
        equ eq;
        for (int j = 0; j < A[i].size(); j++)
        {
          if(A[i][j]){
            eq.add(j+1,A[i][j]);
          }
        }
        eq.y = b[i];
        relations(eq);

      }
      
      if(!clauses.size()) clauses.push_back({1});
      cout << clauses.size() << " " << A[0].size() <<"\n";
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
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> converter.A[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
