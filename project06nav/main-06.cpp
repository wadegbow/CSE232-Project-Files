#include<string>
using std::string;
#include<iostream>
using std::cout; using std::endl;
#include<map>
using std::map;
#include<vector>
using std::vector;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include "functions-06.h"

int main (){
    string target;
    string found;
    map<string, vector<string>> dict;
    setup(dict);

    // test setup
    vector<string> v;
    int longest=0;
    string str;
    for(auto itr=dict.begin(); itr!=dict.end(); itr++){
    if (itr->second.size() > longest){
        longest = itr->second.size();
        v = itr->second;
        str = itr->first;
    }
    }
    cout << str<< ":";
    copy(v.begin(),v.end(),ostream_iterator<string>(cout, ", "));
    cout << endl;

    // test generate
    for (int i=0;i<20;i++) {
        target = generate(20,8,i);
        found = longest_anagram(dict,target);
        cout << "Target:"<<target<<", found:"<<found<<endl;        
    }

    // test longest_anagram
    //target = "abdoopr";
    //found = longest_anagram(dict,target);
    //cout << "Target:"<<target<<", found:"<<found<<endl;


}