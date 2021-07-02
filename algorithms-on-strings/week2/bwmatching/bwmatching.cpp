#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position
//       of this character in the sorted array of
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt,
                   map<char, int>& starts,
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  string ordered = bwt;
  sort(ordered.begin(),ordered.end());
  for(int i = ordered.size()-1; i >= 0; --i) starts[ordered[i]] = i;
  string temp = "ACGT$";
  for(char ch : temp){
    occ_count_before[ch].resize(bwt.size()+1,0);
    for(int i = 0; i < bwt.size(); ++i) occ_count_before[ch][i+1] = occ_count_before[ch][i] + (bwt[i] == ch);
  }
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern,
                     const string& bwt,
                      map<char, int>& starts,
                      map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  int top = 0, bottom = bwt.size()-1,pos = pattern.size()-1;
  while(pos >= 0){
    char ch = pattern[pos--];
    if(  occ_count_before[ch][top] !=  occ_count_before[ch][bottom+1]){
        top = starts[ch] + occ_count_before[ch][top];
        bottom = starts[ch] + occ_count_before[ch][bottom+1]-1;
    }
    else return 0;
  }

  return bottom-top+1;
}


int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
