#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
#include "Graph.h"

using namespace std;

class Gene {
private:
    vector<bool> gene;
    int soln_value;

public:
    Gene();
    Gene(Graph gh);
    Gene(Graph gh, vector<bool> new_gene);
    int calc_soln_value(Graph gh);
    int calc_soln_value_new(Graph gh, vector<bool> new_gene);
    int get_soln_value() const;
    vector<bool> get_gene();
    Gene mutate();
};
bool operator<(const Gene &s1, const Gene &s2);