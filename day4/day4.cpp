#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {

  ifstream file;
  string file_name;
  string card_line;

  vector<int> winning_numbers;
  vector<int> card_numbers;

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

    int i = 0;
    int j = 0;
    while (i < winning_numbers.size() && j < card_numbers.size()) {
      if (winning_numbers[i] == card_numbers[j]) {
        cout << "MATCHING NUMBER " << winning_numbers[i] << " ON " << i
             << " WINNING AND " << j << " CARD " << endl;
        i += 1;
        j += 1;
        card_points += 1;
      } else if (winning_numbers[i] < card_numbers[j]) {
        i += 1;
      } else if (card_numbers[j] < winning_numbers[i]) {
        j += 1;
      }
    }
    cout << "POINTS OF THIS CARD = " << card_points << endl;
    if (card_points != -1) {
      points += pow(2, card_points);
    }
  }

  cout << "TOTAL POINTS = " << points << endl;
}
