#include "aocutils.h"
#include <fstream>
#include <iostream>

using namespace std;

bool all(const vector<int> &vec, bool (*func)(int)) {
  bool ret = true;
  for (int i : vec) {
    ret &= func(i);
  }
  return ret;
}

bool equals_0(int i) { return i == 0; }

int calculate(const vector<int> &numbers) {
  cout << "CALCULATING VECTOR " << numbers << endl;
  vector<int> diffs;
  for (int i = 0; i < numbers.size() - 1; i++) {
    diffs.push_back(numbers[i + 1] - numbers[i]);
  }
  if (all(diffs, &equals_0)) {
    return numbers[numbers.size() - 1];
  }
  return numbers[numbers.size() - 1] + calculate(diffs);
}

int solve(const vector<int> &numbers) {
  int res = calculate(numbers);
  return res;
}

int main(int argc, char *argv[]) {

  string file_name = argv[1];
  ifstream file;

  file.open(file_name);

  string line;
  int sum_nexts = 0;
  while (getline(file, line)) {
    vector<int> numbers;
    for (string s : split_line(line, " ")) {
      numbers.push_back(stoi(s));
    }
    int solution = solve(numbers);
    cout << "Partial sol = " << solution << endl;
    sum_nexts += solution;
  }
  cout << "Solution = " << sum_nexts << endl;
}
