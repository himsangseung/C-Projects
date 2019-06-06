/*
Project 10 BiMap(Dynamic Memoery)

Section 3
11/28/2018

Project Specificaion is same as that of project 8, however this project
concerns with dealing with dynamic memoery, using arrys to build BiMap Class 
AND also Node Class instead of std::pair

*/

#pragma once

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound; using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;

template<typename K, typename V>
struct Node {
/*
Struct Node is built so that it can replace std::pair
acts same as pair however templated
    
*/
	K first;
	V second;
	Node() = default;
	Node(K, V);
	bool operator<(const Node&) const;
	bool operator==(const Node&) const;
	friend ostream& operator<<(ostream &out, const Node &n) {

		out<<n.first<<":"<<n.second;
		return out;
	}
};


template<typename K, typename V>
Node<K,V>::Node(K key ,V value){
    /*
    constructuor for two args of Node Struct
    stores two varaiables in 
    */
    first = key;
    second = value;

}

template<typename K, typename V>
bool Node<K,V>::operator<(const Node & node) const{
    /*
    < operator to compare first value in two Nodes
    
    */
     if (first <node.first){
         return true;
     }
     
     else{
         return false;
     }
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node & node) const{
    /*
    == operator to compare first value in two Nodes
    */
    if (first == node.first){
        return true;
    }
    else{
        return false;
    }
}


template<typename K, typename V>
class BiMap {
/*
Main class of the project, using Node and build arrays of Nodes to be utilized
to have BiMap functionality.

*/
private:
	Node<K, V>* ordered_by_keys_;
	Node<K, V>* ordered_by_vals_;
	size_t last_;
	size_t capacity_;
	Node<K, V>* find_key(K key);
	Node<K, V>* find_value(V value);
	void grow();

public:
	BiMap(int sz = 2);
	BiMap(initializer_list< Node<K, V> >);
	BiMap(const BiMap&);
	BiMap operator=(BiMap);
	~BiMap();
	size_t size();
	
	int index_k(K);
	int index_v(V);
	
	V value_from_key(K);
	K key_from_value(V);
	bool update(K, V);
	K remove_val(V value); 
	V remove_key(K key); 
	bool add(K, V);
	int compare(BiMap &);
	
	friend ostream& operator<<(ostream &out, const BiMap &bm) {
    /*
    puts out ordered_by_keys_, each element for first and second value
    */
	    ostringstream oss;

	    for (auto i=0; i< bm.last_; i++){
	        
	     	//oss<< bm.ordered_by_vals_[i].first<<":"<<bm.ordered_by_vals_[i].second<<", ";   
	        
	        oss<< bm.ordered_by_keys_[i].first<<":"<<bm.ordered_by_keys_[i].second<<", ";
	    }
	    out<<oss.str().substr(0, (oss.str().size() -2));
	    
    return out;
		//WRITE OPERATOR<< CODE HERE
	}
};

template <typename K, typename V>
BiMap<K,V>::BiMap(int sz ){
    /*
    constrcutor of BiMap with one arg
    */
    
    last_ =0;
    capacity_ = sz;
    ordered_by_keys_ = new Node<K,V>[sz]{};
    ordered_by_vals_ = new Node<K,V>[sz]{};
    
}

template <typename K, typename V>
BiMap<K,V>::BiMap(const BiMap<K,V> &Bi){
    /*
    Copy constructor of BiMap
    */
    last_ = Bi.last_;
    capacity_ = Bi.capacity_;
    ordered_by_keys_ = new Node<K,V>*[Bi.last_];
    ordered_by_vals_ = new Node<K,V> * [Bi.last_];
    
    copy(Bi.ordered_by_keys_,Bi.ordered_by_keys_+Bi.last_, ordered_by_keys_);
    copy(Bi.ordered_by_vals_,Bi.ordered_by_vals_+Bi.last_,ordered_by_vals_);
    
}



template <typename K, typename V>
    BiMap<K,V>::~BiMap(){
    /*
    Destrcutor for the created arrays    
    */
    delete [] ordered_by_keys_;
    delete [] ordered_by_vals_;

}

template <typename K, typename V>
BiMap<K,V>::BiMap (initializer_list< Node<K, V> > N ){
    /*
    initalizer constructor
    */
        last_ =0;
        for( auto i = N.begin();i< N.end(); i++){
        add((*i).first,(*i).second);
    }
    
}

template<typename K, typename V>
size_t BiMap<K,V>::size(){
    /*
    returning current size of array of the arrys built
    */
    return last_;
    
}


template<typename K, typename V>
void BiMap<K,V>::grow(){
    /*
    grows its capacity based on its last_ value
    */
 
    Node<K,V> * new_ary;
    Node<K,V> * new_ary2;
    
  if (last_ == 0){
    new_ary = new Node<K,V>[1]{};
    new_ary2 = new Node<K,V>[1]{};
 
    capacity_ =1;
    
     ordered_by_keys_= new_ary;
     ordered_by_vals_ = new_ary2;

  }
  else if (last_ >= capacity_){
  
    new_ary = new Node<K,V>[capacity_* 2]{};
    new_ary2 = new Node<K,V> [capacity_*2]{};
    copy(ordered_by_keys_,ordered_by_keys_+last_, new_ary);
    copy(ordered_by_vals_,ordered_by_vals_+last_,new_ary2);
    
    capacity_*= 2;
    // stl swap, not Stack swap
    std::swap (new_ary, ordered_by_keys_);
    std::swap(new_ary2,ordered_by_vals_);
    delete [] new_ary;
    delete [] new_ary2;
    
  }
}


template <typename K, typename V>
BiMap<K,V> BiMap<K, V>::operator=(BiMap<K,V> Bi){
    // just did the swap here
    swap(this->last_, Bi.last_);
    swap(this->capacity_, Bi.capacity_);
    swap(this->ordered_by_keys_,Bi.ordered_by_keys_);
    swap(this->ordered_by_vals_,Bi.ordered_by_vals_);
    return *this;
}



template <typename K, typename V>
K BiMap<K,V>::key_from_value(V val){
    K key;
    /*
    use the value input and find key using find_value method
    
    */
    if (find_value(val) == nullptr || (*find_value(val)).second != val  ){
        return key; 
    
}
    
    else{
        return (*find_value(val)).first;
    }
}

template <typename K, typename V>
V BiMap<K,V>::value_from_key(K key){
        /*
    use the key input and find valuey using find_key method
    
    */
    V val =0;
 

    if (find_key(key) == nullptr || (*find_key(key)).first != key ){
        
        return val;
    }
    else {
        return   (*find_key(key)).second;
    }
}  

template <typename K, typename V>
bool BiMap<K,V>::update(K key, V value){
    /*
    updates its value if same key exists but diff value does
    
    */
    
        for (size_t i = 0; i<last_; i++){
        
     
        if(ordered_by_keys_[i].first == key){
            if (ordered_by_keys_[i].second ==value){
                return false;
            }
            else{
            ordered_by_keys_[i].second = value;
             ordered_by_vals_[i].second = value;

            return true;
            }

        }
}
return false;
    
    
}

template<typename K,typename V>
int BiMap<K,V>::index_k(K key){
    /*
    indcating index of the key, used for remove function
    */
    
    auto aa  = *find_key(key);
   
   
   auto cc = find_key(key);

    
    size_t key_index;
    
    for (auto i = 0; i< capacity_; i++){
        if (ordered_by_keys_[i].first == aa.first ){

            return  i;
            
        }
            
    }
}

template<typename K,typename V>
int BiMap<K,V>::index_v (V value){
        /*
    indcating index of the value, used for remove function
    */
   auto bb = *find_value(value);
   auto dd = find_value(value);

    size_t value_index;
    

    for (auto j =0 ; j< capacity_; j++){
        if (ordered_by_vals_[j].second == bb.second ){
            
            value_index = j;
            return j;
        }
    }

}



template<typename K, typename V>
K BiMap<K,V>::remove_val(V value){
    /*
    takes in value and finds its index and removes the corresponding node
    
    */
    K key;
    
    if ( (*find_value(value)).second == value   ){
        key = (*find_value(value)).first;
        Node<K,V>* new_arr = new Node<K,V>[last_]; 
        Node<K,V>* new_arr2 = new Node<K,V> [last_];

        int index_key;
        index_key = index_k(key);
        
        int index_value;
        index_value = index_v(value);
        
        
        copy(ordered_by_keys_, ordered_by_keys_+index_key, new_arr);
        
        copy(ordered_by_keys_+index_key+1, ordered_by_keys_+last_,new_arr+index_key);
        
        copy(ordered_by_vals_, ordered_by_vals_+index_value,new_arr2);
        copy(ordered_by_vals_+index_value+1, ordered_by_vals_+last_, new_arr2+index_value);
        
      
        last_  -=1;
        
        copy(new_arr, new_arr+last_,ordered_by_keys_);
        copy(new_arr2, new_arr2+last_, ordered_by_vals_);
       
        
        std::swap(new_arr,ordered_by_keys_);
        std::swap(new_arr2,ordered_by_vals_);
        
        delete [] new_arr;
        delete [] new_arr2;
        
        return key;
    }
    
    else{
        return key;
    }
 
} 


template<typename K, typename V>
V BiMap<K,V>::remove_key(K key){
        /*
    takes in key and finds its index and removes the corresponding node
    
    */
     V value =0;
    
    if ( (*find_key(key)).first ==  key   ){
        value = (*find_key(key)).second;
        
        Node<K,V>* new_arr = new Node<K,V>[last_]; 
        Node<K,V>* new_arr2 = new Node<K,V> [last_];
        
        
        int index_key;
        index_key = index_k(key);
        
        int index_value;
        index_value = index_v(value);
        
        
        copy(ordered_by_keys_, ordered_by_keys_+index_key, new_arr);
        copy(ordered_by_keys_+index_key+1, ordered_by_keys_+last_,new_arr+index_key);
        

        copy(ordered_by_vals_, ordered_by_vals_+index_value,new_arr2);
        copy(ordered_by_vals_+index_value+1, ordered_by_vals_+last_, new_arr2+index_value);
        
        last_  -=1;
        
        copy(new_arr, new_arr+last_,ordered_by_keys_);
        copy(new_arr2, new_arr2+last_, ordered_by_vals_);
      
        
        std::swap(new_arr,ordered_by_keys_);
        std::swap(new_arr2,ordered_by_vals_);
        
        delete [] new_arr;
        delete [] new_arr2;
        
        return value;

    }
    
    else{
        return value;
    }
}


template<typename K, typename V>
Node<K,V>* BiMap<K,V>::find_key(K key){
    /*
    finds the key using key input
    */
    
    auto itr = lower_bound(ordered_by_keys_, ordered_by_keys_
    +last_,key,[](Node<K,V> aa, K key) ->bool {return aa.first < key;});

    return itr;
    }
    
template<typename K, typename V>
Node<K,V>* BiMap<K,V>::find_value (V value){
        /*
    finds the value using key input
    */
	auto itr = lower_bound(ordered_by_vals_, ordered_by_vals_+last_,value,[](Node<K,V> aa, V value) ->bool {return aa.second < value;});

    return itr;
	}


template <typename K, typename V>
bool BiMap<K,V>::add(K key, V value){
    /*
    adds the element into the created array
    */
    
    Node<K,V> news1;

    grow();

   auto aa  = *find_key(key);
   auto bb = *find_value(value);
   auto cc = find_key(key);
   auto dd = find_value(value);

    size_t key_index;
    size_t value_index;
    
    for (auto i = 0; i< capacity_; i++){
        if (ordered_by_keys_[i].first == aa.first ){
            key_index = i;
            break;
        }
            
    }

    for (auto j =0 ; j< capacity_; j++){
        if (ordered_by_vals_[j].second == bb.second ){
            
            value_index = j;
            break;
        }
    }
    

    if (capacity_ ==1 && last_ ==0 ){
            news1.first = key;
            news1.second = value;
            ordered_by_keys_[last_] = news1;
            ordered_by_vals_[last_] = news1;
            last_ += 1;   
            
            return true;
    }
    
    else if (aa.first == key || bb.second == value){
        capacity_ -=1;
        return false;
    }

  else{
    Node<K,V>* insert_node = new Node<K,V>[capacity_];
    Node<K,V>* insert_node2 = new Node<K,V>[capacity_];
    
  news1.first = key;
  news1.second = value;

  copy(ordered_by_keys_,ordered_by_keys_+key_index,insert_node);
  copy(ordered_by_vals_,ordered_by_vals_+value_index,insert_node2);

    if (key_index ==0){
        insert_node[key_index] =news1;        
    }    
    else if (key_index !=0){
            insert_node[key_index] = news1;
            
        }
       
    if (value_index ==0){
        insert_node2[value_index] = news1;
    }
    else if (value_index !=0){
       
    
        insert_node2[value_index] =news1;
    }

  
  copy(ordered_by_keys_+key_index, ordered_by_keys_+last_,insert_node+1+key_index);
  copy(ordered_by_vals_+value_index,ordered_by_vals_+last_,insert_node2+1+value_index);
  
  last_ +=1; 
  
  copy(insert_node,insert_node+last_,ordered_by_keys_);  
  copy(insert_node2,insert_node2+last_,ordered_by_vals_);
  
  delete [] insert_node;
  delete [] insert_node2;
  
}
  
    return true;
    }

template <typename K, typename V>
int BiMap<K,V>::compare(BiMap<K,V> &bm){
    /*
    comparing the two node of each element in side and puts out 1,-1,0
    */
    K * compare1 = new K[last_];
    K * compare2 = new K[bm.last_];
    
    for (auto i = 0; i< last_; i++){
        compare1[i] = ordered_by_keys_[i].first;    
    }
    
    for (auto j = 0; j< bm.last_; j++){
        compare2[j] = bm.ordered_by_keys_[j].first;
    }
    
    size_t smaller_size;
    
    smaller_size = (last_ > bm.last_)? bm.last_ : last_;
    
    for (auto k=0; k<smaller_size; k++){
        if (ordered_by_keys_[k].first > bm.ordered_by_keys_[k].first){
            return 1;
        }
        else if (ordered_by_keys_[k].first < bm.ordered_by_keys_[k].first){
            return -1;
        }
        
        else if (k == smaller_size-1){
            if (ordered_by_keys_[k].first == bm.ordered_by_keys_[k].first){
                    
                
                if (last_ > bm.last_ ){
                    return 1;
                }
                
                else if (last_< bm.last_){
                    return -1;
                }
            
                else {
                    return 0;
                }
            }
        }
            
    }
   
}
    


    


