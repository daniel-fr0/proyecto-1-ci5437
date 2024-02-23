#include<iostream>
#include<vector>
#include"priority_queue.hpp"
#include<climits>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

using namespace std;

int a_estrella(state_t *init){
    PriorityQueue<state_t> q;
    state_t estado, hijo;
    int h, g, ruleid;
    ruleid_iterator_t iter;
    state_map_t *map = new_state_map();
    // Agrega el estado inicial a el state map y a la cola de prioridad 
    state_map_add(map, init, 0);
    q.Add(heuristica(*init), 0, *init);
    
    // Buscamos el estado objetivo hasta que la cola este vacia
    while( !q.Empty()) {
        // Tomamos el estado con la prioridad mas alta
        estado = q.Top();

        cout << "Estado actual: " << endl;
        print_state(stdout, &estado);
        cout << endl;

        // Tomamos el costo del estado con la prioridad mas alta
        g = q.TopG();

        q.Pop();

        // Pasamos al siguiente elemento del while si el mejor costo conocido
        // es menor que el costo actual
        const int *best_g = state_map_get(map,&estado);
        cout << "Best g = " << *best_g << endl;
        assert(best_g != NULL);
        if(*best_g < g){
            continue;
        }
        // Actualizamos el costo del estado actual en el mapa
        state_map_add(map, &estado, g);

        // Si el estado actual es el objetivo, retornamos el costo para alcanzarlo
        if (is_goal(&estado)){
            return g;
        }

        int hist;
        hist = init_history;

        // Iteramos por las posibles reglas que pueden ser aplicadas a el estado actual
        init_fwd_iter(&iter,&estado);     
        while(( ruleid = next_ruleid(&iter)) >= 0 ) {
            if (!fwd_rule_valid_for_history(hist,ruleid)) continue;
            next_fwd_history(hist,ruleid);

            // Aplicamos la regla al estado actual para generar un estado hijo
            apply_fwd_rule( ruleid, &estado, &hijo );
            h = heuristica(hijo);
            if(h < INT_MAX) {
                // Si el estado hijo es alcanzable desde el estado objetivo, se calcula el costo para
                // alcanzar el estado hijo
                int hijo_g = g + get_fwd_rule_cost(ruleid);
                int *anterior_hijo_g = state_map_get(map, &hijo);

                // Si el hijo no ha sido explorado antes, o si el nuevo costo es menor que el mejor conocido, 
                // se actualiza el costo en el mapa y se agrega el hijo a la cola de prioridad
                if((anterior_hijo_g == NULL) || (*anterior_hijo_g > hijo_g)) {
                    state_map_add(map, &hijo, hijo_g);
                    q.Add(hijo_g + h, hijo_g, hijo);
                }
            }
        }
    }
    return -1; // Sin camino
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
    int costo = a_estrella(&init);

    if (costo == -1){
        cout << "No se encontro camino" << endl;
    } else {
        cout << "Costo del camino: " << costo << endl;
    }

    return 0;
}