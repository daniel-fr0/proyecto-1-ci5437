#include<iostream>
#include<vector>
#include"priority_queue.hpp"
#include<climits>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <atomic>
#include <chrono>
#include <future>

using namespace std;

atomic<bool> stop(false);

pair<bool, int> f_bounded_dfs_visit(state_t state, int bound, int g);

vector<int> path;
int explored_distance, explored_nodes, total_nodes;

int ida_estrella(state_t *init){
    int bound = heuristica(*init);
    explored_distance = 0;
    explored_nodes = 0;
    total_nodes = 0;

    while (!stop){
        pair<bool, int> p = f_bounded_dfs_visit(*init, bound, 0);
        if (p.first) return p.second;
        bound = p.second;
    }
    return -1;
}

pair<bool, int> f_bounded_dfs_visit(state_t state, int bound, int g){
    if (g > explored_distance) {
        cout << explored_nodes << " estados en distancia " << explored_distance << endl;
        explored_distance = g;
        explored_nodes = 0;
    }

    explored_nodes++;
    total_nodes++;

    int h = heuristica(state);
    int f = g + h;
    if (f > bound) return make_pair(false, f);
    if (is_goal(&state)) {
        cout << explored_nodes << " estados en distancia " << explored_distance << endl;
        cout << total_nodes << " estados totales" << endl;
        return make_pair(true, g);
    }

    int t = INT_MAX;
    ruleid_iterator_t iter;
    int ruleid;
    state_t child;
    
    int hist;
    hist = init_history;

    init_fwd_iter(&iter, &state);
    while((ruleid = next_ruleid(&iter)) >= 0 && !stop){
        if (!fwd_rule_valid_for_history(hist, ruleid)) continue;
        hist = next_fwd_history(hist, ruleid);

        int cost = g + get_fwd_rule_cost(ruleid);
        apply_fwd_rule(ruleid, &state, &child);

        if (heuristica(child) < INT_MAX){
            path.push_back(ruleid);
            pair<bool, int> p = f_bounded_dfs_visit(child, bound, cost);
            if (p.first) return p;
            if (p.second < t) t = p.second;
            path.pop_back();
        }
    }

    return make_pair(false, t);
}


int main(int argc, char const *argv[]) {
    if (argc < 2){
        cout<<"Uso: "<<argv[0]<<" <archivo con estado inicial>"<<endl;
        return 1;
    }

    int TIME_LIMIT = 300; // 5 minutos por defecto

    // Tiempo limite opcional
    if (argc > 2){
        TIME_LIMIT = stoi(argv[2]);
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

    future<int> future = async(launch::async, ida_estrella, &init);

    if (future.wait_for(chrono::seconds(TIME_LIMIT)) == future_status::timeout){
        stop = true;
        cout << "Tiempo de ejecucion excedido de " << TIME_LIMIT / 60 << " minutos" << endl;
        cout << "No se encontro camino" << endl;
    } else {
        int costo = future.get();
        cout << "Costo del camino minimo encontrado: " << costo << endl;

        for (std::vector<int>::size_type i = 0; i < path.size(); i++){
            cout << path[i] << " ";
        }
        cout << endl;
    }

    return 0;
}