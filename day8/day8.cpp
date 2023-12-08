#include "aocutils.h"
#include "bingraph.h"
#include "circlist.h"
#include <fstream>
#include <iostream>
using namespace std;

using Node = Bingraph<string>::Node;
using Link = Bingraph<string>::Node *;

int main(int argc, char *argv[]) {

  string file_name = argv[1];
  ifstream file;
  file.open(file_name);

  string line;
  getline(file, line);

  Circlist<char> guide;
  for (char c : line) {
    guide.push_back(c);
  }

  Bingraph<string> graph("000", "AAA");

  while (getline(file, line)) {
    if (line.size() > 0) {
      vector<string> split = split_line(line, " ");
      split[2] = split[2].substr(1, 3);
      split[3] = split[3].substr(0, 3);

      Link n;
      n = new Node(split[0], split[2], split[3]);
      cout << "CREATING NODE " << split[0] << " " << split[2] << " " << split[3]
           << endl;
      graph.append(n);
    }
  }

  graph.build();
  cout << "GRAPH CREATED " << endl;
  cout << graph;

  int steps = 0;
  Link position = graph.initial();
  char step = guide.next();
  while (position->id != "ZZZ") {
    if (step == 'L') {
      position = position->l;
    } else if (step == 'R') {
      position = position->r;
    }
    steps += 1;
    step = guide.next();
  }

  cout << "STEPS = " << steps << endl;
}
