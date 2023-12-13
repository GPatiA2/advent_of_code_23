#include "../utils/aocutils.h"
#include "../utils/matrix.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct spring_row {

  string status;
  vector<int> damage_groups;

  spring_row(string s, vector<int> &v) {
    status = s;
    damage_groups = v;
  }

  long int calculate_arrangements() {
    long int total = 0;
    total += arrangements(0, 0, 0);
    return total;
  }

  long int arrangements(long int string_idx, long int groups_idx,
                        long int call_idx) {
    string idx = "";
    for (int i = 0; i < call_idx; i++) {
      idx += "  ";
    }
    // cout << idx << "CALL " << substr(status, string_idx, status.size()) << "
    // "
    //      << subvect(damage_groups, groups_idx, damage_groups.size())
    //      << " SIZE = "
    //      << subvect(damage_groups, groups_idx, damage_groups.size()).size()
    //      << endl;

    if (string_idx >= status.size()) {
      // cout << idx << "BASE CASE " << endl;
      if (groups_idx >= damage_groups.size()) {
        // cout << "1" << endl;
        return 1;
      } else {
        // cout << "0" << endl;
        return 0;
      }
    }

    if (groups_idx >= damage_groups.size()) {
      // cout << idx << "BASE CASE BC " << groups_idx
      //      << " >= " << damage_groups.size();
      if (count_in_substr(status, string_idx, status.size(), '#') == 0) {
        // cout << "1" << endl;
        return 1;
      } else {
        // cout << "0" << endl;
        return 0;
      }
    }

    // cout << idx << "NOT BASE CASE" << endl;

    long int res = 0;

    if (status[string_idx] == '.' || status[string_idx] == '?') {
      // cout << idx << "ADVANCING STRING" << endl;
      res += arrangements(string_idx + 1, groups_idx, call_idx + 1);
    }

    if (status[string_idx] == '#' || status[string_idx] == '?') {
      bool enough_to_cover_group =
          damage_groups[groups_idx] + string_idx <= status.size();

      char next_to_block = status[string_idx + damage_groups[groups_idx]];

      bool block_ends =
          (next_to_block == '.') || (next_to_block == '?') ||
          (string_idx + damage_groups[groups_idx] >= status.size());

      int dots_in_block = count_in_substr(
          status, string_idx, string_idx + damage_groups[groups_idx], '.');

      bool no_dots_in_block = dots_in_block == 0;

      // cout << idx << "ENOUGH TO COVER " << enough_to_cover_group << endl;
      // cout << idx << "BLOCK ENDS " << block_ends << endl;
      // cout << idx << "NO DOTS IN BLOCK " << no_dots_in_block << endl;

      if (no_dots_in_block && block_ends && enough_to_cover_group) {
        res += arrangements(string_idx + damage_groups[groups_idx] + 1,
                            groups_idx + 1, call_idx + 1);
      }
    }

    return res;
  }
};

int main(int argc, char *argv[]) {

  string file_name = argv[1];
  ifstream file(file_name);

  string line;
  vector<spring_row> spring_field;
  while (getline(file, line)) {
    vector<string> split = split_line(line, " ");
    string status = split[0];
    vector<int> g;
    vector<string> g_str = split_line(split[1], ",");
    for (string s : g_str) {
      g.push_back(stoi(s));
    }
    spring_field.push_back(spring_row(status, g));
  }

  long int total_arrangements = 0;
  long int partial_arrangements = 0;
  for (spring_row sr : spring_field) {
    partial_arrangements = 0;
    cout << "FOR " << sr.status << " " << sr.damage_groups << endl;
    partial_arrangements = sr.calculate_arrangements();
    total_arrangements += partial_arrangements;
    cout << " TOTAL ARRANGEMENTS WERE " << total_arrangements << endl;
    // char chasiofd = getchar();
  }

  cout << "TOTAL ARRANGEMENTS = " << total_arrangements << endl;

  return 0;
}
