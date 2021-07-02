#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int to_int(const char &ch){
    if(ch=='$') return 0;
    if(ch=='A') return 1;
    if(ch=='C') return 2;
    if(ch=='G') return 3;
    return 4;
}
char to_char(int x){
    string s = "$ACGT";
    return s[x];
}


string InverseBWT(const string& bwt) {
    string text = "",srt = "";
    vector<int> cnt(5);
    for(const char &ch: bwt) ++cnt[to_int(ch)];
    for(int i = 0; i < 5; ++i){
        srt += string(cnt[i],to_char(i));
    }
    for(int i = 1; i < 5; ++i) cnt[i] += cnt[i-1];
    vector<int> nxt(bwt.size());
    vector<int> cnt2(5);
    for(int i = 0; i < bwt.size(); ++i){
        int pos = to_int(bwt[i]);
        --pos;
        if(pos < 0) {
            nxt[i] = 0;
            continue;

        }
        nxt[i] = cnt[pos] + cnt2[pos];
        ++cnt2[pos];
    }

    int pos = 0;
    text = "$";
    while(true){
        pos = nxt[pos];
        if(!pos) break;
        text += srt[pos];
    }
    reverse(text.begin(),text.end());

    return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
