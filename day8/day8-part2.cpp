#include "aocutils.h"
#include "bingraph.h"
#include "circlist.h"
#include <fstream>
#include <iostream>
#include <numeric>
using namespace std;

using Node = Bingraph<string>::Node;
using Link = Bingraph<string>::Node *;

void print_vector(const vector<Link> &l) {
  for (Link elem : l) {
    cout << *elem << " || ";
  }
  cout << endl;
}

bool ends_with_A(Link l) { return l->id[l->id.size() - 1] == 'A'; }

bool ends_with(Link l, char c) { return l->id[l->id.size() - 1] == c; }

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
  cout << "IT HAS " << graph.count_nodes() << " NODES " << endl;
  cout << graph;
  cout << "______________________________" << endl;

  vector<long long int> steps;
  vector<Link> beg_nodes = graph.filter_nodes(&ends_with_A);
  int end_in_z = 0;
  char step = guide.next();

  for (int i = 0; i < beg_nodes.size(); i++) {
    steps.push_back(0);
    while (!ends_with(beg_nodes[i], 'Z')) {
      if (step == 'L') {
        beg_nodes[i] = beg_nodes[i]->l;
      }
      if (step == 'R') {
        beg_nodes[i] = beg_nodes[i]->r;
      }
      steps[steps.size() - 1] += 1;
      step = guide.next();
    }
  }

  long int final_steps = steps[0];
  for (int i = 1; i < steps.size(); i++) {
    final_steps = lcm(final_steps, steps[i]);
  }

  cout << "STEPS = " << final_steps << endl;
}
