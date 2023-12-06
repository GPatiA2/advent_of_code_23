#include "aocutils.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

using formas = long long int;

formas calcular_formas(long int time, long int record) {

  double tb1 = (time + sqrt(time * time - 4 * record)) / 2.0;
  double tb2 = (time - sqrt(time * time - 4 * record)) / 2.0;

  if (tb1 == floor(tb1)) {
    tb1 -= 1;
  }

  return floor(tb1) - floor(tb2);
  ;
}

int main(int argc, char *argv[]) {

  string file_name = argv[1];
  ifstream file;
  file.open(file_name);

  string line;
  string time_str = "";
  long int time;
  string record_str = "";
  long int record;

  getline(file, line);
  vector<string> split = split_line(line, " ");
  for (int i = 1; i < split.size(); i++) {
    time_str.append(split[i]);
  }
  cout << endl;

  getline(file, line);
  split = split_line(line, " ");
  for (int i = 1; i < split.size(); i++) {
    record_str.append(split[i]);
  }

  time = stol(time_str);
  record = stol(record_str);

  cout << " TIME " << time << endl;
  cout << " RECORD " << record << endl;

  formas prod = 1;
  prod *= calcular_formas(time, record);

  cout << "PROD = " << prod << endl;
  return 0;
}
