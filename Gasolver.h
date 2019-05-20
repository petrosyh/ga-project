#include <vector>
#include <cmath>
#include "Gene.h"
//#include "Graph.h"
#include <algorithm> 
#include <iterator>
#include <iostream>
#include <utility> 

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
    Gene gas_roulette_merge();
    pair<Gene, int> selection();
    pair<Gene, int> roulette_selection();
    Gasolver generation(int child);
    int get_gas_size();
    int get_maxcut();
    int get_maxcut_avg();
    int get_value_sum();
    vector<int> get_value_acc();
    void print_opt_set();
    vector<int> get_all_value();
    double StandardDeviation();
    double Variance(vector<int> samples);

    vector<double> fitnesses();
};
