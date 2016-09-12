/*
    CSE 232 - Wade Bowers
*/

#ifndef PROJECT11
#define PROJECT11

#include<iostream>
using std::ostream; using std::endl; using std::cout;
#include<algorithm>
using std::copy; using std::swap;
#include<stdexcept>
using std::range_error;

//
// Dict Pair
//
template<typename K, typename V>
struct DictPair{
public:
    K key_;
    V value_;
    DictPair* next_;
    DictPair* previous_;

    DictPair(); //DictPair default constructor
    DictPair(K k, V v) : key_(k), value_(v) {}; //DictPair constructor
};

template<typename K, typename V>
ostream& operator<<(ostream& out, const DictPair<K,V>& d){
    out << "{" << d.key_ << "," << d.value_ << "}";

    return out;
}


//
// Dict
//

template<typename K, typename V>
class Dict{
private:
    DictPair<K,V>* head_;
    DictPair<K,V>* tail_;
    size_t sz_;
    DictPair<K,V>* exist_ptr_;

public:
    Dict() : head_(nullptr), tail_(nullptr), sz_(0) {}; //default constructor
    Dict(K key, V val);
    Dict(const Dict& d);
    Dict& operator=(Dict d);
    ~Dict();
    void append (K key, V value);
    void append (DictPair<K,V> &dp);
    bool exists(K key);
    V get_value(K key);
    void erase(K key);
    size_t size();
    friend ostream& operator<<(ostream& out, const Dict& d){
        DictPair<K,V> *ptr;
        for(ptr = d.head_; ptr != nullptr; ptr = ptr->next_)
            out << *ptr << ",";
        return out;
    };
};

//constructor creates a Dict with DictPair(K,V)
template<typename K, typename V>
Dict<K,V>::Dict(K key, V value) {
    DictPair<K,V>* ptr = new DictPair<K,V>(key, value);
    head_ = ptr;
    tail_ = ptr;
    sz_ = 1;
}

//copy constructor
template<typename K, typename V>
Dict<K,V>::Dict(const Dict<K,V>& d){
    //check that the d.head_ has a DictPair
    if (d.head_ == nullptr){
    	head_ = nullptr;
    	tail_ = nullptr;
    } else {
    	head_ = new DictPair<K,V>(d.head_->key_, d.head_->value_);
    	tail_ = head_;
    	DictPair<K,V>* dp_ptr = d.head_->next_;
    	DictPair<K,V>* new_dictpair;
        //iterate through dp_ptr, appending each node
    	while (dp_ptr != nullptr){
            new_dictpair = new DictPair<K,V>(dp_ptr->key_, dp_ptr->value_);
    	    tail_->next_ = new_dictpair;
    	    new_dictpair->previous_ = tail_;
    	    dp_ptr = dp_ptr->next_;
    	    tail_ = new_dictpair;
    	}

    }
    //copy the size
    sz_ = d.sz_;
}

//operator= override, returns new Dict
template<typename K, typename V>
Dict<K,V>& Dict<K,V>::operator=(Dict<K,V> d){
    sz_ = d.sz_;
    exist_ptr_ = d.exist_ptr_;
    swap(head_, d.head_);
    swap(tail_, d.tail_);

    return *this;
}

//destructor
template<typename K, typename V>
Dict<K,V>::~Dict(){
    DictPair<K,V>* to_del = head_;
    //iterate through list, deleting each node
    while (to_del != nullptr){
    	head_ = head_->next_;
    	delete to_del;
    	to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

//method that returns true if a key exists and sets exist_ptr_
template<typename K, typename V>
bool Dict<K,V>::exists(K key){
    DictPair<K,V> *ptr;
    //check that the head_ has a value
    if (head_ != nullptr) {
        //iterate through list, looking for the key
        for(ptr = head_; ptr != nullptr; ptr = ptr->next_) {
            if (ptr->key_ == key) {
                exist_ptr_ = ptr;
                return true;
            }
        }
    }

    return false;
}

//method that appends a DictPair to the Dict
template<typename K, typename V>
void Dict<K,V>::append(DictPair<K,V> &dp){
    //check that the tail has a value
    if (tail_ != nullptr){
        //add the DictPair
    	tail_->next_ = &dp;
        //relink the list
    	dp.previous_ = tail_;
    	dp.next_ = nullptr;
        //set the tail
    	tail_ = &dp;
    }
    else {
    	head_=&dp;
    	tail_=&dp;
    }

    sz_++;
}

//method that creates a new DictPair with key and value
template<typename K, typename V>
void Dict<K,V>::append(K key, V value){
    bool k_exists = this->exists(key);

    //check if the key exists
    if (k_exists) {
        exist_ptr_->value_ = value;
     } else {
        //create a new DictPair and pass it through append(DictPair)
        DictPair<K,V>* dp = new DictPair<K,V>(key, value);
        append(*dp);
    }
}

//method that returns the value of the node with K key
template<typename K, typename V>
V Dict<K,V>::get_value(K key){
    bool k_exists = this->exists(key);

    //check if the key exists
    if (k_exists) {
        //create a pointer for deletion
        DictPair<K,V>* to_mov = exist_ptr_;

        //handle the move differently depending on where the node is located
        if (to_mov == head_) {
            return head_->value_;
        } else if (to_mov->next_ == nullptr) {
            to_mov->next_ = head_;
            to_mov->previous_->next_ = nullptr;
            tail_ = to_mov->previous_;
            to_mov->previous_ = nullptr;
            head_->previous_ = to_mov;
            head_ = to_mov;
        } else {
            to_mov->next_->previous_ = to_mov->previous_;
            to_mov->previous_->next_ = to_mov->next_;
            to_mov->next_ = head_;
            to_mov->previous_ = nullptr;
            head_->previous_ = to_mov;
            head_ = to_mov;
        }

        return head_->value_;
    } else {
        throw range_error("invalid key");
    }
}

template<typename K, typename V>
void Dict<K,V>::erase(K key){
    bool k_exists = this->exists(key);

    //check if the key exists
    if (k_exists) {
        //create a pointer for deletion
        DictPair<K,V>* to_del = exist_ptr_;

        //handle the delete differently depending on where the node is located
        if (to_del == head_) {
            head_ = to_del->next_;
        } else if (to_del->next_ == nullptr) {
            tail_ = to_del->previous_;
            tail_->next_ = nullptr;
        } else {
            to_del->next_->previous_ = to_del->previous_;
            to_del->previous_->next_ = to_del->next_;
        }

        //delete the temp pointer
        delete to_del;
        sz_--;
    }

}

//method for returning the size, helpful for testing
template<typename K, typename V>
size_t Dict<K,V>::size(){
    return sz_;
}

#endif
