/*
Projtect09 BiMap
Section 3
11/19/2018

Creating Map with both using key and value as look up value
The BiMapclass maintains 
two private data member vector< pair< string, string > > ordered_by_keys_ and vector< pair<string, string > > ordered_by_vals_
*/






#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string; using std::to_string; using std::stoi;
#include<algorithm>
using std::copy; using std::lower_bound; using std::find;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;
#include <utility>
using std::pair; using std::make_pair;


#include "proj09_bimap.h"


BiMap::BiMap(initializer_list< pair<string, string> > vec){
    
    /*
    if the string as a key is in the BiMap, do nothing and return false. Otherwise create a pair with the argument values and insert the new pair into the vectors, in sorted order, and return true.
    */
    for( auto i = vec.begin();i< vec.end(); i++){
        add((*i).first,(*i).second);
    }
    
}


	
vector< pair <string, string> >::iterator BiMap::find_key(string key){
    /*
     Uses lower_bound, returns an iterator to a pair<string, string> that is either the first pair in the vector that is equal to (by key) or greater than the key, or ordered_by_keys_.end() (the last two meaning that the key isn't in ordered_by_keys_)
	 Must be private because ordered_by_keys_ is private and we cannot return an iterator to a private data structure.
    */
    
    auto itr = lower_bound(ordered_by_keys_.begin(), ordered_by_keys_.end(),key,[](pair<string,string> aa, string key) ->bool {return aa.first < key;});

    return itr;
    }
    


vector< pair <string, string> >::iterator BiMap::find_value(string value){
	auto itr = lower_bound(ordered_by_vals_.begin(), ordered_by_vals_.end(),value,[](pair<string,string> aa, string value) ->bool {return aa.second < value;});

    return itr;
	}

	
	// if the string as a key is in the BiMap, do nothing and return false. Otherwise create a pair with the argument values and insert the new pair into the vectors, in sorted order, and return true.
bool BiMap::add(string a, string b){
   
   /*
   if the first string as a keyor the second string as a value  is in the 
BiMap, do nothing and return false. Otherwise create a pair with the argument valuesand insert the new pair into the vectors, in sorted order, and return true
   */
    auto aa =find_key(a);
    auto bb = find_value(b);
    pair<string,string> add = make_pair(a,b);

    
    
    for (size_t i =0; i<ordered_by_keys_.size();i++){
        
        if(ordered_by_keys_[i].first == a || ordered_by_keys_[i].second == b){
            
          
            return false;
        }
    }
    
    
    
    if ((aa == ordered_by_keys_.end() || bb == ordered_by_vals_.end()) ){
        
        
        
        if (ordered_by_keys_.size()==0){
         
            ordered_by_keys_.push_back(add);
            ordered_by_vals_.push_back(add);
            return true;
        }
    
        else{
            
                
    ordered_by_keys_.insert(aa,add);
    ordered_by_vals_.insert(bb,add);
    
    return true;
    }
        }
        
        
        if (a==b){
            ordered_by_keys_.insert(aa,add);
              ordered_by_vals_.insert(bb,add);
              return true;
        }
            
            ordered_by_keys_.insert(aa,add);
             ordered_by_vals_.insert(bb,add);
        
        
        return true;
            
    }
// Returns the size of the BiMap (number of pairs) as an unsigned int
size_t BiMap::size(){
// Returns the size of the BiMap (number of pairs) as an unsigned int
    size_t in = ordered_by_keys_.size();
    return in;
    
}

	// Return the key associated with the value. If the value does not exist, then return the empty string.
string BiMap::key_from_value(string a){
    /*
    member function. Return the key associated with the value. 
If the value does not exist, then return the empty string.
    */
    

    if (find_value(a) == ordered_by_vals_.end() || (*find_value(a)).second != a ) {
        return "";
    }
    else{
        return (*find_value(a)).first;
    }
}

string BiMap::value_from_key(string b){
    /*
    member function. Return the value associated with the key.  
If the key does not exist, then return the empty string
    */
    if (find_key(b) == ordered_by_keys_.end() || (*find_key(b)).first != b ){
        return "";
    }
    
    else {
        return  (*find_key(b)).second;
    }
    

}    

// if the first string as a key is in the BiMap, update the key - value pair to the value of the second parameter. Return true. 
	// If the key is not in BiMap, do nothing and return false.
bool BiMap::update(string a, string b){
    
    /*
    if the first string as a key is in the BiMap, and the second string as a value is not,update the key-value pair to the value of the second parameter. Return true. If the key is not in BiMap, do nothing and return false.
    */
    
    for (size_t i = 0; i<ordered_by_keys_.size(); i++){
        
     
        if(ordered_by_keys_[i].first == a){
            ordered_by_keys_[i].second = b;
            ordered_by_vals_[i].second = b;

            return true;
        }
}
return false;
}
	// Look for element, as either a key or a value. If found, remove both the key and value from the BiMap and return that pair<key, value>(that order).
	// if the element does not exist as either a key or a value, return a pair of empty strings.
	// if element exists as both a key and a value, remove both pairs, and return a pair with the key that was associated with element, and the value that was associated with element.
pair<string, string> BiMap::remove(string a){
/*
member function. Look for element, as either a key or a value

*/
    pair<string,string> result;
    

    if (find_key(a) !=ordered_by_keys_.end() 
    &&(*find_value(a)).second == a &&  
    find_value(a) != ordered_by_vals_.end()
    &&(*find_key(a)).first == a
    ){
       
        
        
        auto key_new = key_from_value(a);
        
        
        
        
        auto val_new = value_from_key(a);  
        

        
        if (key_new == val_new ){
            
            
            if (a == key_new && a == val_new){
            
            ordered_by_keys_.erase(find_key(a));
            
            
            ordered_by_vals_.erase(find_value(a));
            
            
            return *(find_value(a));
            }
            
            
            ordered_by_keys_.erase(find_key(a));
            ordered_by_keys_.erase(find_key(key_new));
            
            ordered_by_vals_.erase(find_value(a));
            ordered_by_vals_.erase(find_value(val_new));
            
            return make_pair(a,a);
            

        }
        

        ordered_by_keys_.erase(find_key(a));
        ordered_by_keys_.erase(find_key(key_new));
        
        ordered_by_vals_.erase(find_value(a));

        ordered_by_vals_.erase(find_value(val_new));

        auto cc = make_pair(key_new,val_new);
        return cc;
        
        
        
        
        
        
        
        
        if((*find_value(a)).second == a ){
            
            auto result = *(find_value(a));
            
            auto result1 = find(ordered_by_keys_.begin(),ordered_by_keys_.end(),result);
            
            
            ordered_by_keys_.erase(result1);
            ordered_by_vals_.erase(find_value(a));
            
            return result;
        }
        
        if((*find_key(a)).first == a){
            
            
            auto result = *(find_key(a));
            auto result1 = find(ordered_by_vals_.begin(), ordered_by_vals_.end() ,result);
            
            ordered_by_keys_.erase(find_key(a));
            ordered_by_vals_.erase(result1);
            
            return result;
        }
        
        
        

    }

    
    else if (find_value(a) != ordered_by_vals_.end()    &&a ==  (*(find_value(a))).second    )    {
  
            auto result = *(find_value(a));
            auto result1 = find(ordered_by_keys_.begin(),ordered_by_keys_.end(),result);
            
            ordered_by_vals_.erase(find_value(a));
            
            
            ordered_by_keys_.erase(result1);
   
            return result;
        }
    
        else if (find_key(a) != ordered_by_keys_.end()  &&
        a== (*find_key(a)).first    )     {

            auto result = *(find_key(a));
            
            auto result1 = find(ordered_by_vals_.begin(),ordered_by_vals_.end(),result);
            
            
            ordered_by_keys_.erase(find_key(a));
            ordered_by_vals_.erase(result1);
            
            return result;
        }
        
        
        
        else{
            
            return make_pair("","");
        }
        
     
}

int BiMap::compare(BiMap & bm){
    
    
    /*
    compare the two BiMapslexicographically, that is element by element using the string-key of the pairs as comparison values
    */
    vector<string> vec;
    vector<string> vec1;
    size_t size;
    for (auto i =0; i<ordered_by_keys_.size(); i++){
        
        vec.push_back(ordered_by_keys_[i].first);
       
    }
    
    for (auto j=0; j<bm.ordered_by_keys_.size(); j++){
        vec1.push_back(bm.ordered_by_keys_[j].first);

    }
    
    
    
    auto size1 = ordered_by_keys_.size();
    auto size2 = bm.ordered_by_keys_.size();
    
    
    if(size1 > size2){
        size = bm.ordered_by_keys_.size();
    }
    else{
        size = ordered_by_keys_.size();
    }
    
    
    
    for (size_t z=0; z< size; z++){
        if (vec[z] != vec1[z]){
            
            if(vec[z]>vec1[z] ){
                return 1;
            }
            else if(vec[z]<vec1[z] ){
                return -1;
            }
        }
        
        
        else if (z ==size-1 && vec[z] == vec1[z]) {
            
            if(vec.size()>vec1.size()){
            
                return 1;
            }
            
            else if (vec.size()<vec1.size()){
                return -1;
            }
            
            else {
                return 0;
            }
            
        }
    }
    
    
}    
    
    
    
BiMap BiMap::merge(BiMap &bm ){
    
    
    /*
    Merges the current BiMapwith the BiMapbeing passed in, creating a new BiMapwith the values of both;if both BiMapshave overlapping keys or values, keep those from the calling BiMa
    */
    
    BiMap bm_;
    bm_ = *this;
    
    vector<int> q;
    for (auto k =0; k<bm_.ordered_by_keys_.size();k++){
        
        
        q.push_back( stoi(bm_.ordered_by_keys_[k].second));
        
    }
    
    
    vector<pair<string,string>>::iterator aa;
    vector<pair<string,string>>::iterator bb;
    
    for( auto i = 0;  i< bm.ordered_by_keys_.size(); i++){
        
        aa = bm_.find_key(bm.ordered_by_keys_[i].first);
        
         
        bb = bm_.find_value(bm.ordered_by_vals_[i].second);

    if (aa != bm_.ordered_by_keys_.end() && (*aa).first ==bm.ordered_by_keys_[i].first) {
           
            continue;            
        }
        
    int w = stoi(bm.ordered_by_keys_[i].second);
  
    if( find(q.begin(),q.end(),w) !=q.end() ){
        continue;
    }
    
    
            bm_.ordered_by_keys_.insert(aa,bm.ordered_by_keys_[i]);
        
        
    }
    

    return bm_;
}


ostream& operator<<(ostream& out, BiMap& BiMap){
    /*
    Returns the ostream after writing the BiMapto the ostream
.  The formatting should have each pair colon (‘:’) separated, and each pair comma + space separated (‘, ‘), with no trailing comma

    */
    
    ostringstream oss;
    for (size_t i =0; i<BiMap.ordered_by_keys_.size();i++){
        
        oss<<BiMap.ordered_by_keys_[i].first<<" : "<<BiMap.ordered_by_keys_[i].second<<", ";
    }
    
    out<<oss.str().substr(0, (oss.str().size()-2));
    return out;
}









