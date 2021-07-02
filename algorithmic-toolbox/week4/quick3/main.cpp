#include <bits/stdc++.h>

using namespace std;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}


void partition3(vector<int>&a, int l, int r , int p[]) {
    int x = a[l];
    int j = l, k = l;
    for(int i = l + 1 ; i <= r ; ++i ) {
        if(a[i] < x) {
            ++k;
            ++j;
            swap(a[i],a[k]);
            swap(a[k],a[j]);
        }
        else if(a[i]==k) {
            ++k;
            swap(a[i],a[k]);
        }
    }
    swap(a[l],a[j]);
    p[0] = j;
    p[1] = k+1 ;


}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int p[2];
  partition3(a,l,r,p);
  randomized_quick_sort(a, l, p[0]);
  randomized_quick_sort(a, p[1], r);
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    cout << a[i] << ' ';
  }
}
