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

Gasolver Gasolver::generation(int child) {
    vector<int> values;
    vector<Gene> new_children;
    int minstate;
    Gene g;
    
    sort(gene_vector.begin(), gene_vector.end());
    for (int j = 0; j < child; j ++) {
      gene_vector[j] = gas_merge().mutate();
      // cout << "before local opt : " << gene_vector[j].get_soln_value() << endl;
      gene_vector[j] = gene_vector[j].local_opt(own_graph);
      // int after_val = Gene(own_graph, gene_vector[j].get_gene()).get_soln_value();
      // cout << "after local opt : " << after_val << endl;
      // cout << "local opt check : " << gene_vector[j].get_soln_value() << endl;
      // cout << "check : " << (after_val == gene_vector[j].get_soln_value()) << endl;
    }
    //cout << "here2" << endl;
    
    //for (auto iter: gene_vector) {
    //    cout << iter.get_soln_value() << " ";
    //}
    //cout << endl;
    
    
    return *this;
}

vector<int> Gasolver::get_all_value() {
    vector<int> ret;
    for (auto iter : gene_vector) {
        ret.push_back(iter.get_soln_value());
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
