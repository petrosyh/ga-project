#include "Graph.h"

Graph::Graph(int vn, int en, vector<pair<pair<int, int>, int>> we) {
  vtx_num = vn;
  edge_num = en;
  edges = we; // ((v1, v2), weight)
}

Graph::Graph () {
  vtx_num = 500;
  edge_num = 5000;
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