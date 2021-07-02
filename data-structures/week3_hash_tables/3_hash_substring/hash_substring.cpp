#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef  long long ull;

const ull prime = 1000000007, multiplier = 263;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

bool same_string(const string& a, const string& b, int pos){
    if(b.size()+pos > a.size()) return false;
    for(int i = 0;i < b.size();++i)
        if(a[i+pos]!=b[i])
            return false;
    return true;
}

ull poly_hash(const string& s){
    ull hash = 0;
    for (int i = s.size() - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}



std::vector<ull> pre_compute_hashes(const string& s, int len){
    std::vector<ull> ans(s.size()-len+1);
    string last_sub = s.substr(s.size()-len,len);
    ans[s.size()-len] = poly_hash(last_sub);
//    std::cout << ans[s.size()-len] <<"\n";
    ull y = 1;
    for(long long i = 0; i < len ; ++i) y = (y*multiplier) %prime;
    for(int i = s.size()-len-1; i >= 0; --i){
        ans[i] = (((multiplier * ans[i+1])%prime + s[i])%prime - y*s[i+len]) %prime;
        ans[i] = (ans[i]+prime)%prime;
    }
    return ans;

}



std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.text, t = input.pattern;
    std::vector<int> ans;
    ull sub_hash = poly_hash(t);
//    std::cout << sub_hash << "\n";
    std::vector<ull> hashes = pre_compute_hashes(s,t.size());
    for(int i = 0; i <= s.size()-t.size(); ++i){
//        std::cout << hashes[i] << " " << sub_hash << std::endl;
        if(hashes[i]!=sub_hash) continue;
        else if(same_string(s,t,i)) ans.push_back(i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
//    std::cout << poly_hash("test")<<"\n";
//    std::vector<ull> hashes = pre_compute_hashes("testTesttesT",4);
//    std::cout << hashes[0];
    return 0;
}
