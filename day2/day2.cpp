#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct showing {

  int reds = 0;
  int greens = 0;
  int blues = 0;

  bool possible() {
    bool red_possible = reds <= 12;
    bool green_possible = greens <= 13;
    bool blue_possible = blues <= 14;
    return red_possible && green_possible && blue_possible &&
           (reds + greens + blues <= (13 + 14 + 15));
  }

  string to_text() {
    string ret = "";
    ret += " REDS " + to_string(reds);
    ret += " GREENS " + to_string(greens);
    ret += " BLUES " + to_string(blues) + " ";
    return ret;
  }
};

using game = vector<showing>;

int read_game_id(stringstream &s) {

  string trash = "";
  string game_dirty;
  int game_id;

  s >> trash;
  s >> game_dirty;

  game_dirty.pop_back();

  game_id = stoi(game_dirty);

  return game_id;
}

game read_shows(stringstream &s) {
  game g;
  string word_read = "";
  showing sh;
  int number;
  while (s >> word_read) {
    if (word_read.length() > 2) {
      if (word_read == "green," || word_read == "green;") {
        sh.greens = number;
      } else if (word_read == "blue," || word_read == "blue;") {
        sh.blues = number;
      } else if (word_read == "red," || word_read == "red;") {
        sh.reds = number;
      }
    } else {
      number = stoi(word_read);
    }
    if (word_read[word_read.length() - 1] == ';') {
      g.push_back(sh);
      sh.blues = 0;
      sh.greens = 0;
      sh.reds = 0;
    }
  }
  if (word_read == "green") {
    sh.greens = number;
  } else if (word_read == "blue") {
    sh.blues = number;
  } else if (word_read == "red") {
    sh.reds = number;
  }
  g.push_back(sh);
  return g;
}

int main(int argc, char *argv[]) {

  string file_name = argv[1];

  ifstream file;
  file.open(file_name);

  string line;
  stringstream game_info;
  int game_id;
  game game_data;

  bool possible;
  int i = 0;
  int sum = 0;

  while (getline(file, line)) {

    possible = true;
    game_info = stringstream(line);

    game_id = read_game_id(game_info);

    game_data = read_shows(game_info);
    i = 0;
    while (i < game_data.size() && possible) {
      possible = possible && game_data[i].possible();
      i++;
    }

    int min_red = 0;
    int min_blue = 0;
    int min_green = 0;
    for (showing sh : game_data) {
      min_red = max(min_red, sh.reds);
      min_blue = max(min_blue, sh.blues);
      min_green = max(min_green, sh.greens);
    }
    cout << "FOR GAME " << game_id << " THE MINIMUMS ARE " << endl;
    cout << "   " << min_red << " REDS" << endl;
    cout << "   " << min_blue << " BLUES " << endl;
    cout << "   " << min_green << " GREENS" << endl;
    cout << "    AND THE POWER IS " << min_red * min_blue * min_green << endl;
    int power = min_red * min_blue * min_green;
    sum += power;
  }
  cout << "SUM = " << sum << endl;
}
