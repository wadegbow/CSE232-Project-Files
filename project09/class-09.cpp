#include "class-09.h"

//constructor takes a positive long for size
SparseVector::SparseVector(long size) {
  if (size < 0)
    throw range_error("bad size");

  sz_ = size;
  def_ = 0;
}

//constructor takes a positive long for size and a long default value
SparseVector::SparseVector(long size, long default_val) {
  if (size < 0)
    throw range_error("bad size");

  sz_ = size;
  def_ = default_val;
}

//constructor takes a positive long for size and a long default value
//and an init list to set specific elements
SparseVector::SparseVector(long size, long default_val,
initializer_list<pair<long,long>> il) {
  if (size < 0)
    throw range_error("bad size");

  sz_ = size;
  def_ = default_val;

  //loop through the init list and insert values with a good index
  for (auto x : il) {
    if (x.first >= 0 && x.first <= this->size()-1) {
      //check that the value isnt a default value
      if (x.second != def_)
        m_.insert(x);

    } else {
      throw range_error("bad init list");
    }
  }
}

//operator[] override, returns the long with key of index
long SparseVector::operator[] (long index) {
  if (m_.find(index) == m_.end()) {
    //check if the index is within the size range
    if (index >= 0 && index <= this->size()-1)
      return def_;
    else
      throw range_error("bad []");

  } else {
    return m_.at(index);
  }
}

//set method sets the index of the map to val
void SparseVector::set(long index, long val) {
  if (index >= 0 && index <= this->size()-1) {
    //check that the val isn't the default
    if (val != def_)
      m_[index] = val;
      
  } else {
    throw range_error("bad set");
  }
}

//size method returns the size of the map
long SparseVector::size() {
  return sz_;
}

//element_count method returns the number of set elements
long SparseVector::element_count() {
  return m_.size();
}

//operator+ override, returns new sparsevector that is sv1+sv2
SparseVector operator+(const SparseVector& sv1, const SparseVector& sv2) {
  SparseVector new_sv(sv1.sz_), temp_sv(sv1.sz_);

  //find the sparsevector with more set elements
  //create a new_sv and temp_sv
  if (sv1.m_.size() > sv2.m_.size()) {
    new_sv = sv1;
    temp_sv = sv2;
  } else {
    new_sv = sv2;
    temp_sv = sv1;
  }

  //configure size of new vector by finding the larger size
  if (sv1.sz_ >= sv2.sz_) {
    new_sv.sz_ = sv1.sz_;
  } else {
    new_sv.sz_ = sv2.sz_;
  }

  //iterate through the new_sv and add elements in the same place
  //if there is no value in the same place, add the default
  for (auto itr = new_sv.m_.begin(); itr != new_sv.m_.end(); itr++) {
    if (temp_sv.m_.find(itr->first) != temp_sv.m_.end())
      new_sv.m_[itr->first] = itr->second + temp_sv.m_.at(itr->first);
    else
      new_sv.m_[itr->first] = itr->second + temp_sv.def_;
  }

  //define the new_sv's default value
  new_sv.def_ = new_sv.def_ + temp_sv.def_;

  return new_sv;
}

//operator+ override, returns a new sparsevector that is sv+x
SparseVector operator+(const SparseVector& sv, const long x) {
  SparseVector new_sv(sv.sz_, sv.def_+x);
  for (auto itr = sv.m_.begin(); itr != sv.m_.end(); itr++) {
    new_sv.m_[itr->first] = itr->second + x;
  }

  return new_sv;
}

//operator+ override, returns a new sparsevector that is x+sv
SparseVector operator+(const long x, const SparseVector& sv) {
  SparseVector new_sv(sv.sz_, sv.def_+x);
  for (auto itr = sv.m_.begin(); itr != sv.m_.end(); itr++) {
    new_sv.m_[itr->first] = itr->second + x;
  }

  return new_sv;
}

//operator* override, returns a long that is the dot product of sv1 and sv2
long operator*(const SparseVector& sv1, const SparseVector& sv2) {
  SparseVector new_sv(sv1.sz_), temp_sv(sv1.sz_);
  long total = 0;

  //find the larger sparsevector
  //create a new_sv and temp_sv
  if (sv1.m_.size() > sv2.m_.size()) {
    new_sv = sv1;
    temp_sv = sv2;
  } else {
    new_sv = sv2;
    temp_sv = sv1;
  }

  //iterate through the new_sv and multiply elements in the same place
  //if there is no value in the same place, multiply by the default
  for (auto itr = new_sv.m_.begin(); itr != new_sv.m_.end(); itr++) {
    if (temp_sv.m_.find(itr->first) != temp_sv.m_.end())
      new_sv.m_[itr->first] = itr->second * temp_sv.m_.at(itr->first);
    else
      new_sv.m_[itr->first] = itr->second * temp_sv.def_;

    //keep track of total
    total = total + new_sv.m_[itr->first];
  }

  //add the remaining default values
  total = total + (temp_sv.sz_ - new_sv.m_.size())*(new_sv.def_ * temp_sv.def_);

  return total;
}

//operator* override, returns a sparsevectir that is the product of sv and x
SparseVector operator*(const SparseVector& sv, const long x) {
  SparseVector new_sv(sv.sz_, sv.def_*x);
  for (auto itr = sv.m_.begin(); itr != sv.m_.end(); itr++) {
    new_sv.m_[itr->first] = itr->second * x;
  }

  return new_sv;
}

//operator* override, returns a sparsevectir that is the product of x and sv
SparseVector operator*(const long x, const SparseVector& sv) {
  SparseVector new_sv(sv.sz_, sv.def_*x);
  for (auto itr = sv.m_.begin(); itr != sv.m_.end(); itr++) {
    new_sv.m_[itr->first] = itr->second * x;
  }

  return new_sv;
}

//operator<< override, returns a printable ostream
ostream &operator<<(ostream& out, const SparseVector& sv) {
  out << "{";

  //if the size of the sv is greater than 0, print the vector
  if (sv.m_.size() > 0)
    for (auto itr = sv.m_.begin(); itr != sv.m_.end(); itr++) {
      out << "{" << itr->first << ":" << itr->second << "},";
    }
  else
    out << "no set values."; //is printed when the sv is only default values

  out << "\b" << "}";
  return out;
}
