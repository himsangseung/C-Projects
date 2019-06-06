/*
Project 11 BiMap<Singley Linked List>
Similar to project 9 and 10, but singely linked list which uses 'next' pointer to proceed to next element is used
Section: 3
12/05/2018

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
using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;


// Node

template<typename K, typename V>
struct Node {
/*
Struct Node is built so that it can replace std::pair
acts same as pair however templated
*/
  K first;
  V second;
  Node *next = nullptr;
  
  Node() = default;
  Node(K,V);
  Node(const Node&);
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n){
    out<<n.first<<":"<<n.second;
    return out;
  }
};

template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    /*
    constructuor for two args of Node Struct
    stores two varaiables in 
    */
    first = key;
    second = value;
}

template<typename K, typename V>
Node<K,V>::Node(const Node& n){
/*
Copy contructor to be used;
*/
    first = n.first;
    second = n.second;
    next = n.next;
    
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node& n) const{
    /*
    == operator to compare first value in two Nodes
    */
    
    if(first == n.first){
        return true;
    }
    else{
        return false;
    }
}


// BiMap
template<typename K, typename V>
class BiMap{
 private:
  Node<K,V>* ordered_by_keys_head_ = nullptr;
  
  Node<K,V>* ordered_by_vals_head_ = nullptr;
 
  size_t sz_ = 0;

  pair<Node<K, V>*,Node<K, V>*> find_key(K);
  pair<Node<K, V>*,Node<K, V>*> find_value(V);
  
 public:
  BiMap()=default;
  BiMap(initializer_list< Node<K,V> >);
 // BiMap (const BiMap&); copy constructor kept giving error, it is defined below but commented out 
  BiMap operator=(BiMap);
  //~BiMap(); Deconstructor kept giving error, it is defined below but commented out 
  size_t size();
  K remove_val(V value); 
  V remove_key(K key); 
  bool add(K,V);
  V value_from_key(K);
  K key_from_value(V);
  bool update(K,V);  
  int compare(BiMap&);
  BiMap merge (BiMap&);

  friend ostream& operator<<(ostream &out, const BiMap &bm){
      ostringstream oss;
    if (bm.ordered_by_keys_head_->next != nullptr){

    }
      for (auto i = bm.ordered_by_keys_head_; i != nullptr; i = i->next){
          oss<< (i->first)<<":" <<(i->second)<<", ";
      }
     /*
     //for printing ordered_by_vals_head_ sequence
    for (auto i = bm.ordered_by_vals_head_; i != nullptr; i = i->next){
          oss<< (i->first)<<":" <<(i->second)<<", ";
      }
      */
    out<<oss.str().substr(0, (oss.str().size()-2 ));  
    return out;
  }  
  
};
/* it is defined but kept giving overall error so commented out 
template<typename K, typename V>
BiMap<K,V>::~BiMap(){
    Node<K,V>* to_del = ordered_by_keys_head_;
    while (to_del != nullptr){
        ordered_by_keys_head_= ordered_by_keys_head_->next;
        delete to_del;
        to_del= ordered_by_keys_head_;
    }
    Node<K,V>* to_del2 = ordered_by_vals_head_;
    while (to_del2 != nullptr){
        ordered_by_vals_head_= ordered_by_vals_head_->next;
        delete to_del;
        to_del2= ordered_by_vals_head_;
    }    
}
*/


template<typename K, typename V>
BiMap<K,V>::BiMap(initializer_list< Node<K,V> > init){
    /*
    initializer list putting elments in
    */
    for (auto ele : init){
        add(ele.first,ele.second);
    }
    
    
}
/*it is defined but kept giving overall error so commented out 
template<typename K, typename V> 
BiMap<K,V>::BiMap (const BiMap& bm){
    
    bm.ordered_by_keys_head_= ordered_by_keys_head_;
    bm.ordered_by_vals_head_ = ordered_by_vals_head_;
    bm.sz_ = sz_;
     
 }
 */
template<typename K, typename V>
BiMap<K,V> BiMap<K,V>::operator=(BiMap bm){
    /*
    = operator for equating two BiMap class
    */
     swap(ordered_by_keys_head_, bm.ordered_by_keys_head_);
     swap(ordered_by_vals_head_, bm.ordered_by_vals_head_);
     swap(sz_,bm.sz_);
     
          
     return *this;
    }


template<typename K, typename V>
size_t BiMap<K,V>::size(){
    /*
    getting the size of ordered_by_keys_head_ element
    */
    int cnt =0;
    for (auto i = ordered_by_keys_head_; i != nullptr; i = i->next){
        cnt++;
}
    return cnt;
}

template<typename K, typename V>
 V BiMap<K,V>::value_from_key(K key){
     /*
     getting value from key element
     */
    V val =0;
    if (find_key(key).second == nullptr || ( (find_key(key).second) ->first) != key ){
        
        return val;
    }
    else {
        
        return   ( (find_key(key).second)->second);
    }
}  
     
 template<typename K, typename V>
 K BiMap<K,V>::key_from_value(V value){
     /*
     getting key from value element
     */
  K key ="";
  
  //cout<<(find_value(value).second)->first<<endl;
  
  if(find_value(value).second == nullptr || (find_value(value).second -> second) != value  ){
      
      return key;
  }
  else{
         return (find_value(value).second)->first;
  }
     
 }


template<typename K, typename V>
pair<Node<K, V>*,Node<K, V>*> BiMap<K,V>::find_key(K key){
    /*
    find key method using key elemnet,
    this returns first element of the pair which is one element ahead,
    and second element of the pair, one behind
    */
Node<K,V>* lower;
Node<K,V>* upper;
pair<Node<K, V>*,Node<K, V>*> pairs;
    
for ( auto j = ordered_by_keys_head_; j != nullptr; j = j->next ){
     if (j != nullptr && j == ordered_by_keys_head_ && (j->first) >= key){
        pairs.first = nullptr;
        
        if (ordered_by_keys_head_->next == nullptr){ 
            
            if (j->first == key){
              
                pairs.second = j;
            }
            else{
            pairs.second = nullptr;
            }
        }
        else{
            pairs.second = j->next;
        }

        break;
    }
    
    else if (j != nullptr && (j->next) == nullptr){
        lower =j;
        pairs.first = j;
        pairs.second = nullptr;
        break;
    }
    
    else if (j != nullptr && (j->next)->first  >= ( key ) ){
        lower = j;
        upper = j->next;
        pairs.first = j;
        pairs.second = j->next;
        
        break;
    }
}

return pairs;
}

template<typename K, typename V>
pair<Node<K, V>*,Node<K, V>*>  BiMap<K,V>::find_value(V value){
    /*
    find value method using value elemnet,
    this returns first element of the pair which is one element ahead,
    and second element of the pair, one behind
    */
Node<K,V>* lower;
Node<K,V>* upper;
pair<Node<K, V>*,Node<K, V>*> pairs;
for ( auto j = ordered_by_vals_head_; j != nullptr; j = j->next ){
        if (j != nullptr && j == ordered_by_vals_head_ && (j->second) >= value){

        pairs.first = nullptr;
        
        if (ordered_by_vals_head_->next == nullptr || ordered_by_vals_head_->second == value){
            
            if (ordered_by_vals_head_->second == value){
                
                pairs.second = j;
            }
            
            else{
            
            pairs.second = nullptr;
            break;
            }
        }    
        
        else{
         
            pairs.second = j->next;
            break;
        }
        break;
     
    }
    
    else if (j != nullptr && (j->next) == nullptr){
        lower =j;
        pairs.first = j;
        pairs.second = nullptr;
        break;
    }
    else if (j != nullptr && (j->next)->second  >= ( value ) ){
        lower = j;
        upper = j->next;
        pairs.first = j;
        pairs.second = j->next;
        
        break;
    }
}
    
    
return pairs;

}

template<typename K, typename V>
bool BiMap<K,V>::add(K key,V value){
    /*
    adding elements in from ordered_by_keys_head_ or ordered_by_vals_head_
    if nothing is being contained, make a pointer and add in,
    if not, use key_from_value and value_from_key to inser in
    */
    
    auto a = find_key(key);
    auto b = find_value(value);
    
    Node<K,V>* new_node0;
    Node<K,V>* new_node;
    Node<K,V>* new_node1;
    int c;
    for (auto i = ordered_by_keys_head_; i != nullptr; i=i->next){
        /*
        for repeating key or value, it returns false
        */
        if (i->first ==key){
            c =100;   
        }   
    }
    if (c == 100){
        c=0;
        return false;
    }
  
    
    if (ordered_by_keys_head_ == nullptr){
        
        new_node = new Node<K,V>(key,value);
        new_node1 = new Node<K,V>(key,value);
        ordered_by_keys_head_ = new_node;
        ordered_by_vals_head_ = new_node1;
        return true;
    }

    else if( (a.second) != nullptr && (a.second)->first == key  ){
        return false;
    }
    
    else if ( (b.second) != nullptr &&  (b.second)->second == value   ){
    
        return false;
    }
    
    
    else {
        new_node = new Node<K,V>(key,value);
        new_node1 = new Node<K,V>(key,value);

if ( a.first == nullptr){ 
    
    new_node->next = ordered_by_keys_head_;
    ordered_by_keys_head_ = new_node;
    
    
    
    if (b.first == nullptr || !(b.second == nullptr) ){
        new_node1->next = ordered_by_vals_head_;
        ordered_by_vals_head_ = new_node1;
       
        return true;
    }
    
    
    else{
        (b.first)->next = new_node1;
        new_node1->next = (b.second);

        return true;
        
    }
    
}


else if ( a.first != nullptr && a.second == nullptr){
    //cout<<(a.first)->next<<endl;

    (a.first)->next = new_node;
    //cout<<a.first->next->first<<endl; 
    if (b.first == nullptr ){
        new_node1->next = ordered_by_vals_head_;
        ordered_by_vals_head_ = new_node1;
        return true;
    }
    
    else{

        
        (b.first)->next = new_node1;
        new_node1->next = (b.second);

 return true;   
    }

    
}
        (a.first)->next = new_node;
        new_node->next = (a.second);
        if  (b.first != nullptr){
        (b.first)->next = new_node1;
        new_node1->next = (b.second);
        }
        return true;
        
    }
}


template <typename K, typename V>
bool BiMap<K,V>::update(K key, V value){
    /*
    updates its value if same key exists but diff value does
    */
    Node<K,V>* new_one;
    Node<K,V>* new_two;
    
    auto a = find_key(key);
    int cnt;

   if ( (a.first != nullptr && a.first->next !=nullptr) && !( a.first->first == key  || a.first->next->first ==key )   ){
       cout<<"?????"<<endl;
       return false;
   }
   
   if (a.first !=nullptr && a.first->next == nullptr && a.first->first !=key){
    return false;
       
   }
   
    for (auto i = ordered_by_keys_head_; i != nullptr; i = i->next){
        if(i->first == key ){
            if (i->second != value){
                
                i->second = value;    
                }
            else{
                return false;
            }
            }
    }
    
    for (auto i = ordered_by_vals_head_; i != nullptr; i = i->next){  
        if (i->first == key){
            if (i->second != value){
                i->second = value;
                
            }
        }
    }
            
    remove_key(key);
    add(key,value);
    return true;

}




template <typename K, typename V>
V BiMap<K,V>::remove_key(K key){
    /*
    removing key from the element
    */
    auto a = find_key(key);
    int value;
    
    Node<K,V>* aaa; 
    for (auto i = ordered_by_keys_head_; i != nullptr; i = i->next){
        if(i->first == key && i->next != nullptr ){

            value = i->second; 
            if ( a.first == nullptr && i->next != nullptr ){
                aaa = i->next;
                delete ordered_by_keys_head_;
                ordered_by_keys_head_ = aaa;

            }
            
            else if (a.first != nullptr && i->next != nullptr){

                
                aaa = i->next;
                delete i;
                (a.first) ->next =  aaa;
                
            }
            }
            
        else if ( i->first == key && i->next == nullptr ) {
            value = i->second; 
            delete i;
            a.first->next =nullptr;
         
        }    

    }
    
    auto b = find_value (value);
    
    for (auto i = ordered_by_vals_head_; i != nullptr; i = i->next){

        if(i->second == value && i->next != nullptr ){    
            
            if ( b.first == nullptr && i->next != nullptr ){
                aaa = i->next;
                delete ordered_by_vals_head_;
                
                ordered_by_vals_head_ = aaa;
                return value;
      
            }
            
            else if (b.first != nullptr && i->next != nullptr){
   
                
                aaa = i->next;
               
                delete i;
                (b.first) ->next =  aaa;
                return value;
            }
            }
            
        else if ( i->first == key && i->next == nullptr ) {
            delete i;
            
            b.first->next =nullptr;
             
             return value;
        }
        }
        
        return 0;
} 

template <typename K, typename V>
K BiMap<K,V>::remove_val(V value){
        /*
    removing value from the element
    */
    
    auto b = find_value(value);
    string key;
    
    Node<K,V>* aaa; 
    for (auto i = ordered_by_vals_head_; i != nullptr; i = i->next){
        
        if(i->second == value && i->next != nullptr ){
           
            key = i->first;
            
            if ( b.first == nullptr && i->next != nullptr ){
                aaa = i->next;
                
                delete ordered_by_vals_head_;
                
                ordered_by_vals_head_ = aaa;
                
            }
            
            else if (b.first != nullptr && i->next != nullptr){

                aaa = i->next;
                delete i;
                (b.first) ->next =  aaa;
                
            }
            }
            
        else if ( i->second == value && i->next == nullptr ) {

            key = i->first;
            delete i;
            b.first->next =nullptr;
            
             
        } 
    }
        
    auto a = find_key (key);
    for (auto i = ordered_by_keys_head_; i != nullptr; i = i->next){
        if(i->first == key && i->next != nullptr ){

            value = i->second; 
            if ( a.first == nullptr && i->next != nullptr ){
                aaa = i->next;
         
                delete ordered_by_keys_head_;
                
                ordered_by_keys_head_ = aaa;
                //cout<<"what is this2222:  "<<aaa->first<<endl;
                return key;
            }
            
            else if (a.first != nullptr && i->next != nullptr){
         
                
                aaa = i->next;
                delete i;
                (a.first) ->next =  aaa;
                return key;
            }
            }
            
        else if ( i->first == key && i->next == nullptr ) {
            value = i->second; 
            delete i;
            a.first->next =nullptr;
            return key;
             
        }    
            
            
    }
 return key;   
}
    
template <typename K, typename V>
int BiMap<K,V>::compare(BiMap& bm){
    /*
    comparing two BiMap elements using first element key, to put out each 1,0, or -1
    */
    size_t a = this->size();
    size_t b = bm.size();
    size_t c;
    c = (a<b) ? a:b;
  
    Node<K,V> * aa;
    Node<K,V> * bb;
    aa = ordered_by_keys_head_;
    bb = bm.ordered_by_keys_head_;
    for (auto i= 0; i !=c ; i++){
        if ( aa->first > bb->first){
            return 1;
        }
            
        else if (aa->first < bb->first){
            return -1;
        }    
        else if (i == (c-1)  ){
    
            
            if ( a>b){
                return 1;
            }
            else if (a<b){
                return -1;
            }
        else{
        
            return 0;
        }
        }

        aa = aa->next;
        bb = bb->next;
    }
}


template <typename K, typename V>
BiMap<K,V> BiMap<K,V>::merge (BiMap& bm){
    /*
    merge, or put together two BiMAP list
    */
    BiMap<K,V> bm_;
    cout<<(*this)<<endl;
    for (auto i = ordered_by_keys_head_; i != nullptr; i = i->next){
            bm_.add(i->first,i->second);        
    }

    for (auto i = bm.ordered_by_keys_head_; i != nullptr; i = i->next){
            bm_.add(i->first,i->second);       
    }
    return bm_;
}

