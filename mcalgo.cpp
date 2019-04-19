#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
//#include "Graph.h"
//#include "Gene.h"
#include "Gasolver.h"

using namespace std;

#define INITIAL 1000
#define ITERTIME 5
#define CHILDNUM 40

int main(int argc, char *argv[]) {
  clock_t start_time = clock();
  clock_t diff_time;
  string filePath = argv[1];  // "maxcut.in";
  int vtxnum, edgenum;
  int v1, v2, weight;
  int iteration = 0;
  vector<pair<pair<int, int>, int>> we;
  Graph gh;
  Gasolver gas;
  ifstream openFile(filePath.data());

  if (openFile.is_open()) {
    string line;
    int num;
    stringstream ss;
    getline(openFile, line);

    // first line
    ss.str(line);
    ss >> vtxnum >> edgenum;
    ss.clear();
    //cout << "vtx: " << vtxnum << endl;
    //cout << "edge: " << edgenum << endl;

    // other lines
    while(getline(openFile, line)) {
      ss.str(line);
      //cout << "cur_line: " << line << endl;

      ss >> v1 >> v2 >> weight;
      we.push_back(make_pair(make_pair(v1, v2), weight));
      ss.clear();
    }
    openFile.close();
  }

  gh = Graph(vtxnum, edgenum, we);
  gas = Gasolver(gh, INITIAL);
  vector<Gene> gas_vector = gas.get_gene_vector();
  //cout << "Graph length: " << gh.get_edges().size() << endl;
  //cout << "GAS: " << gas.get_gas_size() << endl;
  //for (int j = 0; j < gas.get_gas_size(); j ++) {
  //  cout << gas_vector[j].get_soln_value() << endl;
  //}

  do {
    //cout << "Hi " << endl;
    iteration ++;
    //cout << "Hi 1" << endl;
    gas = gas.generation(CHILDNUM);
    //cout << "Hi 2" << endl;
    cout << "iter : " << iteration << "max : " << gas.get_maxcut() << endl;
    diff_time = (float) (clock() - start_time) / CLOCKS_PER_SEC;
  } while(diff_time <= ITERTIME);

  return 0;
}

//Graph string_parser(string fpath) {
//  
//}
