#ifndef CIRCLIST_H
#define CIRCLIST_H

#include <vector>
using namespace std;

template <class T> class Circlist {

public:
  Circlist() { act_idx = -1; };

  T next() {
    act_idx = (act_idx + 1) % list.size();
    return list[act_idx];
  }

  T prev() {
    act_idx = act_idx - 1;
    if (act_idx < 0) {
      act_idx = list.size() - 1;
    }
    return list[act_idx];
  }

  void push_back(const T &elem) { list.push_back(elem); }

  void remove(int idx) { list.erase(idx); }

  int size() const { return list.size(); }

  void set_idx(int i) {
    if (i >= list.size()) {
      i = i % list.size();
    } else if (i < 0) {
      i = list.size() + i;
    }
    act_idx = i;
  }

  void reset() { act_idx = -1; }

private:
  vector<T> list;
  int act_idx;
};

#endif
