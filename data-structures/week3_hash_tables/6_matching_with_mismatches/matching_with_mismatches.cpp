#include <bits/stdc++.h>

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const long long m = 1000000007;
long long x;

void calculate_prehash(vector<long long>& pre_hash ,const string& s,long long m){
    pre_hash[0] = 0;
    for(int i = 1; i <= s.size(); ++i){
        pre_hash[i] = ((x * pre_hash[i-1] )%m + s[i-1]) %m;
    }
}

//long long sum_range(int pos1 , int pos2, vector<long long>& pre_hash){
//    long long ans = pre_hash[pos2+1]-pre_hash[pos1];
//    return ans;
//}

long long sub_hash(int pos, int len, vector<long long>&pre_hash_1,long long m,vector<long long>& powers1){
        long long h = pre_hash_1[pos+len];
        long long power = powers1[len];
        h = (h - (power * pre_hash_1[pos])%m )%m;
        h = (h+m)%m;
        return h;
}

bool check(int pos,const string &text, const string &pattern,int k,vector<long long>& pre_hash_text,vector<long long>&pre_hash_patt,vector<long long>&powers){
    int l = pos , r = pos+pattern.size()-1,md;
    int cnt = 0;
    while(l<pos+pattern.size()){
        r = pos+pattern.size()-1;
        while(l<=r){
            md = (l+r)/2;
            if( sub_hash(l,md-l+1,pre_hash_text,m,powers) == sub_hash(l-pos,md-l+1,pre_hash_patt,m,powers)){
                l = md+1;
            }
            else r = md-1;
        }
        if(l!=pos+pattern.size()) ++cnt;
        ++l;
    }
    return cnt <= k;

}

vector<int> solve(int k, const string &text, const string &pattern) {
	vector<int> pos;
	x =  uniform_int_distribution<long long>(1,m)(rng);
	vector<long long> pre_hash_text(text.size()+1), pre_hash_patt(pattern.size()+1),powers(max(pattern.size(),text.size())+1);
	calculate_prehash(pre_hash_text,text,m);
	calculate_prehash(pre_hash_patt,pattern,m);
    powers[0] = 1;
    for(int i = 1; i < powers.size(); ++i){
        powers[i] = powers[i-1] * x %m;
    }

    for(int i = 0; i <= text.size()-pattern.size(); ++i){
        if(check(i,text,pattern,k,pre_hash_text,pre_hash_patt,powers)) pos.push_back(i);
    }


	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
