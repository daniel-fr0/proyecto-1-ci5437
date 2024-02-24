#include<iostream>
#include<vector>
#include"priority_queue.hpp"
#include<climits>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

using namespace std;

pair<bool, int> f_bounded_dfs_visit(int bound, int g);

state_t state;
vector<int> path;

int ida_estrella(state_t *init){
    state = *init;
    int bound = heuristica(state);

    while (true){
        pair<bool, int> p = f_bounded_dfs_visit(bound, 0);
        if (p.first) return p.second;
        bound = p.second;
    }
}

pair<bool, int> f_bounded_dfs_visit(int bound, int g){
    int h = heuristica(state);
    int f = g + h;
    if (f > bound) return make_pair(false, f);
    if (h == 0) return make_pair(true, g);

    int t = INT_MAX;
    ruleid_iterator_t iter;
    int ruleid;
    state_t child, current_state = state;
    
    int hist;
    hist = init_history;

    init_fwd_iter(&iter, &state);
    while((ruleid = next_ruleid(&iter)) >= 0){
        if (!fwd_rule_valid_for_history(hist, ruleid)) continue;
        next_fwd_history(hist, ruleid);

        int cost = g + get_fwd_rule_cost(ruleid);
        apply_fwd_rule(ruleid, &state, &child);
        state = child;

        if (heuristica(child) < INT_MAX){
            path.push_back(ruleid);
            pair<bool, int> p = f_bounded_dfs_visit(bound, cost);
            if (p.first) return p;
            if (p.second < t) t = p.second;
            path.pop_back();
        }
        state = current_state;
    }

    return make_pair(false, t);
}


int main(int argc, char const *argv[]) {
    if (argc < 2){
        cout<<"Uso: "<<argv[0]<<" <archivo con estado inicial>"<<endl;
        return 1;
    }

    // Abrimos el archivo con el estado inicial
    ifstream file(argv[1]);

    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    // Se lee el archivo en un string
    string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Se copia el string en un buffer de char*
    char* buffer = new char[contents.length() + 1];
    std::copy(contents.begin(), contents.end(), buffer);
    buffer[contents.length()] = '\0'; // Caracter nulo al final del buffer

    file.close();

    state_t init;
    read_state(buffer, &init);

    // Liberamos el buffer
    delete[] buffer;

    cout << "Construyendo heuristica..." << endl;
    init_heuristica();
    cout << "Buscando camino..." << endl;
    int costo = ida_estrella(&init);

    if (costo == -1){
        cout << "No se encontro camino" << endl;
    } else {
        cout << "Costo del camino minimo encontrado: " << costo << endl;

        for (std::vector<int>::size_type i = 0; i < path.size(); i++){
            cout << path[i] << " ";
        }
        cout << endl;
    }

    return 0;
}