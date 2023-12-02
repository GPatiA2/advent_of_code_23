#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <regex>
using namespace std;

string match_last_read(string read) {

  string possible_matches[18] = {"one",   "1", "two",   "2", "three", "3",
                                 "four",  "4", "five",  "5", "six",   "6",
                                 "seven", "7", "eight", "8", "nine",  "9"};
  int i = 0;
  while (i < 18) {
    if (read.length() >= possible_matches[i].length()) {
      if (read.substr(read.length() - possible_matches[i].length()) ==
          possible_matches[i]) {
        return possible_matches[i];
      }
    }
    i++;
  }
  return "";
}

string text_to_digit(string text) {

  if (text == "one") {
    return "1";
  }
  if (text == "two") {
    return "2";
  }
  if (text == "three") {
    return "3";
  }
  if (text == "four") {
    return "4";
  }
  if (text == "five") {
    return "5";
  }
  if (text == "six") {
    return "6";
  }
  if (text == "seven") {
    return "7";
  }
  if (text == "eight") {
    return "8";
  }
  if (text == "nine") {
    return "9";
  }
  return "";
}

int main(int argc, char *argv[]) {

  string file = argv[1];

  ifstream rfile;
  rfile.open(file);

  string line;
  int sum = 0;

  while (getline(rfile, line)) {
    cout << "line = " << line << endl;
    string read = "";
    string first = "";
    string last = "";

    for (int i = 0; i < line.length(); i++) {
      read += line[i];
      string match = match_last_read(read);
      if (first == "") {
        first = match;
      } else if (match != "") {
        last = match;
        // cout << "READ = " << read << " UPDATED LAST TO " << last << endl;
      }
    }

    if (first != "" && last == "") {
      last = first;
    }

    if (first.length() > 1) {
      first = text_to_digit(first);
    }
    if (last.length() > 1) {
      last = text_to_digit(last);
    }

    first.append(last);
    cout << "NUMBER = " << first << endl;
    sum += stoi(first);
  }

  cout << "SUM = " << sum << endl;
}
