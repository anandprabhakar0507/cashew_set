#include "cashew_set.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
using namespace cashew;
using namespace std;

using intSet = cashew_set<int32_t>;

void testNodeAlignment() {
  auto p = make_unique<CashewSetNode<int,CashewSetTraits<int>>[]>(10);
  assert((ptrdiff_t(p.get()) & (CashewSetTraits<int>::cache_line_nbytes-1))
      == 0);
}

void testSmallInserts() {
  intSet s;
  // Check if it's empty.
  assert(s.empty());
  assert(s.count(1)==0);

  // Start running.
  for(int i=1;i<=100;++i) {
    assert(s.insert(i));
    assert(!s.empty());
    assert(s.count(i)==1);
    assert(s.count(i+1)==0);
    assert(s.size()==i);
  }

  // Insert duplicates.
  assert(!s.insert(1));
  assert(!s.insert(10));
  assert(!s.insert(100));
}

void testRandomInserts() {
  vector<int> v(100000);
  for(int i=0;i<v.size();++i) v[i]=i;
  random_shuffle(v.begin(),v.end());

  intSet s;
  for(int x:v) {
    assert(s.count(x)==0);
    assert(s.insert(x));
    assert(s.count(x)==1);
  }
  reverse(v.begin(),v.end());
  for(int x:v) assert(s.count(x)==1);
  assert(s.count(200000)==0);
}

int main() {
  testNodeAlignment();
  testSmallInserts();
}