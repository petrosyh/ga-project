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

    // cout << "mut start : " << sz * MUTATE  << endl;

    for (int i =0; i < sz*MUTATE; i++) {
      int ith = rand()%sz;
      // delta = get_delta(gh, gene, ith+1);
      gene[ith] = !gene[ith];
      // soln_value = soln_value + delta;
      // delta = 0;
    }
    soln_value = calc_soln_value_new(gh, gene);
    // cout << "mut6" << endl;
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

int Gene::get_delta(vector<vector<pair<int, int>>> *rel_edges, 
		    vector<bool> gee, int pos) {
  int flip_pos = pos - 1;
  auto pos_rel_edges = (*rel_edges)[flip_pos];

  //cout << "rel_edge_size: " << pos_rel_edges.size() << endl;

  int delta = 0;
  int rel_vol;
  int weight;
  
  for (auto iter: pos_rel_edges) {
    rel_vol = iter.first;
    weight = iter.second;
    if (gee[flip_pos] == gee[rel_vol])
      delta = delta + weight;
    else {
      delta = delta - weight;
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
  auto rel_edges = gh.get_rel_edges();
  for (int i = 1; i <= size; i ++) {
    rperm.push_back(i);
  }
  random_shuffle (rperm.begin(), rperm.end());
  // int aaaa = calc_soln_value_new(gh, gene);
  // cout << "aaaaaaaaa: " << aaaa << endl;
  // cout << "soln : " << soln_value << endl;
  // exit(0);
  // cout << "rperm size : " << rperm.size() << endl;
  // int i = 0;
  // cout << "hi 2" << endl;

  // int iter = 0;
  // int iter2 = 0;
  while (imp) {
    imp = false;
    for (auto j: rperm) {
      
      // filped_vector = gene;
      // filped_vector[j] = !filped_vector[j];
      // int fliped = calc_soln_value_new(gh, filped_vector);
      // delta = fliped - soln_value;

      // cout << "hi3" << endl;
      delta = get_delta(&rel_edges, gene, j);
      // iter ++;
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
    // iter2 ++;
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
  // cout << "local opt per local search : " << iter2 << endl;
  // cout << "delta per local : " << iter << endl;
  return *this;
}

Gene::Gene() {
    soln_value = INT_MIN;
}

bool operator<(const Gene &s1, const Gene &s2){
    return s1.get_soln_value() < s2.get_soln_value();
}
