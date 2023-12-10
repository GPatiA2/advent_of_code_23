#include "aocutils.h"
#include "matrix.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

using Coords = Matrix<long int>::Coords;

pair<long int, long int> calculate_adjacent(char c, long int i, long int j,
                                            const Matrix<long int> &g) {
  Coords c1(-1, -1);
  Coords c2(-1, -1);
  pair<long int, long int> ret(-1, -1);

  if (c == '|') {
    c1.x = i - 1;
    c1.y = j;

    c2.x = i + 1;
    c2.y = j;
  } else if (c == '-') {
    c1.x = i;
    c1.y = j + 1;

    c2.x = i;
    c2.y = j - 1;
  } else if (c == 'L') {
    c1.x = i - 1;
    c1.y = j;

    c2.x = i;
    c2.y = j + 1;
  } else if (c == 'J') {
    c1.x = i - 1;
    c1.y = j;

    c2.x = i;
    c2.y = j - 1;
  } else if (c == '7') {
    c1.x = i + 1;
    c1.y = j;

    c2.x = i;
    c2.y = j - 1;

  } else if (c == 'F') {
    c1.x = i + 1;
    c1.y = j;

    c2.x = i;
    c2.y = j + 1;
  }

  if (g.in_bounds(c1)) {
    ret.first = g.to_arr_pos(c1);
  }
  if (g.in_bounds(c2)) {
    ret.second = g.to_arr_pos(c2);
  }

  return ret;
}

long int get_adj(long int prev, long int idx, const Matrix<long int> &m) {
  if (m[idx][0] == prev) {
    return m[idx][1];
  } else {
    return m[idx][0];
  }
}

bool same_to(long int elem1, long int elem2) { return elem1 == elem2; }

pair<int, int> two_met(const vector<long int> &v) {
  pair<int, int> p(-1, -1);
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (v[i] == v[j]) {
        p.first = i;
        p.second = j;
      }
    }
  }
  return p;
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
  Matrix<long int> graph(lines_read.size(), lines_read[0].size(), false);

  Matrix<long int> adj(lines_read.size() * lines_read[0].size(), 2);

  long int Sidx;
  for (long int i = 0; i < lines_read.size(); i++) {
    for (long int j = 0; j < lines_read[0].size(); j++) {
      long int idx = graph.to_arr_pos(i, j);
      auto coords_adj = calculate_adjacent(lines_read[i][j], i, j, graph);
      adj[idx][0] = coords_adj.first;
      adj[idx][1] = coords_adj.second;
      if (lines_read[i][j] == 'S') {
        Sidx = idx;
      }
    }
  }

  vector<long int> prev;
  vector<long int> starting;
  vector<long int> nexts;
  vector<long int> steps;

  for (int i = 0; i < adj.get_rows(); i++) {
    if (adj[i][0] == Sidx || adj[i][1] == Sidx) {
      starting.push_back(i);
      prev.push_back(Sidx);
      steps.push_back(1);
      nexts.push_back(0);
    }
  }

  bool reached = false;
  int total_steps;
  while (!reached) {
    for (int i = 0; i < starting.size(); i++) {
      nexts[i] = get_adj(prev[i], starting[i], adj);
      prev[i] = starting[i];
      starting[i] = nexts[i];
      steps[i] += 1;
    }

    auto ps = two_met(starting);
    reached = ps.first != -1 && ps.second != -1;
    if (reached) {
      total_steps = steps[ps.first];
      cout << steps[ps.first] << " " << steps[ps.second] << endl;
      cout << "MET AT " << starting[ps.first] << " " << starting[ps.second]
           << endl;
    }
  }

  cout << "STEPS = " << total_steps << endl;
}
