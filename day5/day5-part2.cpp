#include <cctype>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Interval {

public:
  Interval() {}
  Interval(unsigned long int init, unsigned long int last) {
    beg = init;
    fin = last;
  }

  unsigned long int get_beg() const { return beg; }
  unsigned long int get_fin() const { return fin; }

  void set_beg(unsigned int b) { beg = b; }
  void set_fin(unsigned int f) { fin = f; }

private:
  unsigned long int beg;
  unsigned long int fin;
};

class Range {

public:
  Range() {}

  Range(unsigned long int s, unsigned long int f, unsigned long int l) {
    start = s;
    length = l;
    fin = f;
  }

  bool in_range(unsigned long int number) {
    return number >= start && number <= start + length - 1;
  }

  unsigned long int operator[](unsigned long int number) {
    unsigned long int dif = number - start;
    unsigned long int n_pos = fin + dif;
    return n_pos;
  }

  unsigned long int get_start() const { return start; }
  unsigned long int get_length() const { return length; }
  unsigned long int get_end() const { return fin; }

private:
  unsigned long int start;
  unsigned long int length;
  unsigned long int fin;
};

class RangeMap {

public:
  RangeMap() {}

  RangeMap(const vector<Range> &v) { ranges = v; }

  unsigned long int operator[](unsigned long int number) {

    bool found = false;

    unsigned long int i = 0;
    while (i < ranges.size() && !found) {

      found = ranges[i].in_range(number);
      if (!found) {
        /* cout << number << " NOT IN RANGE " << ranges[i].get_end() << " "
             << ranges[i].get_start() << " " << ranges[i].get_length() << endl;
         */
      } else {

        // cout << number << " IN RANGE " << ranges[i].get_end() << " "
        //      << ranges[i].get_start() << " " << ranges[i].get_length() <<
        //      endl;
      }
      i++;
    }

    unsigned long int ret;
    if (found) {
      i -= 1;
      ret = ranges[i][number];
    } else {
      ret = number;
      // cout << " NO RANGE FOUND SO RETURNING NUMBER " << number << endl;
    }

    return ret;
  }
  void append(const Range &r) { ranges.push_back(r); }

  vector<Range> get_ranges() const { return ranges; }

private:
  vector<Range> ranges;
};

vector<Interval> split_interval(const Interval &i, const Range &r) {
  vector<Interval> parts;
  if (i.get_fin() <= r.get_start() + r.get_length() - 1) {
    parts.push_back(i);
  } else if (i.get_beg() >= r.get_start()) {
    parts.push_back({i.get_beg(), r.get_start() + r.get_length() - 1});
    parts.push_back({r.get_start() + r.get_length(), i.get_fin()});
  }

  return parts;
}

void transform(Interval &i, const Range &r) {
  i.set_beg(i.get_beg() - r.get_start() + r.get_end());
  i.set_fin(i.get_fin() - r.get_start() + r.get_end());
}

vector<Interval> operator+(const Interval &i, const Range &r) {
  vector<Interval> ret;
  vector<Interval> parts = split_interval(i, r);
  for (Interval i : parts) {
    transform(i, r);
  }

  return parts;
}

ostream &operator<<(ostream &os, const RangeMap &r) {
  for (Range range : r.get_ranges()) {
    os << range.get_end() << " " << range.get_start() << " "
       << range.get_length() << endl;
  }
  os << endl;
  return os;
}

ostream &operator<<(ostream &os, const Range &r) {
  os << r.get_end() << " " << r.get_start() << " " << r.get_length() << endl;
  return os;
}

ostream &operator<<(ostream &os, const vector<RangeMap> &ranges) {
  for (RangeMap r : ranges) {
    os << r << endl;
  }

  return os;
}

unsigned long int get_min_place(unsigned long int seed, vector<RangeMap> &r) {
  unsigned long int place = seed;

  for (unsigned long int i = 0; i < r.size(); i++) {
    place = r[i][place];
  }
  return place;
}

void print_vec(const vector<Interval> &v) {
  for (Interval i : v) {
    cout << "   " << i.get_beg() << " " << i.get_fin();
  }
}

int main(int argc, char *argv[]) {

  string file_name;
  ifstream file;

  file_name = argv[1];
  file.open(file_name);

  string line;
  string trash;
  stringstream l_read;

  getline(file, line);
  l_read = stringstream(line);
  l_read >> trash;

  vector<Interval> seed_intervals;
  vector<unsigned long int> seed_nums;
  unsigned long int r_n;
  while (l_read >> r_n) {
    seed_nums.push_back(r_n);
  }

  for (int i = 0; i < seed_nums.size(); i += 2) {
    seed_intervals.push_back(
        {seed_nums[i], seed_nums[i] + seed_nums[i + 1] - 1});
  }

  vector<RangeMap> ranges;
  unsigned long int line_count = 0;
  RangeMap *r = new RangeMap();
  while (getline(file, line)) {
    if (line.length() == 0 && line_count != 0) {
      ranges.push_back(*r);
    } else if (isalpha(line[0])) {
      r = new RangeMap();
    } else {
      l_read = stringstream(line);
      unsigned long int start = 0;
      unsigned long int end = 0;
      unsigned long int len = 0;
      l_read >> end;
      l_read >> start;
      l_read >> len;
      Range rang(start, end, len);
      r->append(rang);
    }
    line_count += 1;
  }

  ranges.push_back(*r);

  unsigned long int abs_min = 1000000000000000000;

  for (Interval i : seed_intervals) {
    for (unsigned long int j = i.get_beg(); j < i.get_fin(); j++) {
      abs_min = min(abs_min, get_min_place(j, ranges));
    }
  }

  cout << abs_min << endl;
}
