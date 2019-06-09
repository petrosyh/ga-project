#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h> 
#include "Graph.h"

using namespace std;

class Gene {
private:
    const Graph *own_gh;
    vector<bool> gene;
    int soln_value;

public:
    Gene();
    Gene(const Graph* gh);
    Gene(const Graph* gh, vector<bool> new_gene);
    int calc_soln_value(const Graph* gh);
    int calc_soln_value_new(const Graph* gh, vector<bool> new_gene);
    int get_soln_value() const;
    vector<bool> get_gene();
    Gene mutate();
    Gene local_opt();
    int get_delta(vector<bool> gee, int pos);
};
bool operator<(const Gene &s1, const Gene &s2);
