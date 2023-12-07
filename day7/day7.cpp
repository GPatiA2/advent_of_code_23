#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

enum Hand_Val {
  FIVE_OF_A_KIND,
  FOUR_OF_A_KIND,
  FULL_HOUSE,
  THREE_OF_A_KIND,
  TWO_PAIR,
  ONE_PAIR,
  HIGH_CARD
};

class Hand {

private:
  string cards;
  int bid;

  Hand_Val val;

  string code;

  static map<Hand_Val, string> enum_to_string;
  static map<string, Hand_Val> code_to_enum;
  static vector<char> card_order;

  Hand_Val get_hand_val() {

    map<char, int> card_type_counter;
    for (char c : cards) {
      if (card_type_counter.find(c) == card_type_counter.end()) {
        card_type_counter.insert({c, 1});
      } else {
        card_type_counter[c] += 1;
      }
    }

    vector<int> card_type_counts;
    for (auto i = card_type_counter.begin(); i != card_type_counter.end();
         i++) {
      card_type_counts.push_back(i->second);
    }

    sort(card_type_counts.begin(), card_type_counts.end());

    code = "";
    for (int i = card_type_counts.size() - 1; i >= 0; i--) {
      code += to_string(card_type_counts[i]);
    }

    return code_to_enum[code];
  }

  int card_val(char c) const {
    int i = 0;
    while (c != card_order[i]) {
      i++;
    }
    return i;
  }

public:
  Hand(string s, int b) {
    cards = s;
    bid = b;
    val = get_hand_val();
  }

  char get(int i) const {
    if (i < 0 || i > 4) {
      return ' ';
    } else {
      return cards[i];
    }
  }

  bool operator<(const Hand &h2) const {
    if (this->val != h2.val) {
      return this->val < h2.val;
    } else {
      int i = 0;
      while (i < this->cards.size() && this->get(i) == h2.get(i)) {
        i++;
      }

      if (i == this->cards.size()) {
        return true;
      } else {
        int cv1 = card_val(this->get(i));
        int cv2 = card_val(h2.get(i));
        return card_val(this->get(i)) < card_val(h2.get(i));
      }
    }
  }

  int get_bid() const { return bid; }
  string get_cards() const { return cards; }
  Hand_Val get_val() const { return val; }
  string get_code() const { return code; }
};

map<Hand_Val, string> Hand::enum_to_string = {
    {FIVE_OF_A_KIND, "FIVE_OF_A_KIND"},
    {FOUR_OF_A_KIND, "FOUR_OF_A_KIND"},
    {FULL_HOUSE, "FULL_HOUSE"},
    {THREE_OF_A_KIND, "THREE_OF_A_KIND"},
    {TWO_PAIR, "TWO_PAIR"},
    {ONE_PAIR, "ONE_PAIR"},
    {HIGH_CARD, "HIGH_CARD"}};

map<string, Hand_Val> Hand::code_to_enum = {
    {"5", FIVE_OF_A_KIND},    {"41", FOUR_OF_A_KIND}, {"32", FULL_HOUSE},
    {"311", THREE_OF_A_KIND}, {"221", TWO_PAIR},      {"2111", ONE_PAIR},
    {"11111", HIGH_CARD}};

vector<char> Hand::card_order = {'A', 'K', 'Q', 'J', 'T', '9', '8',
                                 '7', '6', '5', '4', '3', '2'};

ostream &operator<<(ostream &out, const Hand &h) {
  out << h.get_cards() << " " << h.get_code() << " " << h.get_val() << " "
      << h.get_bid();
  return out;
}

Hand parse_hand(istream &s) {
  string cards;
  int b;

  s >> cards;
  s >> b;

  return {cards, b};
}

int main(int argc, char *argv[]) {

  string file_name = argv[1];
  ifstream file;
  file.open(file_name);

  string line;
  stringstream r_line;

  vector<Hand> game;

  while (getline(file, line)) {
    r_line = stringstream(line);
    Hand h = parse_hand(r_line);
    game.push_back(h);
  }

  for (Hand h : game) {
    cout << h << endl;
  }
  cout << " ____________________________ " << endl;

  sort(game.begin(), game.end());

  for (Hand h : game) {
    cout << h << endl;
  }

  int sum = 0;
  int hand_pos = 1;
  for (int i = game.size() - 1; i >= 0; i--) {
    sum += game[i].get_bid() * hand_pos;
    hand_pos++;
  }

  cout << "SUM = " << sum << endl;
}
