/* 
 * File:   functions-06.cpp
 * Author: naqvisy1
 *
 * Created on February 24, 2015, 11:46 AM
 */

// Example program
#include <iostream>
#include <string>
using std::string;
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "functions-06.h"
#include <vector>
#include <cctype>
using std::copy_if;
using std::sort;
using std::ifstream;
using std::cout;
using std::endl;
using std::back_inserter;

string generate(int consonant_cnt, int vowel_cnt, long seed) {
//generate function that returns random string with correct consonant count
//and correct vowel count
    //initializing variables
    string full_conson;
    string full_vowel;
    string conson;
    string full_string;
    string vowel;
    int count;
    count = 0;
    std::mt19937_64 randomGenerator(seed);
    std::uniform_int_distribution<int> dist(0, 20);
    //creating a string with all vowels and consonants
    vowel = "aeiou";
    conson = "bcdfghjklmnpqrstvwxyz";
    //while loop that iterates through and fills full_conson 
    //pulling letters from the conson string
    while (full_conson.size() < consonant_cnt) {
        full_conson = full_conson + conson[dist(randomGenerator)];
    }
    std::uniform_int_distribution<int> dist2(0, 4);
    //while loop that iterates through and fills full_vowel 
    //pulling letters from the vowel string
    while (full_vowel.size() < vowel_cnt) {
        full_vowel = full_vowel + vowel[dist2(randomGenerator)];
    }
    //concatenate string
    full_string = full_vowel + full_conson;
    sort(full_string.begin(), full_string.end());
    return full_string;


}

void setup(map<string, vector<string >> &m) {
//setup function sorts the words and adds them to the key and puts the words as values to the vector
    string words;
    string sortedwords;
    int count;
    count = 0;
    //opening words.txt
    ifstream myfile("words.txt");
    if (myfile.is_open()) {
        //while loop iterates through the words.txt
        while (getline(myfile, words)) {
            sortedwords = words;
            //sort the words and make them the key
            sort(sortedwords.begin(), sortedwords.end());
            auto location = m.find(sortedwords);
            //if key exists add the word to the vector
            if (location != m.end()) {
                (location -> second).push_back(words);
            } else {
                //if key doesn't exist then make the key and add the string
                vector<string> temp;
                temp.push_back(words);
                m[sortedwords] = temp;
            }
        }
        myfile.close();
    } else {
        //if file not found put this error
        cout << "File not found" << endl;
    }

}

string longest_anagram(map<string, vector<string >> &m, string target) {
//return longest anagram
    //initializing variables
    string keys1;
    string str2;
    string temp;
    string first_word;
    vector<string> v;
    int count;
    //for loop iterates through map
    for (auto itr = m.begin(); itr != m.end(); itr++) {
        str2 = "";
        keys1 = (itr -> first);
        //intersect determines validity of keys
        std::set_intersection(keys1.begin(), keys1.end(), target.begin(), target.end(), std::back_inserter(str2));
        //if the key is valid then add the values to the vector
        if (str2 == keys1){
            count = 0;
                while (count < (itr -> second).size()){
                    temp = (itr -> second)[count];
                    v.push_back(temp);
                    count = count + 1;
                }
            //if the key doesn't work then get the next key

            }
        }
    //sort the vector
    sort(v.begin(), v.end());
    //set first_word to the first word in the vector
    first_word = v[0];
                //iterate through the vector
                for (string words :v){
                    //if size of words which is the words in the vector is larger than first_word
                    //then first_word is equal to that word
                    if(words.size() > first_word.size()){
                        first_word = words;
                    }
                }
    return first_word;
    }


