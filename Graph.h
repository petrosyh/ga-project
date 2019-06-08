#define MAXVTX 1000
#include <vector>
#include <iostream>

using namespace std;

class Graph {
private:
  int vtx_num;
  int edge_num;
  vector<pair<pair<int, int>, int>> edges; // ((v1, v2), weight)
  vector<vector<pair<int, int>>> rel_edges;

public:
  Graph();
  Graph(int vtx_nam, int edge_num, vector<pair<pair<int, int>, int>> edges);
  int get_vtx_num();
  int get_edge_num();
  vector<pair<pair<int, int>, int>> get_edges();
  vector<vector<pair<int, int>>> get_rel_edges();
};
