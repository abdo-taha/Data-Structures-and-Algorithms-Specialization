#include <iostream>
#include <math.h>
#include <utility>
#include <stdio.h>
#include <time.h>
#include <map>
#include <cassert>
#include <random>
using namespace std;


typedef long long ll;

ll prime  = 1e9+7;
default_random_engine gen;
uniform_int_distribution<int> dist(1, prime);
vector<ll> a,b,sa,sb; 
vector<vector<ll>> count_sketch;

ll mhash(ll x, ll a, ll b){
    return (x * a + b )%prime;
}

int sign(ll x, ll sa, ll sb){
    ll t = ( (x * sa+ sb) % prime ) % 100;
    if(t < 50) return -1;
    return 1;
}



void init_hash(int n){
    int t = log(n)+1;
    int m = t * 50;
    count_sketch.resize(t,vector<ll>(m,0));
    a.resize(t); b.resize(t); sa.resize(t); sb.resize(t);
    for (int i = 0; i < t; i++)
    {
        a[i] = dist(gen);
        b[i] = dist(gen);
        sa[i] = dist(gen);
        sb[i] = dist(gen);
    }
    
}

void add(int id, int value){
    int mod = count_sketch[0].size();
    for (int i = 0; i < count_sketch.size(); i++)
    {
        count_sketch[i][ mhash(id,a[i],b[i])%mod ] += sign(id,sa[i],sb[i]) * value;
    }
    
}

int ans(int id){
    ll tmp = 0;
    int mod = count_sketch[0].size();
    for (int i = 0; i < count_sketch.size(); i++)
    {
        tmp += count_sketch[i][ mhash(id,a[i],b[i])%mod ] * sign(id,sa[i],sb[i]);
    }
    tmp /= count_sketch.size();
    return (int) tmp;
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);

    int id, value;
    init_hash(n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &id, &value);
        add(id,value);
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &id, &value);
        add(id,-value);
    }

    int num_queries = 0;
    scanf("%d", &num_queries);
    for (int q = 0; q < num_queries; ++q) {
        int query = 0;
        scanf("%d", &query);

        
        if (ans(query) >= t)
            cout << "1 ";
        else
            cout << "0 ";
    }

    return 0;
}



