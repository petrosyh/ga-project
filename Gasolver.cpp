#include "Gasolver.h"


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

pair<Gene, int> Gasolver::selection() {
    srand(static_cast<unsigned int>(clock()));
    int selector = rand()%size;
    return make_pair(gene_vector[selector], selector);
}

//assume values are sorted.
pair<Gene, int> Gasolver::roulette_selection() {
    int whole_sum = get_value_sum();
    vector<int> value_acc = get_value_acc();
    
    assert(whole_sum == value_acc[size -1]);
    
    srand(static_cast<unsigned int>(clock()));
    int selector = rand()%whole_sum;
    
    for (int ith = 0; ith < size; ith ++) {
        if (selector < value_acc[ith]) {
            return make_pair(gene_vector[ith], ith);
        }
    }
    return make_pair(gene_vector[size - 1], size - 1);
}

Gene Gasolver::gas_roulette_merge() {
    pair<Gene, int> sel1 = roulette_selection();
    pair<Gene, int> sel2 = roulette_selection();

    Gene g1 = sel1.first;
    Gene g2 = sel2.first;

    int ith_1 = sel1.second;
    int ith_2 = sel2.second;

    int gene_size = g1.get_gene().size();
    
    vector<bool> new_gene1;
    Gene ret;

    for (int i = 0; i < gene_size; i++) {
        if (i % 2 == 0) {
            new_gene1.push_back(gene_vector[ith_1].get_gene()[i]);
        } else {
            new_gene1.push_back(gene_vector[ith_2].get_gene()[i]);
        }
    }
    ret = Gene(own_graph, new_gene1);

    return ret;
}
Gene Gasolver::gas_merge() {
    pair<Gene, int> sel1 = selection();
    pair<Gene, int> sel2 = selection();
    pair<Gene, int> sel3 = selection();
    pair<Gene, int> sel4 = selection();
    
    Gene g1 = sel1.first;
    Gene g2 = sel2.first;
    Gene g3 = sel3.first;
    Gene g4 = sel4.first;

    int winner1, winner2, looser1, looser2;

    int gene_size = g1.get_gene().size();
    vector<bool> new_gene1;
    Gene ret;

    if (g1.get_soln_value() > g2.get_soln_value()) {
        looser1 = sel2.second;
        winner1 = sel1.second;
    } else if (g1.get_soln_value() < g2.get_soln_value()) {
        looser1 = sel1.second;
        winner1 = sel2.second;
    } else {
        looser1 = sel1.second;
        winner1 = sel2.second;
    }

    if (g3.get_soln_value() > g4.get_soln_value()) {
        looser2 = sel4.second;
        winner2 = sel3.second;
    } else if (g3.get_soln_value() < g4.get_soln_value()) {
        looser2 = sel3.second;
        winner2 = sel4.second;
    } else {
        looser2 = sel3.second;
        winner2 = sel4.second;
    }

    for (int i = 0; i < gene_size; i++) {
        if (i % 2 == 0) {
            new_gene1.push_back(gene_vector[winner1].get_gene()[i]);
        } else {
            new_gene1.push_back(gene_vector[winner2].get_gene()[i]);
        }
    }
    ret = Gene(own_graph, new_gene1);
    
    gene_vector[looser1] = ret;
    gene_vector[looser2] = ret;
    //for (auto i : new_gene) {
    //    cout << i;
    //}
    //cout << endl;

    return ret;
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


Gasolver Gasolver::generation(int child) {
    vector<int> values;
    // vector<Gene> new_children;
    // int minstate;
    Gene g;

    // cout << "before mut soln: " << gene_vector[0].get_soln_value() << endl;
    // cout << "before mut calc: " << calc_aux(own_graph, gene_vector[0].get_gene()) << endl;
    sort(gene_vector.begin(), gene_vector.end());
    for (int j = 0; j < child; j ++) {
      gene_vector[j] = gas_roulette_merge().mutate(own_graph);
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
    
    
    
    return *this;
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

vector<double> Gasolver::fitnesses() {
    vector<int> values = get_all_value();

    int min = minval(values);
    int max = maxval(values);
    vector<double> ret;
    for (auto iter : gene_vector) {
        ret.push_back((min - iter.get_soln_value() + min - max)/(size - 1));
    }
    return ret;
}
