#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>
#include <chrono>

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
class Solver {
	string s;
	vector<long long> pre_hash_1 , pre_hash_2, powers1,powers2;
	const long long m1 = 1000000007, m2 = 1000000009;
	long long x;

    long long sub_hash_1(int pos, int len){
        long long h = pre_hash_1[pos+len];
        long long power= powers1[len];
        h = (h - (power * pre_hash_1[pos])%m1 )%m1;
        h = (h+m1)%m1;
        return h;
    }

    long long sub_hash_2(int pos, int len){
        long long h = pre_hash_2[pos+len];
        long long power = powers2[len];
        h = (h - (power * pre_hash_2[pos])%m2 )%m2;
        h = (h+m2)%m2;
        return h;
    }

public:
	Solver(string s) : s(s) {
		pre_hash_1.resize(s.size()+1,0);
		pre_hash_2.resize(s.size()+1,0);
		x = uniform_int_distribution<long long>(1,m1)(rng);
		for(int i = 1; i <= s.size(); ++i){
            pre_hash_1[i] = ((x * pre_hash_1[i-1] )%m1 + s[i-1]) %m1;
            pre_hash_2[i] = ((x * pre_hash_2[i-1] )%m2 + s[i-1]) %m2;

		}
		powers1.resize(s.size()+1);
		powers2.resize(s.size()+1);
		powers1[0] = powers2[0] = 1;
		for(int i = 1; i <= s.size(); ++i){
            powers1[i] = powers1[i-1] * x %m1;
            powers2[i] = powers2[i-1] * x %m2;
		}

	}
	bool ask(int a, int b, int l) {
	    bool check1, check2;
	    check1 = sub_hash_1(a,l) == sub_hash_1(b,l);
	    check2 = sub_hash_2(a,l) == sub_hash_2(b,l);
		return check1 && check2;
	}


};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
