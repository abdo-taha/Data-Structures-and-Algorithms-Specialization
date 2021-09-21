/* not working  */
/* not working  */
/* not working  */
/* not working  */
/* not working  */
/* not working  */
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

typedef vector<vector<double>> matrix;
typedef std::vector<double> Column;

const double eps = 1e-6, err = 1e-10;


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

void print_column(Column x){
  
  std::cout <<"-----------------------------\n";
  for(double xx:x) cout << xx << " ";
  cout << "\n";
  
  std::cout <<"-----------------------------\n";
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

void print_eq(Equation eq){

  print_matrix(eq.a);
  print_column(eq.b);


}


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
    for (int r = 0; r < a.size(); r++) if( (r != pivot_element.row ))
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


void swap_column(Equation &eq, int pos1 , int pos2){
  for (int i = 0; i < eq.a.size(); i++)
  {
    swap(eq.a[i][pos1],eq.a[i][pos2]);
  }
  
}
void swap_column(matrix &a, int pos1 , int pos2){
  for (int i = 0; i < a.size(); i++)
  {
    swap(a[i][pos1],a[i][pos2]);
  }
  
}


pair<Column,Column> get_line(Equation equation){
  
  pair<Column,Column> ret;
  matrix &a = equation.a;
  Column &b = equation.b;

  std::vector <bool> used_columns(a[0].size()-1, false);
  std::vector <bool> used_rows(a.size(), false);
  for (int step = 0; step < a.size(); ++step) {
      Position pivot_element = SelectPivotElement(a, used_rows, used_columns);  
      if(pivot_element.row >= a.size() || pivot_element.column >= a[0].size()) break;
      if(!a[pivot_element.row][pivot_element.column]) break;
      SwapLines(a, b, used_rows, pivot_element);
      ProcessPivotElement(a, b, pivot_element);
      MarkPivotElementUsed(pivot_element, used_rows, used_columns);
  }
  ret.second = b;
  if(a.size() && a[0].size()) for (int i = 0; i < a.size(); i++)
  {
    ret.first.push_back(a[i][a[0].size()-1]);
  }
  return ret;
  
}

pair<int,double> get_limit(pair<Column,Column> p, Column c, double b){
  // a * x1 <  bb

  double a = c[c.size()-1];

  for (int i = 0; i < c.size()-1; i++)
  {
    a += c[i] * -p.first[i];
    b -= c[i] * p.second[i]; 
  }

  if(a < 0) return {-1,b/a};
  return {1,b/a};
}

double get_value(Column a, Column b){
  double ret = 0;
  for (int i = 0; i < a.size(); i++)
  {
    ret += a[i] * b[i];
  }
  return ret;
}


int  col0(Equation eq){
  int ans = 0;
  for (int i = 0; i < eq.a[0].size(); i++)
  {
    bool nonzero = false;
    for (int j = 0; j < eq.a.size(); j++)
    {
      if(abs(0-eq.a[j][i]) > err) nonzero = true; 
    }
    if(nonzero == false) return i;
    ++ans;
  }
  return ans-1;

}


Column nxt_point(Equation eq , matrix eqns, Column b, Column mx){

  double best = -1e18;
  Column ret;
  for (int i = 0; i < eqns.size(); i++)
  {
    double l = -1e10 , r = 1e10;
    matrix a_t; Column b_t;
    
    for (int  j = 0; j < eqns.size(); j++) if(i != j)
    {
      a_t.push_back(eqns[j]);
      b_t.push_back(b[j]);
    }
    
    Equation eq_t(a_t,b_t);



    int pos0 = col0(eq_t),pos1 = eq_t.a[0].size()-1;
    swap_column(eq_t,pos0,pos1);
    swap_column(eq,pos0,pos1);
    swap(mx[pos1],mx[pos0]);
    swap_column(eqns,pos1,pos0);

    pair<Column,Column> p = get_line(eq_t);

    for (int j = 0; j < eq.a.size(); j++)
    {
      pair<int,double> lim = get_limit(p,eq.a[j],eq.b[j]);  
      if(lim.first == 1){
        r = min(r,lim.second);
      }else{
        l = max(l,lim.second);
      }
    }

    if(l < r){
        Column tmp;
        for (int j = 0; j < p.first.size(); j++)
        {
            tmp.push_back(-p.first[j]*l+p.second[j]);
        }
        tmp.push_back(l);
        double tval = get_value(tmp,mx);
        if(tval > best){
          best = tval;
          ret = tmp;
          swap(ret[pos0],ret[pos1]);
        }

        tmp.clear();
        for (int j = 0; j < p.first.size(); j++)
        {
            tmp.push_back(-p.first[j]*r+p.second[j]);
        }
        tmp.push_back(r);
        tval = get_value(tmp,mx);
        if(tval > best){
          best = tval;
          ret = tmp;
          swap(ret[pos0],ret[pos1]);
        }
    }

    swap_column(eq_t,pos0,pos1);
    swap_column(eq,pos0,pos1);
    swap(mx[pos1],mx[pos0]);
    swap_column(eqns,pos1,pos0);
  }


  return ret;

  
}

bool belong(Column a, double b, Column point){
  double ans = get_value(a,point);
  if(abs(ans-b) < err) return true;
  return false;
}



pair<int, vector<double>> allocate_ads(
    int n, // number of eqns
    int m,  // number of variables
    matrix A, 
    vector<double> b, 
    vector<double> c) {
    
    for (int i = 0; i < m; i++)
    {
      Column tmp(m,0);
      tmp[i] = -1;
      A.push_back(tmp);
      b.push_back(0);
    }
    
    A.push_back( Column(m,1) );
    b.push_back(1e9);
    for(double &x : b) x += eps;

    n = A.size();
    Equation eq(A,b);

    matrix tmpa; Column tmpb;
    for (int i = 0; i < m; i++)
    {
      tmpa.push_back(A[i]);
      tmpb.push_back(b[i]);
    }
    Equation eq0(tmpa,tmpb);
    Column point = SolveEquation(eq0);
    bool better = true;
    double best = get_value(point,c);

    while (better)
    {
      better = false;
      matrix eqns;
      Column b_;
      for (int i = 0; i < n; i++)
      {
        if(eqns.size()==m) break;
        if(belong(A[i],b[i],point)){
          eqns.push_back(A[i]);
          b_.push_back(b[i]);
        }
      }
      if(eqns.size() == m){
        Column  point1 = nxt_point(eq,eqns,b_,c);
        double val = get_value(point1,c);
        if(val > best){
          best = val;
          point = point1;
          better = true;
        }
      }
      
    }
  
  if(belong(A[A.size()-1],b[b.size()-1],point)) return {1,point};
  if(!check(A,b,point) ) return {-1,point};
  return {0, point};
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

  pair<int, vector<double>> ans = allocate_ads(n, m, A, b, c);

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
