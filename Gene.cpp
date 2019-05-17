#include "Gene.h"
#include <iostream>
using namespace std;

//#define MUTATE 0.73

double doubleRand() {
  return double(rand()) / (double(RAND_MAX) + 1.0);
}

Gene::Gene(Graph gh) {
    int vnum = gh.get_vtx_num();
    srand(static_cast<unsigned int>(clock()));
    for (int i = 0; i < vnum; i ++) {
        double k = doubleRand();
        //cout << k << endl;
        gene.push_back(k >= 0.5);
    }

    soln_value = calc_soln_value(gh);    
}

// int vtx_num;
// int edge_num;
//  vector<pair<pair<int, int>, int>> edges; // ((v1, v2), weight)

Gene::Gene(Graph gh, vector<bool> new_gene) {
    gene = new_gene;
    soln_value = calc_soln_value_new(gh, new_gene);
}


int Gene::calc_soln_value(Graph gh) {
    int val = 0;
    int fst_vtx = 0;
    int snd_vtx = 0;
    vector<pair<pair<int, int>, int>> edges = gh.get_edges();
    for (auto iter: edges) {
        fst_vtx = iter.first.first;
        snd_vtx = iter.first.second;
        if (gene[fst_vtx-1] != gene[snd_vtx-1]) {
            val = val + iter.second;
        }
    }
    return val;
}

int Gene::calc_soln_value_new(Graph gh, vector<bool> new_gene) {
    int val = 0;
    int fst_vtx = 0;
    int snd_vtx = 0;
    vector<pair<pair<int, int>, int>> edges = gh.get_edges();
    for (auto iter: edges) {
        fst_vtx = iter.first.first;
        snd_vtx = iter.first.second;
        if (new_gene[fst_vtx-1] != new_gene[snd_vtx-1]) {
            val = val + iter.second;
        }
    }
    return val;
}

Gene Gene::mutate() {
    srand(static_cast<unsigned int>(clock()));
    int ith = rand()%(gene.size());
    int sz = gene.size();
    gene[ith] = !gene[ith];
    ith = rand()%(gene.size());
    gene[sz - ith - 1] = !gene[sz - ith - 1];
    //int mutation_size = sz * MUTATE;
    //for (int i = 0; i < mutation_size; i++) {
    //    ith = rand()%(gene.size());
    //    if (ith < mutation_size) {
    //        gene[ith] = !gene[ith];
    //    }
    //}
    return *this;
}


int Gene::get_soln_value() const {
    return soln_value;
}

vector<bool> Gene::get_gene() {
    return gene;
}

void Gene::local_opt(Graph gh) {
  vector<int> rperm;
  bool imp = true;
  int delta = 0;
  int size = gene.size();
  vector<bool> filped_vector = gene;
  
  for (int i = 0; i < size; i ++) {
    rperm.push_back(i);
  }
  random_shuffle (rperm.begin(), rperm.end());

  while (imp) {
    imp = false;
    for (auto j: rperm) {
      filped_vector[j] = !filped_vector[j];
      delta = calc_soln_value_new(gh, filped_vector);
      if (delta > 0) {
	gene[j] = !gene[j];
	soln_value = soln_value + delta;
	imp = true;
      }
    }
  }
}

Gene::Gene() {
    soln_value = INT_MIN;
}

bool operator<(const Gene &s1, const Gene &s2){
    return s1.get_soln_value() < s2.get_soln_value();
}
