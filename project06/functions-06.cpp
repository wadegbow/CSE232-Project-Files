#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <iostream>
using std::cout; using std::endl; using std::cin;
#include <algorithm>
using std::sort; using std::copy_if;
#include <random>
using std::uniform_int_distribution; using std::mt19937_64;
using std::random_device;
#include <sstream>
using std::ostringstream; using std::istringstream;
#include <iterator>
using std::ostream_iterator; using std::back_inserter;
#include <cctype>
using std::isalnum;



//takes in two strings and counts their characters
//returns false if word has more of any character than target
bool match_anagram(string target, string word) {
    map<char, int> target_map, word_map;

    //build a map that stores character counts for target
    for (char n : target) {
        if (target_map.find(n) == target_map.end()) {
            target_map[n] = 1;
        } else {
            target_map[n] = target_map[n] + 1;
        }
    }

    //build a map that stores character counts for word
    for (char n : word) {
        if (word_map.find(n) == word_map.end()) {
            word_map[n] = 1;
        } else {
            word_map[n] = word_map[n] + 1;
        }
    }

    for (auto item : word_map) {
        //initialize iterator
        map<char, int>::iterator search = target_map.find(item.first);

        if (search == target_map.end()) {
            return false; //return false if the character isn't in the target
        } else {
            //check to see that there are less of the letter than in the target
            if (item.second <= target_map[item.first]) {  
                continue;
            }
            else {
                return false; //the word had more of a character than the target            
            }
        }
    }

    return true;
}

//Takes in a map by reference and fills it with anagrams as keys
//and the correlating words as vector values
void setup(map<string, vector<string>> &m) {
	ifstream words;
	string word, stripped_word, input;

    //try to open words.txt
    try {
        words.open("words.txt");
        //if the file isn't good, throw an error
        if (!words.good())
            throw 1;
    } catch (int e) {
        //when there is an error inform user and exit the program
        cout << "The file was not found." << endl;
        exit(e);
    }
    //loop through the file getting each line
	if(words.is_open()) {
		while (getline(words, word)) {
            //from example:
            // clear the stripped_word
            stripped_word.erase();
            // copy chars from file_word to stripped_word if they are isalnum
            // if you want punctuation as well, use isprint
            copy_if(word.begin(), word.end(),
                back_inserter(stripped_word),
                [](char c){
                    return isalnum(c);
                });
            //end example   
                     
            //initialize the key string then sort
            string key = word;
            sort(key.begin(), key.end());
            //push the word into the vector at the corresponding key
			m[key].push_back(word);
		}
        //close words.txt
        words.close();
	}
}

//Takes in a consonant count, a vowel count and a random number seed
//generates random letter sequence and returns the string
string generate(int cons_cnt, int vowel_cnt, long seed) {
	int key_length = cons_cnt + vowel_cnt;
	string new_key = "", vowels = "aeiou";

    mt19937_64 gen(seed);
    uniform_int_distribution<int> vowel_dist (0,4);
    uniform_int_distribution<int> alpha_dist (97,122);

    //add vowels to our new_key
    for (int n=0; n<vowel_cnt; ++n)
        new_key = new_key + vowels[vowel_dist(gen)];

    //initialize iterator
    string::iterator search;

    //add constanants to new_key
    while (new_key.length() < key_length) {
    	char cons = static_cast<char>(alpha_dist(gen));
    	search = find (vowels.begin(), vowels.end(), cons);

    	if (search == vowels.end())
    		new_key = new_key + cons;
    }

    //sort the new_key alphabetically
    sort(new_key.begin(), new_key.end());

   	return new_key;
}

//Takes in a filled map reference m (from setup) and a sorted string target (from generate) and finds
//the longest combination of target characters that make a legal English word, if any
string longest_anagram(map<string, vector<string>> &m, string target){
    vector<string> possible_anagrams, valid_anagrams;
    string longest_key = "";

    //loop through the items in m
    for (auto item : m) {
        bool invalid = false;

        //loop through the characters in the item key
        for (char c : item.first) {
            //check to see if the character is in the target
            if (find(target.begin(), target.end(), c) == target.end()) {
                invalid = true; //the key was invalid
                break; //break out of loop
            }
        }

        //check if the key is invalid
        if (invalid)
            continue; //key is invalid, restart loop

        //pass the target and the key through match_anagram
        //a value of true means the key is a possible match
        if (match_anagram(target, item.first)) {
            //weed out keys that are too short
            if (item.first.length() >= longest_key.length()) {
                longest_key = item.first;
                //fill vector with possible keys
                possible_anagrams.insert(possible_anagrams.end(), 
                    m[item.first].begin(), m[item.first].end());
            }
        }
    }

    //loop through possible_anagrams, fill new vector with keys
    //that meet the length requirement
    for (auto x : possible_anagrams) {
        if (x.length() == longest_key.length())
            valid_anagrams.push_back(x);
    }

    //sort the valid keys
    sort(valid_anagrams.begin(), valid_anagrams.end());

    //return the first (alphabetically lowest) value
    return valid_anagrams[0];
}