#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Range {

public:
  Range() {}

  Range(long long int s, long long int f, long long int l) {
    start = s;
    length = l;
    fin = f;
  }

  bool in_range(long long int number) {
    return number >= start && number <= start + length - 1;
  }

  long long int operator[](long long int number) {
    long long int dif = number - start;
    long long int n_pos = fin + dif;
    return n_pos;
  }

  long long int get_start() const { return start; }
  long long int get_length() const { return length; }
  long long int get_end() const { return fin; }

private:
  long long int start;
  long long int length;
  long long int fin;
};

class RangeMap {

public:
  RangeMap() {}

  RangeMap(const vector<Range> &v) { ranges = v; }

  long long int operator[](long long int number) {

    bool found = false;

    long long int i = 0;
    while (i < ranges.size() && !found) {

      found = ranges[i].in_range(number);
      if (!found) {
        cout << number << " NOT IN RANGE " << ranges[i].get_end() << " "
             << ranges[i].get_start() << " " << ranges[i].get_length() << endl;
      } else {

        cout << number << " IN RANGE " << ranges[i].get_end() << " "
             << ranges[i].get_start() << " " << ranges[i].get_length() << endl;
      }
      i++;
    }

    long long int ret;
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

ostream &operator<<(ostream &os, const RangeMap &r) {
  for (Range range : r.get_ranges()) {
    os << range.get_end() << " " << range.get_start() << " "
       << range.get_length() << endl;
  }
  cout << endl;
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

long long int get_min_place(long long int seed, vector<RangeMap> &r) {
  long long int place = seed;

  for (long long int i = 0; i < r.size(); i++) {
    place = r[i][place];
  }
  return place;
}

int main(int argc, char *argv[]) {

  string file_name;
  ifstream file;

  file_name = argv[1];
  file.open(file_name);

  string line;
  string trash;
  stringstream l_read;

  vector<long long int> seeds;
  getline(file, line);
  l_read = stringstream(line);
  l_read >> trash;

  long long int seed_num;
  while (l_read >> seed_num) {

    seeds.push_back(seed_num);
  }

  vector<RangeMap> ranges;
  long long int line_count = 0;
  RangeMap *r = new RangeMap();
  while (getline(file, line)) {
    if (line.length() == 0 && line_count != 0) {
      ranges.push_back(*r);
    } else if (isalpha(line[0])) {
      r = new RangeMap();
    } else {
      l_read = stringstream(line);
      long long int start = 0;
      long long int end = 0;
      long long int len = 0;
      l_read >> end;
      l_read >> start;
      l_read >> len;
      Range rang(start, end, len);
      r->append(rang);
    }
    line_count += 1;
  }

  ranges.push_back(*r);

  cout << "READ " << ranges.size() << " MAPS" << endl;
  for (RangeMap r : ranges) {
    cout << r << endl;
  }

  cout << endl;
  long long int min_place = get_min_place(seeds[0], ranges);
  for (long long int i = 1; i < seeds.size(); i++) {
    long long int p = get_min_place(seeds[i], ranges);
    min_place = min(p, min_place);
  }

  cout << "MIN POS " << min_place << endl;
}
