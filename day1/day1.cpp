#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char *argv[]) {

  string file = argv[1];

  ifstream rfile;
  rfile.open(file);

  string line;
  int number = 0;
  int expo = 0;
  int sum = 0;
  int i = 0;
  int last = -1;
  int first = -1;

  while (getline(rfile, line)) {
    cout << "READ LINE " << line << endl;
    expo = 0;
    number = 0;
    i = line.length() - 1;
    last = -1;
    first = -1;

    while (i >= 0) {
      if (isdigit(line[i])) {
        if (last == -1) {
          last = line[i] - '0';
        } else {
          first = line[i] - '0';
        }
      }
      i--;
    }
    if (first == -1 && last == -1) {
      number += 0;
    } else {
      number += last;
      if (first == -1) {
        first = last;
      }
      number += first * pow(10, 1);
      cout << "FIRST = " << first << " LAST = " << last << endl;
      sum += number;
    }
  }
  cout << "NUMBER = " << sum << endl;
}
