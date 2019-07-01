#pragma once

#include <iterator>
#include <algorithm>
using namespace std;

template <typename It>
class IteratorRange {
public:
  IteratorRange(It first, It last) : first(first), last(last), size_(distance(first, last)) {
  }

  It begin() const {
    return first;
  }

  It end() const {
    return last;
  }

  size_t size() const {
	  return size_; 
  }

private:
	It first, last;
	size_t size_;
};

template <typename Container>
auto Head(Container& c, int top) {
  return IteratorRange(begin(c), next(begin(c), min<size_t>(max(top, 0), c.size() )) );
}
