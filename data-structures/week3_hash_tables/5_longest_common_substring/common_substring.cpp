#include <bits/stdc++.h>
/**
needs cleaning

**/

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const long long m1 = 1000000007, m2 = 1000000009;
long long x;

struct Answer {
	size_t i, j, len;
};

void calculate_prehash(vector<long long>& pre_hash_1 ,const string& s,long long m){
    pre_hash_1[0] = 0;
    for(int i = 1; i <= s.size(); ++i){
        pre_hash_1[i] = ((x * pre_hash_1[i-1] )%m + s[i-1]) %m;
    }
}
void calculate_powers( vector<long long>& powers1 , long long x , int sz , long long m ){
    powers1[0] = 1;
    for(int i = 1; i < sz; ++i){
        powers1[i] = powers1[i-1] * x %m;
    }
}

long long sub_hash(int pos, int len, vector<long long>&pre_hash_1,long long m,vector<long long>& powers1){
        long long h = pre_hash_1[pos+len];
        long long power = powers1[len];
        h = (h - (power * pre_hash_1[pos])%m )%m;
        h = (h+m)%m;
        return h;
}

pair<bool, Answer> common( string s,  string t, int len, vector<long long>&pre_hash_11 , vector<long long>&pre_hash_12,vector<long long>&pre_hash_21,vector<long long>&pre_hash_22,vector<long long>&powers2,vector<long long>&powers1){
    Answer ans = {0,0,0};
    map<long long, int> mp1, mp2;

    for(int i = 0; i+len <= s.size(); ++i ){
        long long h1 = sub_hash(i,len,pre_hash_11,m1,powers1);
        long long h2 = sub_hash(i,len,pre_hash_12,m2,powers2);
        mp1[h1] = i;
        mp2[h2] = i;
    }

    for(int i = 0; i+len <= t.size(); ++i ){
        long long h1 = sub_hash(i,len,pre_hash_21,m1,powers1);
        long long h2 = sub_hash(i,len,pre_hash_22,m2,powers2);
        if( mp1.count(h1) && mp1[h1]==mp2[h2]){
            ans = {mp1[h1],i,len};
            return {1,ans};
        }
    }



    return {0,ans};

}


Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	int l = 1 , r = min(s.size(),t.size()),md,longest = 0;
    x =  uniform_int_distribution<long long>(1,m1)(rng);

    int sz = max(s.size() , t.size())+1;
    vector<long long> powers1(sz), powers2(sz),pre_hash_11(sz), pre_hash_12(sz), pre_hash_21(sz), pre_hash_22(sz);
    calculate_powers(powers1,x,max(s.size(),t.size())+1,m1);
    calculate_powers(powers2,x,max(s.size(),t.size())+1,m2);
    calculate_prehash(pre_hash_11,s,m1);
    calculate_prehash(pre_hash_12,s,m2);
    calculate_prehash(pre_hash_21,t,m1);
    calculate_prehash(pre_hash_22,t,m2);


	while(l<=r){
        md = (l+r)/2;
        pair<bool,Answer> check = common(s,t,md,pre_hash_11,pre_hash_12,pre_hash_21,pre_hash_22,powers2,powers1);
//        cout << md << " " << check.first << endl;
        if(check.first){
            l = md +1;
            if(longest < md) {
                longest = md;
                ans = check.second;
            }
        }
        else{
            r = md -1;
        }

	}


	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
