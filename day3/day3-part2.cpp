#include <cctype>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct coords {
  int x;
  int y;
};

class Matrix {

public:
  Matrix(int r, int c) {
    rows = r;
    cols = c;

    scheme = new char *[rows];
    visited = new bool *[rows];
    for (int i = 0; i < rows; i++) {
      scheme[i] = new char[cols];
      visited[i] = new bool[cols];
    }
  }

  vector<string> numbers_adj_to_simbol(const coords &c) {
    vector<string> str_numbers;
    vector<coords> ady_to_c = get_adjacent(c);
    for (coords c2 : ady_to_c) {
      if (isdigit(scheme[c2.x][c2.y])) {
        string number = find_number(c2);
        str_numbers.push_back(number);
      }
    }
    return str_numbers;
  }

  void store(char c, int r, int col) {
    scheme[r][col] = c;
    visited[r][col] = false;
  }

  char at(coords c) { return scheme[c.x][c.y]; }

private:
  char **scheme;
  bool **visited;

  int rows;
  int cols;

  int adyX[3] = {1, 0, -1};
  int adyY[3] = {1, 0, -1};

  bool in_bounds(const coords &c) {
    bool x_bounds = c.x >= 0 && c.x < this->rows;
    bool y_bounds = c.y >= 0 && c.y < this->cols;
    return x_bounds && y_bounds;
  }

  vector<coords> get_adjacent(const coords &c) {

    vector<coords> adj;
    visited[c.x][c.y] = true;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        coords c2;
        c2.x = c.x + adyX[i];
        c2.y = c.y + adyY[j];
        if (in_bounds(c2) && !visited[c2.x][c2.y]) {
          adj.push_back(c2);
        }
      }
    }

    return adj;
  }

  string find_number(const coords &c) {
    deque<char> number;
    if (visited[c.x][c.y]) {
      return "0";
    }
    coords c2;
    c2.x = c.x;
    c2.y = c.y;
    visited[c2.x][c2.y] = true;
    number.push_back(scheme[c2.x][c2.y]);
    c2.y += 1;
    while (in_bounds(c2) && isdigit(scheme[c2.x][c2.y]) &&
           !visited[c2.x][c2.y]) {
      number.push_back(scheme[c2.x][c2.y]);
      visited[c2.x][c2.y] = true;
      c2.y += 1;
    }
    c2.x = c.x;
    c2.y = c.y;
    c2.y -= 1;
    while (in_bounds(c2) && isdigit(scheme[c2.x][c2.y]) &&
           !visited[c2.x][c2.y]) {
      number.push_front(scheme[c2.x][c2.y]);
      visited[c2.x][c2.y] = true;
      c2.y -= 1;
    }

    string n_ret = "";
    while (!number.empty()) {
      n_ret += number.front();
      number.pop_front();
    }
    return n_ret;
  }
};

int main(int argc, char *argv[]) {

  string file_name = argv[1];

  ifstream file;
  file.open(file_name);

  vector<string> lines;
  string l;
  int cols = 0;
  int rows = 0;

  while (getline(file, l)) {
    cols = l.length();
    lines.push_back(l);
    rows += 1;
  }

  vector<coords> symb_coords;
  Matrix m(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.store(lines[i][j], i, j);
      if (!isdigit(lines[i][j]) && lines[i][j] != '.') {
        coords sc;
        sc.x = i;
        sc.y = j;
        symb_coords.push_back(sc);
      }
    }
  }

  int sum = 0;
  for (coords co : symb_coords) {
    cout << "FOR COORDS " << co.x << " " << co.y << " CONTAINING " << m.at(co)
         << endl;
    vector<string> numbers = m.numbers_adj_to_simbol(co);
    for (string s : numbers) {
      cout << s << " ";
      sum += stoi(s);
    }
    cout << endl;
  }

  cout << "SUM = " << sum << endl;
}
