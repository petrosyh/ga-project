#define MAXVTX 500
#include <vector>

using namespace std;

class Graph {
private:
  int vtx_num;
  int edge_num;
  vector<pair<pair<int, int>, int>> edges; // ((v1, v2), weight)


public:
  Graph(int vtx_nam, int edge_num, vector<pair<pair<int, int>, int>> edges);
};
