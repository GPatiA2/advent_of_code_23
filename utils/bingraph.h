#ifndef BIGRAPH_H
#define BIGRAPH_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

template <class T, class U> class Bingraph {

public:
  struct Node;
  using Link = Node *;
  struct Node {

    U info;
    T id_right;
    T id_left;
    Link l;
    Link r;

    Node(U name, T l, T r) {
      info = name;
      id_left = l;
      id_right = r;
    }

    Node() {}

    friend ostream &operator<<(ostream &out, typename Bingraph<T, U>::Node n) {
      out << n.id << " " << n.l->id << " " << n.r->id;
      return out;
    }

    Link opposite_to(const Link &o) {
      if (o == l) {
        return r;
      }
      if (o == r) {
        return l;
      }
      return nullptr;
    }

    friend bool operator==(const Node &n1, const Node &n2) {
      return n1.info == n2.info;
    }
  };

  Bingraph(T entry_id, T id_first) {
    entry_point = Node(entry_id, id_first, id_first);
  }

  Bingraph() {}

  void append(const Link n) { nodes.insert({n->id, n}); }

  void build() {
    for (auto pair : nodes) {
      Node *n = pair.second;
      string id_l = n->id_left;
      string id_r = n->id_right;
      pair.second->l = nodes[id_l];
      pair.second->r = nodes[id_r];
    }
  }

  Link left(Link orig) const { return orig->l; }

  Link right(Link orig) const { return orig->r; }

  Link initial() const { return entry_point.l; }

  friend ostream &operator<<(ostream &out, const Bingraph<T, U> &g) {
    for (auto pair : g.nodes) {
      out << *pair.second << endl;
    }

    return out;
  }

  vector<Link> filter_nodes(bool (*filter)(Link l, Link l2), string id2) {
    vector<Link> v_ret;
    for (auto pair : nodes) {
      if (filter(pair.second, nodes[id2])) {
        v_ret.push_back(pair.second);
      }
    }
    return v_ret;
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

template <class T, class U>
bool operator==(const typename Bingraph<T, U>::Link &l1,
                const typename Bingraph<T, U>::Link &l2) {
  return l1->info == l2->info;
}

#endif
