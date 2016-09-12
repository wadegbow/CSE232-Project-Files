#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <vector>
using std::vector;
#include <map>
using std::map;
#include <algorithm>
using std::copy;
#include <utility>
using std::pair; using std::initializer_list;
#include <exception>
using std::range_error;
#include <iostream>
using std::ostream; using std::cout;
#include <iterator>
using std::ostream_iterator;

class SparseVector {
private:
  map<long,long> m_;
  long sz_;
  long def_;

public:
  SparseVector(long);
  SparseVector(long, long);
  SparseVector(long, long, initializer_list<pair<long,long>>);

  long operator[] (long);
  void set(long, long);
  long size();
  long element_count();

  friend SparseVector operator+(const SparseVector &, const SparseVector &);
  friend SparseVector operator+(const SparseVector &, const long);
  friend SparseVector operator+(const long, const SparseVector &);
  friend long operator*(const SparseVector &, const SparseVector &);
  friend SparseVector operator*(const SparseVector &, const long);
  friend SparseVector operator*(const long, const SparseVector &);
  friend ostream &operator<<(ostream&, const SparseVector &);
};

#endif
