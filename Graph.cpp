#include "Graph.h"

Graph::Graph(int vn, int en, vector<pair<pair<int, int>, int>> we) {
  vtx_num = vn;
  edge_num = en;
  edges = we; // ((v1, v2), weight)
}
