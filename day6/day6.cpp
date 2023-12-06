#include "aocutils.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

using formas = long int;

formas calcular_formas(int time, int record) {

  double disc = sqrt(time * time - 4 * record);
  double tb1 = (time + disc) / 2;
  double tb2 = (time - disc) / 2;

  int b1 = floor(tb1);
  int b2 = ceil(tb2);

  cout << "B1 = " << b1 << endl;
  cout << "B2 = " << b2 << endl;

  return b1 - b2;
}

int main(int argc, char *argv[]) {

  string file_name = argv[1];
  ifstream file;
  file.open(file_name);

  vector<int> times;
  vector<int> records;

  string line;

  getline(file, line);
  vector<string> split = split_line(line, " ");
  for (int i = 1; i < split.size(); i++) {
    times.push_back(stoi(split[i]));
  }
  cout << endl;

  getline(file, line);
  split = split_line(line, " ");
  for (int i = 1; i < split.size(); i++) {
    records.push_back(stoi(split[i]));
  }

  cout << times << endl;
  cout << records << endl;

  formas prod = 1;
  for (int i = 0; i < times.size(); i++) {
    formas ci = calcular_formas(times[i], records[i]);
    cout << " PARA LA CARRERA " << i << " HAY " << ci << " FORMAS " << endl;
    prod *= ci;
  }

  cout << "PROD = " << prod << endl;
  return 0;
}
