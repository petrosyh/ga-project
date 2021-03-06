#include <vector>
#include <cmath>
#include "Gene.h"
//#include "Graph.h"
#include <algorithm> 
#include <iterator>
#include <iostream>

using namespace std;

class Gasolver {
private:
    vector<Gene> gene_vector;
    Graph own_graph;
    int size;

public:
    Gasolver(Graph gh, int sz);
    Gasolver();
    vector<Gene> get_gene_vector();
    Gene gas_merge();
    Gene selection();
    Gasolver generation(int child);
    int get_gas_size();
    int get_maxcut();
    vector<int> get_all_value();
    vector<double> fitnesses();
};