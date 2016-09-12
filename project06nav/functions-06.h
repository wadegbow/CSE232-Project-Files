#ifndef COUNTDOWN
#define COUNTDOWN
#include<string>
using std::string;
#include<map>
using std::map;
#include<vector>
using std::vector;

void setup(map<string, vector<string>> &m);
string generate(int cons_cnt, int vowel_cnt, long seed);
string longest_anagram(map<string, vector<string>> &m, string target);

#endif
