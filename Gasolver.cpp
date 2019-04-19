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
        i++;
        if (ret > iter) {
            ret = iter;
            j = i;
        }   
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

int maxwhere(vector<int> values) {
    int ret = INT_MIN;
    int i = 0;
    int j = 0;
    for (auto iter : values) {
        i++;
        if (ret < iter) {
            ret = iter;
            j = i;
        }   
    }
    return j;
}


vector<Gene> Gasolver::get_gene_vector() {
    return gene_vector;
}

int Gasolver::get_gas_size() {
    return size;
}

Gene Gasolver::selection() {
    int selector = rand()%size;
    return gene_vector[selector];
}

Gene Gasolver::gas_merge() {
    Gene g1 = selection();
    Gene g2 = selection();
    int gene_size = g1.get_gene().size();
    vector<bool> new_gene;

    for (int i = 0; i < gene_size; i++) {
        if (i % 2 == 0) {
            new_gene.push_back(g1.get_gene()[i]);
        } else {
            new_gene.push_back(g2.get_gene()[i]);
        }
    }

    //for (auto i : new_gene) {
    //    cout << i;
    //}
    //cout << endl;

    return Gene(own_graph, new_gene);
}

Gasolver Gasolver::generation(int child) {
    vector<int> values;
    vector<Gene> new_children;
    int minstate;
    Gene g;
    for (int i = 0; i < child; i++) {
        values = get_all_value();
        minstate = minwhere(values);
        g = gas_merge().mutate();
        gene_vector[minstate] = g;
    }

    
    //sort(gene_vector.begin(), gene_vector.end());
    //for (int j = 0; j < child; j ++) {
    //    gene_vector[gene_vector.size() - j - 1] = new_children[j];
    //}
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