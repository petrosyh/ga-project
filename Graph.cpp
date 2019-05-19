#include "Graph.h"
// #include <cassert>

Graph::Graph(int vn, int en, vector<pair<pair<int, int>, int>> we) {
  vtx_num = vn;
  edge_num = en;
  edges = we; // ((v1, v2), weight)
  rel_edges.resize(1000);
  // cout << "Size : " << rel_edges.size() << endl;
  int to, from;
  for (auto iter:we) {
    to = iter.first.first - 1;
    from = iter.first.second - 1;
    // cout << to << endl;
    // cout << from << endl;
    // assert (to >= 0);
    // assert (from >= 0);
    rel_edges[to].push_back(iter);
    rel_edges[from].push_back(iter);
  }
  // cout << "hi" << endl;

}

Graph::Graph () {
  vtx_num = 1000;
  edge_num = 10000;
}

int Graph::get_vtx_num () {
  return vtx_num;
}

int Graph::get_edge_num () {
  return edge_num;
}

vector<pair<pair<int, int>, int>> Graph::get_edges () {
  return edges;
}

vector<vector<pair<pair<int, int>, int>>> Graph::get_rel_edges() {
  return rel_edges;
}
