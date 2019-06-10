#include "Gasolver.h"

#define EVOL_PRESSURE 0.65
#define ROULETTE_K 4

#define LOC0 30
#define LOC1 75
#define FM0 2
#define FM1 10

Gasolver::Gasolver(Graph gh, int sz) {
    Gene gene;
    own_graph = gh;
    size = sz;
    for (int i = 0; i < sz; i ++) {
        gene = Gene(gh);
        gene_vector.push_back(gene);
    }

}

Gasolver::Gasolver() {

}

int minval(vector<int> values) {
    int ret = INT_MAX;
    for (auto iter : values) {
        if (ret > iter) {
            ret = iter;
        }
    }
    return ret;
}

int minwhere(vector<int> values) {
    int ret = INT_MAX;
    int i = 0;
    int j = 0;
    for (auto iter : values) {
        if (ret > iter) {
            ret = iter;
            j = i;
        }
        i++;
    }
   return j;
}

int maxval(vector<int> values) {
    int ret = INT_MIN;
    for (auto iter : values) {
        if (ret < iter)
            ret = iter;
    }
    return ret;
}

int sumval(vector<int> values) {
    int ret = 0;
    for (auto iter : values) {
        ret += iter;
    }
    return ret;
}


int maxwhere(vector<int> values) {
    int ret = INT_MIN;
    int i = 0;
    int j = 0;
    for (auto iter : values) {
        if (ret < iter) {
            ret = iter;
            j = i;
        }
        i++;
    }
    return j;
}


vector<Gene> Gasolver::get_gene_vector() {
    return gene_vector;
}

int Gasolver::get_gas_size() {
    return size;
}

int Gasolver::selection() {
    // srand(static_cast<unsigned int>(clock()));
    int selector = rand()%size;
    return selector;
}

double dRand(double dMin, double dMax) {
    double d = (double)rand() / RAND_MAX;
    return dMin + d * (dMax - dMin);
}

//assume values are sorted.
int Gasolver::roulette_selection(vector<double> fit, double sum_of_fit) {
  srand(static_cast<unsigned int>(clock()));
  double point = dRand(0, sum_of_fit);
  double sum = 0;

  for (int i = 0; i < size; i ++) {
    sum = sum + fit[i];
    if (point < sum)
      return i;
  }
  return size - 1;
}



Gene Gasolver::gas_roulette_merge() {
  // srand(static_cast<unsigned int>(clock()));
  // vector<double> fitness_vec = fitnesses();
  // double sum_of_fitnesses = 0;
  // for (auto& n : fitness_vec)
  //   sum_of_fitnesses += n;

  //   pair<Gene, int> sel1 = roulette_selection();
  //   pair<Gene, int> sel2 = roulette_selection();

  //   Gene g1 = sel1.first;
  //   Gene g2 = sel2.first;

  //   int ith_1 = sel1.second;
  //   int ith_2 = sel2.second;

  //   int gene_size = g1.get_gene().size();

  //   vector<bool> new_gene1;
  //   Gene ret;

  //   for (int i = 0; i < gene_size; i++) {
  //       if (i % 2 == 0) {
  //           new_gene1.push_back(gene_vector[ith_1].get_gene()[i]);
  //       } else {
  //           new_gene1.push_back(gene_vector[ith_2].get_gene()[i]);
  //       }
  //   }
  //   ret = Gene(own_graph, new_gene1);
  Gene ret = Gene();
    return ret;
}

void gene_random_merge(Gene &gene1, Gene &gene2, vector<bool> &child) {
    srand(static_cast<unsigned int>(clock()));
    vector<bool> g1 = gene1.get_gene();
    vector<bool> g2 = gene2.get_gene();
    int size = g1.size();

    // cout << "SIZE : " << size << endl;
    // cout << "value: " << gene1.get_soln_value() << endl;
    // assert (g1.size() == g2.size());
    // cout << "before child : "<< child.size() << endl;
    for (int i = 0; i < size; i ++){
        int p = rand() % 2;
        //cout << "P0 : " << p << endl;
        if (p == 1) {
            child[i] = g1[i];
        } else if (p == 0) {
            assert(p == false);
            child[i] = g2[i];
        }
    }
    // cout << "HERE!!!!!!! : "<< child.size() << endl;
}

int tournament(int g1, int g2) {
    srand(static_cast<unsigned int>(clock()));
    double r = ((double) rand() / (RAND_MAX));
    // cout << "r : " << r << endl;
    if (EVOL_PRESSURE > r) {
        return max(g1, g2);
    } else {
        return min(g1, g2);
    }
}

Gene Gasolver::gas_merge() {

    return Gene();
}

int calc_aux(Graph gh, vector<bool> new_gene) {
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


void Gasolver::generation(int child, int flag) {
  for (int i = 0; i < child; i ++) {
    gene_vector[i] = gene_vector[i].variation_of_fm(&own_graph);
  }
}

vector<int> Gasolver::get_all_value() {
    vector<int> ret;
    for (auto iter : gene_vector) {
        ret.push_back(iter.get_soln_value());
    }
    return ret;
}

int Gasolver::get_value_sum() {
    int ret = 0;
    for (auto iter : gene_vector) {
        ret = ret + iter.get_soln_value();
    }
    return ret;
}

vector<int> Gasolver::get_value_acc() {
    vector<int> ret;
    int acc = 0;
    for (auto iter : gene_vector) {
        acc = acc + iter.get_soln_value();
        ret.push_back(acc);
    }
    return ret;
}

int Gasolver::get_maxcut() {
    vector<int> values = get_all_value();
    int max = maxval(values);
    return max;
}

int Gasolver::get_maxcut_avg() {
    vector<int> values = get_all_value();
    int sum = sumval(values);
    return (sum/size);
}

void Gasolver::print_opt_set() {
    vector<int> values = get_all_value();
    int max_state = maxwhere(values);
    vector<bool> opt_set = gene_vector[max_state].get_gene();
    for (int i = 0; i < opt_set.size(); i ++) {
        if (opt_set[i])
            cout << (i+1) << " ";
    }
}

double Gasolver::StandardDeviation()
{
  vector<int> values = get_all_value();
  return sqrt(Variance(values));
}

double Gasolver::Variance(vector<int> samples)
{
     int size = samples.size();

     double variance = 0;
     double t = samples[0];
     for (int i = 1; i < size; i++)
     {
          t += samples[i];
          double diff = ((i + 1) * samples[i]) - t;
          variance += (diff * diff) / ((i + 1.0) *i);
     }

     return variance / (size - 1);
}

vector<double> Gasolver::fitnesses() {
    vector<int> values = get_all_value();

    int min = minval(values);
    int max = maxval(values);
    vector<double> ret;
    for (auto iter : gene_vector) {
      ret.push_back((min - iter.get_soln_value()) + ((min - max)/(ROULETTE_K - 1)));
    }
    return ret;
}
