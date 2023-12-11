#include "../utils/aocutils.h"
#include "../utils/matrix.h"
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

using Coords = Matrix<char>::Coords;

long long int calculate(const Matrix<char> &space, const Coords &start,
                        const Coords &end, const set<long long int> &rng,
                        const set<long long int> &cng) {

  long long int dist = 0;
  long long int x_diff = 0;
  long long int y_diff = 0;

  x_diff = start.x - end.x;
  y_diff = start.y - end.y;

  cout << "FOR COORDS " << start << " || " << end << endl;
  cout << "   XDIFF = " << x_diff << " YDIFF = " << y_diff;

  long long int x_start = min(start.x, end.x);
  long long int x_end = max(start.x, end.x);
  long long int y_start = min(start.y, end.y);
  long long int y_end = max(start.y, end.y);

  for (long long int i = x_start; i < x_end; i++) {
    if (rng.find(i) != rng.end()) {
      if (x_diff < 0) {
        x_diff -= 999999;
      } else {
        x_diff += 999999;
      }
    }
  }

  for (long long int j = y_start; j < y_end; j++) {
    if (cng.find(j) != cng.end()) {
      if (y_diff < 0) {
        y_diff -= 999999;
      } else {
        y_diff += 999999;
      }
    }
  }
  cout << "   THEN XDIFF = " << x_diff << " "
       << " YDIFF = " << y_diff << endl;
  dist = abs(x_diff) + abs(y_diff);
  cout << " THEN DIST = " << dist << endl;
  return dist;
}

int main(int argc, char *argv[]) {

  string file_name = argv[1];
  ifstream file;
  file.open(file_name);

  string line;
  vector<string> lines_read;
  while (getline(file, line)) {
    lines_read.push_back(line);
  }

  Matrix<char> space(lines_read.size(), lines_read[0].size(), '.');
  vector<Coords> galaxies;
  set<long long int> rows_no_galaxy;
  set<long long int> cols_no_galaxy;
  long long int galaxy_count = 0;
  for (long long int i = 0; i < lines_read.size(); i++) {
    galaxy_count = 0;
    for (long long int j = 0; j < lines_read[0].size(); j++) {
      Coords c(i, j);
      if (lines_read[i][j] == '#') {
        galaxies.push_back(c);
        galaxy_count += 1;
      }
      space[c] = lines_read[i][j];
    }
    if (galaxy_count == 0) {
      rows_no_galaxy.insert(i);
    }
  }

  for (long long int j = 0; j < lines_read[0].size(); j++) {
    galaxy_count = 0;
    for (long long int i = 0; i < lines_read.size(); i++) {
      if (lines_read[i][j] == '#') {
        galaxy_count += 1;
      }
    }
    if (galaxy_count == 0) {
      cols_no_galaxy.insert(j);
    }
  }

  long long int total_length = 0;
  for (long long int i = 0; i < galaxies.size(); i++) {
    for (long long int j = i + 1; j < galaxies.size(); j++) {
      total_length += calculate(space, galaxies[i], galaxies[j], rows_no_galaxy,
                                cols_no_galaxy);
    }
  }

  cout << "TOTAL SUM = " << total_length << endl;
}
