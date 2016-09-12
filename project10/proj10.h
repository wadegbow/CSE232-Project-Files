#ifndef PROJECT11
#define PROJECT11

#include<iostream>
using std::ostream; using std::endl; using std::cout;
#include<algorithm>
using std::copy;
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

    DictPair();
    DictPair(K k, V v);
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
    Dict() : head_(nullptr), tail_(nullptr), sz_(0) {}; // FIX IT here
    Dict(K key, V val); // FIX here or below
    Dict(const Dict& d);
    Dict& operator=(Dict d);
    ~Dict();
    //void append (K key, V value);
    //bool exists(K key);
    //V get_value(K key);
    //void erase(K key);
    friend ostream& operator<<(ostream& out, const Dict& d){
        DictPair<K,V> *ptr;
        for(ptr = d.head_; ptr != nullptr; ptr = ptr->next_)
            out << *ptr << ",";
        return out;
    };
};

template<typename K, typename V>
Dict<K,V>::Dict(K key, V value) {
    DictPair<T>* ptr = new DictPair<K,V>(key, value);
    head_ = ptr;
    tail_ = ptr;
}

template<typename K, typename V>
Dict<K,V>::Dict(const Dict<K,V>& d){
    if (d.head_ == nullptr){
    	head_ = nullptr;
    	tail_ = nullptr;
    }
    else{
    	head_ = new DictPair<K,V>(d.head_->key_, d.head_->value_);
    	tail_ = head_;
    	DictPair<K,V>* dp_ptr = d.head_->next_;
    	DictPair<K,V>* new_dictpair;
    	while (dp_ptr != nullptr){
            new_dictpair = new DictPair<K,V>(dp_ptr->key_, dp_ptr->value_);
    	    tail_->next_ = new_dictpair;
    	    new_dictpair->prev_ = tail_;
    	    dp_ptr = dp_ptr->next_;
    	    tail_ = new_dictpair;
    	}
    }
}

template<typename K, typename V>
Dict<K,V>& Dict<K,V>::operator=(Dict<K,V> d){
    swap(head_, d.head_);
    swap(tail_, d.tail_);
}

template<typename K, typename V>
Dict<K,V>::~Dict(){
    DictPair<K,V>* to_del = head_;
    while (to_del != nullptr){
    	head_ = head_->next_;
    	delete to_del;
    	to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
}
/*
template<typename K, typename V>
bool Dict<K,V>::exists(K key){
// FIX IT
}

template<typename K, typename V>
void Dict<K,V>::append(K key, V value){
// FIX IT
}

template<typename K, typename V>
V Dict<K,V>::get_value(K key){
// FIX IT
}

template<typename K, typename V>
void Dict<K,V>::erase(K key){
// FIX IT
}
*/

#endif
