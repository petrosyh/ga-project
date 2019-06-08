#include "Gene.h"
#include <iostream>
using namespace std;

#define MUTATE 0.05

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

Gene Gene::mutate(Graph gh) {
    srand(static_cast<unsigned int>(clock()));
    int sz = gene.size();
    int delta = 0;

    for (int i =0; i < sz*MUTATE; i++) {
      int ith = rand()%sz;
      delta = get_delta(gh, gene, sz - ith);    
      gene[sz - ith - 1] = !gene[sz - ith - 1];
      soln_value = soln_value + delta;
      delta = 0;
    }
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

int Gene::get_delta(Graph gh, vector<bool> gee, int pos) {
  auto rel_edges = gh.get_rel_edges();
  // cout << "hi size : " << rel_edges.size() << endl;
  auto pos_rel_edges = rel_edges[pos - 1];
  // cout << "hi pos : " << pos << endl;

  int delta = 0;

  for (auto iter: pos_rel_edges) {
    if (gee[iter.first.first-1] == gee[iter.first.second-1])
      delta = delta + iter.second;
    else {
      delta = delta - iter.second;
    }
  }
  return delta;  
}

Gene Gene::local_opt(Graph gh) {
  // cout << "hi1" << endl;
  vector<int> rperm;
  bool imp = true;
  int delta = 0;
  //int delta_sum = 0;
  int size = gene.size();
  vector<bool> filped_vector = gene;
  
  for (int i = 1; i <= size; i ++) {
    rperm.push_back(i);
  }
  random_shuffle (rperm.begin(), rperm.end());
  // int aaaa = calc_soln_value_new(gh, gene);
  // cout << "aaaaaaaaa: " << aaaa << endl;
  // cout << "soln : " << soln_value << endl;
  // exit(0);
  
  // int i = 0;
  // cout << "hi 2" << endl;
  while (imp) {
    imp = false;
    for (auto j: rperm) {
      
      // filped_vector = gene;
      // filped_vector[j] = !filped_vector[j];
      // int fliped = calc_soln_value_new(gh, filped_vector);
      // delta = fliped - soln_value;

      // cout << "hi3" << endl;
      delta = get_delta(gh, gene, j);
      // cout << "hi4" << endl;
      if (delta > 0) {
	// cout << endl;
	// cout << "j info : " << j << " delta : " << delta << endl;
	// int a_soln_value = calc_soln_value_new(gh, gene);
	// cout << "before flip: " << a_soln_value << endl;
	// cout << "hi5" << endl;
	gene[j-1] = !gene[j-1];
	// cout << "hi6" << endl;
	// int b_soln_value = calc_soln_value_new(gh, gene);
	// cout << "after flip: " << b_soln_value << endl;
	// assert ((b_soln_value - a_soln_value) == delta);

	soln_value = soln_value + delta;

	// cout << "soln val 1: " << soln_value << endl;
	//assert (soln_value == b_soln_value);
	imp = true;
      }
    }
    // int c_soln_value = calc_soln_value_new(gh, gene);
    // cout << "c value: " << c_soln_value << endl;
    // cout << "soln val 2: " << soln_value << endl;
  }
  // int bbbb = calc_soln_value_new(gh, gene);

  // if (bbbb>aaaa) {
  //   cout << "before_opt: " << aaaa << endl;
  //   cout << "delta : " << bbbb - aaaa << endl;
  //   cout << "after_opt: " << bbbb << endl;
  //   cout << "after_opt soln: " << soln_value << endl;
  //   assert (bbbb == soln_value);
  //   // exit(0);
  // }
  // assert (bbbb>=aaaa);
  // cout << "hi end" << endl;
  //  int after_val = calc_soln_value_new(gh, gene);
  return *this;
}

Gene::Gene() {
    soln_value = INT_MIN;
}

bool operator<(const Gene &s1, const Gene &s2){
    return s1.get_soln_value() < s2.get_soln_value();
}
