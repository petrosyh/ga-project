#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>
//#include "Graph.h"
//#include "Gene.h"
#include "Gasolver.h"

using namespace std;

#define INITIAL 1000
#define ITERTIME 170000
#define CHILDNUM 300

int main(int argc, char *argv[]) {
  //clock_t start_time = clock();
  const std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  //clock_t diff_time;
  string filePath = argv[1];  // "maxcut.in";
  int vtxnum, edgenum;
  int v1, v2, weight;
  int iteration = 0;
  vector<pair<pair<int, int>, int>> we;
  Graph gh;
  Gasolver gas;
  ifstream openFile(filePath.data());
  double iter_time = 0;
  
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
  iter_time = (500 * vtxnum / 3000) * 1000; /* msec */
  gh = Graph(vtxnum, edgenum, we);
  gas = Gasolver(gh, INITIAL);
  // vector<Gene> gas_vector = gas.get_gene_vector();
  //cout << "Graph length: " << gh.get_edges().size() << endl;
  //cout << "GAS: " << gas.get_gas_size() << endl;
  //for (int j = 0; j < gas.get_gas_size(); j ++) {
  //  cout << gas_vector[j].get_soln_value() << endl;
  //}

  do {
    //cout << "Hi " << endl;
    iteration ++;
    //cout << "Hi 1" << endl;
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    double six = now/iter_time;
    if (six < 0.2)
      gas.generation(CHILDNUM, 0);
    else
      gas.generation(CHILDNUM, 1);
    //cout << "Hi 2" << endl;
    // cout << "HIIIIII " << endl;
    
    // if (iteration % 10 == 0) {
    //  	cout << iteration << ", " << gas.get_maxcut() << ", " << gas.get_maxcut_avg() << endl;
    // 	// for (auto iter: gas.get_gene_vector()) {
    // 	//   cout << iter.get_soln_value() << " ";
    // 	// }
    // 	// cout << endl;    
    
    // }
    //diff_time = (float) (clock() - start_time) / CLOCKS_PER_SEC;
    
  } while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() <= (iter_time - 5000));

  // gas.print_opt_set();
  cout << iteration << ", " << gas.get_maxcut() << ", " << gas.get_maxcut_avg() << ", " << gas.StandardDeviation() << endl;
  return 0;
}

//Graph string_parser(string fpath) {
//  
//}
