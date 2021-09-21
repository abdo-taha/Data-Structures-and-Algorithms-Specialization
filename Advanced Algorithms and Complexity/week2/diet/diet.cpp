#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <bitset>
using namespace std;

typedef vector<vector<double>> matrix;
typedef std::vector<double> Column;
typedef std::vector<double> Row;


int popcount(int x){
  int set_bits = 0;
  while(x)
  {
    if (x & 1)
        ++set_bits;
    x >>= 1;
  }
  return set_bits;
}

struct Equation {
    Equation(const matrix
   &a, const Column &b):
        a(a),
        b(b)
    {}

    matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Position SelectPivotElement(
  const matrix &a, 
  std::vector <bool> &used_rows, 
  std::vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row] && pivot_element.row+1 < used_rows.size())
        ++pivot_element.row;
    while ((used_columns[pivot_element.column]||!a[pivot_element.row][pivot_element.column] ) && pivot_element.column+1 < used_columns.size())
        ++pivot_element.column;
    return pivot_element;
}

void SwapLines(matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here
    double x = a[pivot_element.row][pivot_element.column];
    for(double &elm : a[pivot_element.row]) elm /= x;
    b[pivot_element.row] /= x;
    for (int r = 0; r < a.size(); r++) 
    if(r != pivot_element.row && a[r][pivot_element.column])
    {
        double tmp = a[r][pivot_element.column] ;
        for (int c = 0; c < a[0].size(); c++)
        {
            a[r][c] -= tmp * a[pivot_element.row][c];
        }
        b[r] -= tmp * b[pivot_element.row];
    }
    
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Equation &equation) {
    matrix &a = equation.a;
    Column &b = equation.b;

    std::vector <bool> used_columns(a[0].size(), false);
    std::vector <bool> used_rows(a.size(), false);
    for (int step = 0; step < a.size(); ++step) {
        Position pivot_element = SelectPivotElement(a, used_rows, used_columns);  
        if(!a[pivot_element.row][pivot_element.column]) break;
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }

    return b;
}

bool check(matrix &A, vector<double> &b, vector<double> &ans){
  for (int i = 0; i < A.size(); i++)
  {
    double tmp = 0;
    for (int j = 0; j < ans.size(); j++)
    {
      tmp += ans[j] * A[i][j];
    }
    if(tmp > b[i] + 1e-3 ) return false;
    
  }
  return true;
  
}

void print_matrix(matrix x){
  
  std::cout <<"-----------------------------\n";
  for (int i = 0; i < x.size(); i++)
  {
    for (int j = 0; j < x[i].size(); j++)
    {
      std::cout<<x[i][j] << " ";
    }
    std::cout << "\n";
    
  }
  std::cout <<"-----------------------------\n";
  
}

pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  double best = -1e12;
  vector<double> ret(m,0);
  bool inf = false;

  for (int i = 0; i < m; i++)
  {
    vector<double> tmp = vector<double>(m,0);
    tmp[i] = -1; 
    A.push_back(tmp);
    b.push_back(0);
  }
  A.push_back(vector<double>(m,1));
  b.push_back(1000000000);
  int pwr = A.size();
  
  for (int i = 0; i < (1<<pwr); i++)
  {
    if(popcount(i) == m ){
      matrix a1;
      Column b1;
      for (int j = 0; j < pwr; j++) if(i & (1<< j) )
      {
        a1.push_back(A[j]);
        b1.push_back(b[j]);
      }
      Equation eq(a1,b1);
      Column ans = SolveEquation(eq);

      // print_matrix(eq.a);

      if(check(A,b,ans)){
        double cmp = 0;
        for (int j = 0; j < c.size(); j++)
        {
          cmp += c[j] * ans[j];
        }
        if(cmp > best){
          best = cmp;
          ret = ans;
          if(i & (1<<(pwr-1)) ) inf = true;
        }
        
      }
    
    }
  }
  
  if(abs(best+1e12) < 1e-9) return {-1,ret};
  if(inf) return {1,ret};
  return {0,ret};

}

int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
