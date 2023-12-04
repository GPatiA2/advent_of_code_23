#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
using namespace std;

int get_matches(const vector<int> &winning_numbers,
                const vector<int> &card_numbers) {
  int matches = 0;
  int i = 0;
  int j = 0;
  while (i < winning_numbers.size() && j < card_numbers.size()) {
    if (winning_numbers[i] == card_numbers[j]) {
      i += 1;
      j += 1;
      matches += 1;
    } else if (winning_numbers[i] < card_numbers[j]) {
      i += 1;
    } else if (card_numbers[j] < winning_numbers[i]) {
      j += 1;
    }
  }
  return matches;
}

int main(int argc, char *argv[]) {

  ifstream file;
  string file_name;
  string card_line;

  vector<vector<int>> winning_list;
  vector<vector<int>> card_list;
  vector<int> units;

  string trash;
  stringstream reading_line;

  int read_number;

  int points = 0;
  int card_points = -1;

  file_name = argv[1];
  file.open(file_name);
  while (getline(file, card_line)) {

    vector<int> winning_numbers;
    vector<int> card_numbers;
    card_points = -1;
    reading_line = stringstream(card_line);
    reading_line >> trash;
    reading_line >> trash;

    reading_line >> trash;
    while (trash != "|") {
      read_number = stoi(trash);
      winning_numbers.push_back(read_number);
      reading_line >> trash;
    }
    while (reading_line >> read_number) {
      card_numbers.push_back(read_number);
    }

    sort(winning_numbers.begin(), winning_numbers.end());
    sort(card_numbers.begin(), card_numbers.end());
    winning_list.push_back(winning_numbers);
    card_list.push_back(card_numbers);
    units.push_back(1);
  }

  for (int i = 0; i < winning_list.size(); i++) {
    int matches = get_matches(winning_list[i], card_list[i]);
    for (int j = i + 1; j < i + matches + 1 && j < units.size(); j++) {
      units[j] += units[i];
    }
    points += units[i];
  }

  cout << "TOTAL POINTS = " << points << endl;
}
