
#ifndef AOCUTILS_H
#define AOCUTILS_H

#include <sstream>
#include <string>
#include <vector>
using namespace std;

inline vector<string> split_line(string s, string sep) {
  vector<string> ret;
  int pos = 0;
  string token;
  stringstream s_read = stringstream(s);
  while (s_read >> token) {
    ret.push_back(token);
  }

  return ret;
}

template <class T> inline ostream &operator<<(ostream &os, vector<T> vec) {
  for (T it : vec) {
    os << it << " ";
  }
  return os;
}

#endif
