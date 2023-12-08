#ifndef BIGRAPH_H
#define BIGRAPH_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

template <class T> class Bingraph {

public:
  struct Node;
  using Link = Node *;
  struct Node {

    T id;
    T id_right;
    T id_left;
    Link l;
    Link r;
    int num_node; 
    
    Node(T name, T l, T r) {
      id = name;
      id_left = l;
      id_right = r;
    }

    Node() {}

    friend ostream &operator<<(ostream &out, typename Bingraph<T>::Node n) {
      out << n.id << " " << n.l->id << " " << n.r->id;
      return out;
    }
  };

  Bingraph(T entry_id, T id_first) {
    entry_point = Node(entry_id, id_first, id_first);
  }

  void append(const Link n) { nodes.insert({n->id, n}); }

  void build() {
    int count = 0;
    for (auto pair : nodes) {
      Node *n = pair.second;
      string id_l = n->id_left;
      string id_r = n->id_right;
      pair.second->l = nodes[id_l];
      pair.second->r = nodes[id_r];
      n->num_node = count;
      if (count == 0) {
        entry_point.l = pair.second;
        entry_point.r = pair.second;
      }
      count++;
    }
  }

  Link left(Link orig) const { return orig->l; }

  Link right(Link orig) const { return orig->r; }

  Link initial() const { return entry_point.l; }

  friend ostream &operator<<(ostream &out, const Bingraph<T> &g) {
    for (auto pair : g.nodes) {
      out << *pair.second << endl;
    }

    return out;
  }

  vector<Link> filter_nodes(bool (*filter)(Link l)) {
    vector<Link> v_ret;
    for (auto pair : nodes) {
      if (filter(pair.second)) {
        v_ret.push_back(pair.second);
      }
    }
    return v_ret;
  }

  int count_nodes() const { return nodes.size(); }

private:
  map<string, Node *> nodes;
  Node entry_point;
};

#endif
