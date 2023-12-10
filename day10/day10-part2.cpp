#include "aocutils.h"
#include "matrix.h"
#include <fstream>
#include <iostream>
#include <set>
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

vector<long int> inside_h(const vector<string> &lines_read,
                          const set<long int> &full_path,
                          const Matrix<long int> &graph) {
  int inside = 0;
  int outside = 0;
  int v_borders_crossed = 0;
  vector<long int> inside_set;

  for (int i = 0; i < lines_read.size(); i++) {
    v_borders_crossed = 0;
    for (int j = 0; j < lines_read[0].size(); j++) {
      char at_pos = lines_read[i][j];
      long int ar_idx = graph.to_arr_pos(i, j);
      bool in_path = (full_path.find(ar_idx) != full_path.end());
      if ((at_pos == '7' || at_pos == 'F' || at_pos == '|') && in_path) {
        v_borders_crossed += 1;
      } else {
        if (!in_path) {
          if (v_borders_crossed % 2 == 1) {
            inside_set.push_back(ar_idx);
          } else {
            outside += 1;
          }
        }
      }
    }
  }

  return inside_set;
}
char guess_S(char c1, char c2) {
  if (c1 == '-' && c2 == 'F') {
    return 'J';
  } else if (c1 == 'F' && c2 == '-') {
    return 'J';
  }
  return '.';
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
  int Sx;
  int Sy;
  for (long int i = 0; i < lines_read.size(); i++) {
    for (long int j = 0; j < lines_read[0].size(); j++) {
      long int idx = graph.to_arr_pos(i, j);
      auto coords_adj = calculate_adjacent(lines_read[i][j], i, j, graph);
      adj[idx][0] = coords_adj.first;
      adj[idx][1] = coords_adj.second;
      if (lines_read[i][j] == 'S') {
        Sidx = idx;
        Sx = i;
        Sy = j;
      }
    }
  }

  vector<long int> prev;
  vector<long int> starting;
  vector<long int> nexts;
  vector<long int> steps;
  vector<vector<long int>> path;

  for (int i = 0; i < adj.get_rows(); i++) {
    if (adj[i][0] == Sidx || adj[i][1] == Sidx) {
      starting.push_back(i);
      prev.push_back(Sidx);
      steps.push_back(1);
      nexts.push_back(0);
      vector<long int> p;
      path.push_back(p);
    }
  }

  cout << starting << endl;

  Coords Spos = graph.from_arr_pos(Sidx);
  Coords ady1 = graph.from_arr_pos(starting[0]);
  Coords ady2 = graph.from_arr_pos(starting[1]);
  char c1 = lines_read[ady1.x][ady1.y];
  char c2 = lines_read[ady2.x][ady2.y];
  cout << " SCOORDS = " << Spos << lines_read[Spos.x][Spos.y] << endl;
  cout << " ADY1 = " << ady1 << " " << lines_read[ady1.x][ady1.y] << endl;
  cout << " ADY2 = " << ady2 << " " << lines_read[ady2.x][ady2.y] << endl;

  char S_g = 'J';
  // char S_g = 'F';

  bool reached = false;
  int total_steps;
  set<long int> full_path;
  vector<long int> full_path_vec;
  full_path_vec.push_back(Sidx);
  while (!reached) {
    for (int i = 0; i < starting.size(); i++) {
      nexts[i] = get_adj(prev[i], starting[i], adj);
      prev[i] = starting[i];
      path[i].push_back(starting[i]);
      starting[i] = nexts[i];
      steps[i] += 1;
    }

    auto ps = two_met(starting);
    reached = ps.first != -1 && ps.second != -1;
    if (reached) {
      total_steps = steps[ps.first];
      for (long int elem : path[ps.first]) {
        full_path.insert(elem);
        full_path_vec.push_back(elem);
      }
      for (long int elem : path[ps.second]) {
        full_path.insert(elem);
        full_path_vec.push_back(elem);
      }
      full_path.insert(nexts[ps.first]);
      full_path_vec.push_back(nexts[ps.first]);
      full_path.insert(Sidx);
    }
  }

  cout << "TOTAL STEPS = " << total_steps << endl;
  lines_read[Spos.x][Spos.y] = S_g;
  vector<long int> i_h = inside_h(lines_read, full_path, graph);

  int inside = i_h.size();

  cout << "INSIDE = " << inside << endl;
}
