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
  vector<int> values;
  // vector<Gene> new_children;
  // int minstate;
  Gene g;

  // cout << "before mut soln: " << gene_vector[0].get_soln_value() << endl;
  // cout << "before mut calc: " << calc_aux(own_graph, gene_vector[0].get_gene()) << endl;
  sort(gene_vector.begin(), gene_vector.end());

  vector<bool> children[child];
  vector<Gene> children_gene;
  for (int i = 0; i < child; i ++) {
    // srand(static_cast<unsigned int>(clock()));
    // vector<double> fitness_vec = fitnesses();
    // double sum_of_fitnesses = 0;
    // for (auto& n : fitness_vec) {
    // 	sum_of_fitnesses += n;
    // }

    // int sel1 = roulette_selection(fitness_vec, sum_of_fitnesses);
    // int sel2 = roulette_selection(fitness_vec, sum_of_fitnesses);
    // int sel3 = roulette_selection(fitness_vec, sum_of_fitnesses);
    // int sel4 = roulette_selection(fitness_vec, sum_of_fitnesses);

    int sel1 = selection();
    int sel2 = selection();
    int sel3 = selection();
    int sel4 = selection();
    // cout << "sel: " << sel1 << ", " << sel2 << ", " << sel3 << ", " << sel4 << endl;
    // assert (sel1 != sel2);

    int winner1 = tournament(sel1, sel2);
    int winner2 = tournament(sel3, sel4);
    // cout << "win: " << winner1 << ", " << winner2 << endl;
    children[i] = vector<bool>(gene_vector[sel1].get_gene().size());
    // cout << "G1: " << gene_vector[winner1].get_gene().size() << ", " << gene_vector[winner2].get_gene().size() << endl;
    // cout << "G2: " << gene_vector[winner1].get_soln_value() << ", " << gene_vector[winner2].get_soln_value() << endl;
    // cout << "MCUT: " << get_maxcut() << endl;
    gene_random_merge(gene_vector[winner1], gene_vector[winner2], children[i]);
    // cout << "merge fin" << endl;


    Gene new_gene = Gene(own_graph, children[i]);
    new_gene = new_gene.mutate(&own_graph, flag);

    int loc_rate;
    int fm_rate;
    if (flag == 0) {
      loc_rate = LOC0;
      fm_rate = FM0;
    } else if (flag == 1) {
      loc_rate = LOC1;
      fm_rate = FM1;
    }


    // if (i % loc_rate == 0) {
    //   // new_gene = new_gene.local_opt(&own_graph);
    // }
    if (i % fm_rate == 0) {
      new_gene = new_gene.variation_of_fm(&own_graph);
    }
    children_gene.push_back(new_gene);

    // cout << "3" << endl;
  }
  // cout << "4" << endl;

  for (int i = 0; i < child; i ++) {
    gene_vector[i] = children_gene[i];
  }

  /*for (int j = 0; j < child; j ++) {
    gene_vector[j] = gas_merge().mutate(own_graph);
    // if (j ==0) {
    // 	cout << "before mut soln: " << gene_vector[0].get_soln_value() << endl;
    // 	cout << "before mut calc: " << calc_aux(own_graph, gene_vector[0].get_gene()) << endl;
    // }
    //gene_vector[j] = gas_roulette_merge().mutate();
    // cout << "before local opt : " << gene_vector[j].get_soln_value() << endl;
    // int after_val = Gene(own_graph, gene_vector[j].get_gene()).get_soln_value();
    // cout << "after local opt : " << after_val << endl;
    // cout << "local opt check : " << gene_vector[j].get_soln_value() << endl;
    // cout << "check : " << (after_val == gene_vector[j].get_soln_value()) << endl;
    }
    gene_vector[0] = gene_vector[0].local_opt(own_graph);
    //cout << "here2" << endl;
    */


  // return *this;
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
