/*
proj07 : Aut-Completion and Spell checkers
section 3
10/27/2018
*/

#include "proj07_functions.h"

#include<fstream>
using std::ifstream;

#include<string>
using std::string;

#include<set>
using std::set;

#include<vector>
using std::vector;

#include<cctype>

#include<iostream>
using std::cout; using std::endl;

#include<algorithm>
using std::find; using std::remove;using std::remove_if; using std::search;using std::distance; 
using std::transform; using std::copy; using std::set_union;

#include<iterator>
using std::iterator;using std::back_inserter; using std::ostream_iterator;

void read_words(string fname, set<string> &result){
    /*
    reads the file through the file name ,and putout each line of the text file,
    then go through each characcter of it and sort out lower case of the alphabet
    converted words separted by space are inserted into the set.
    */
    string line;
    string word;
    ifstream infile(fname);
    
    while(!infile.eof()){
        
        getline(infile,line);

        for (char chars: line){
            if (isalpha(chars)){
                word += tolower(chars);    
            }
        }
        
        if (word!=""){
        result.insert(word);
        }
        word ="";
        }
}


void deletes(const string &word, set<string> &result){
    /*
    it creates all the single letter deletes possible from the argument word
    and passes them in the arguement result
    */
    int len = word.length();
    string word1 = word;
    for ( int i =0; i !=len; i++){
        {
            word1.erase(i,1);
            result.insert(word1);
            word1 = word;
        }
    }
}

void transposes(const string &word, set<string> &result){
    /*
    it creates all the single letter transpositions possible from the argument word 
    and places them in the arguemtn result
    */
    string swi;
    int a = word.length();
    string word1= word;
    string word2;
    for (int i=0; i !=a-1; i++){
        word2 = word1.substr(i+1,1) + word1.substr(i,1);
      
        word1.replace(i,2,word2);

        result.insert(word1);
        word1 = word;
    }
 
}


void replaces(const string &word, set<std::string> &result){
    /*
    it creates all the single letter replaces possible from the argument word and
    places them in the argument result
    */
    int len = word.length();
    string word1 = word;
    for( int i=0; i !=len; i++){
        word1.erase(i,1);
        
        for (char chars : letters){
            string word2 = word1;
            if (chars == word[i]){
                continue;
            }
            string sub(1,chars);
            word2.insert(i,sub);
            
            
            
            result.insert(word2);
            }
        word1 = word;
        result.insert(word);
    }
}


void inserts(const string &word, set<std::string> &result){
    /*
    it creates all the single letter insertions possible from the argument word and
    places them in the argument result
    */
    string word1= word;
    int len = word.length();
    
    for (int i=0; i != len+1;i++){ 

        for (char chars: letters){
            string sub(1,chars);
            
            word1.insert(i,sub);
            
            result.insert(word1);

            word1= word;
        }
    }
}


void find_completions(const string &word,const set<string> &word_list,set<string> &result) {
for (auto ele:word_list){
    /*
    the function takes in a word 'w' as a string, and a set of valid words
    */
auto pos = search(ele.begin(),ele.end(),word.begin(),word.end());
    if (ele.find(*pos) != 0){
        continue;
    }
    if (pos != ele.end()){  
        result.insert(ele);
    }
}
}


void find_corrections(const string &word,set<string> &result) {
/*
    the function takes in a wored as a string, and calculates the deletes,inserts, tranposes, and 
    replaces sets for the word
*/
    deletes(word,result);
    inserts(word,result);
    transposes(word,result);
    replaces(word,result);

}

void find_2step_corrections(const string &word,set<string> &result) {
    /*
    takes in a word as a string, and calculates 2 levels of the deletes, inserts,
    transposes, and replaces sets for the word
    */

    find_corrections(word, result);
    vector<string> sum_vec;
    set<string> sum_set;
    for (string element: result){
        set<string> result1;
        find_corrections(element,result1);

        vector<string> vec;
        copy(result1.begin(),result1.end(),inserter(vec,vec.end()));

        copy(vec.begin(),vec.end(),inserter(sum_vec,sum_vec.end()));
    }
    
    copy(sum_vec.begin(),sum_vec.end(),inserter(sum_set,sum_set.end()));
    
    set_union(sum_set.begin(),sum_set.end(),result.begin(),result.end(),inserter(result,result.end()));
    
    
}
 

 void find_reasonable_corrections(const set<string> &possibles,const set<string> &word_list,set<string> &result){

/*
for every word in a possibles, check if that word exists in the word_list
*/
for (auto ele:possibles){
    if (word_list.find(ele) != word_list.end()){
        result.insert(ele);
   
    }
    }
}
