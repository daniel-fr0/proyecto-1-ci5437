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
    int d, ruleid;
    ruleid_iterator_t iter;
    state_map_t *map = new_state_map();
    // Agrega el estado inicial a el state map y a la cola de prioridad 
    state_map_add(map, init, 0);
    q.Add(heuristica(*init), 0, *init);
    // q.Add(0, 0, *init);
    int test = 5000;  // Esto es solo para ver los primeros estados y ver como avanza,
                      // Se puede quitar esto y la condicion "test != 0" del while
                      // una vez funcione.
    // Buscamos el estado objetivo hasta que la cola este vacia
    while( !q.Empty() && test != 0) {
        test--;
        // Tomamos el estado con la prioridad mas alta
        d = q.CurrentPriority();
        
        cout<<d<<endl;
        printf("metiste: ");
        print_state(stdout,&estado);
        printf("\n");

        estado = q.Top();
        q.Pop();

        // Pasamos al siguiente elemento del while si el mejor costo conocido
        // es menor que el costo actual
        const int *best_dist = state_map_get(map,&estado);
        if(*best_dist < d){
            continue;
        }
        // Actualizamos el costo del estado actual en el mapa
        state_map_add(map, &estado, d);

        // Si el estado actual es el objetivo, retornamos el costo para alcanzarlo
        if (is_goal(&estado)){
            return d;
        }

        // Iteramos por las posibles reglas que pueden ser aplicadas a el estado actual
        init_fwd_iter(&iter,&estado);     
        while(( ruleid = next_ruleid(&iter)) >= 0 ) {
            // Aplicamos la regla al estado actual para generar un estado hijo
            apply_fwd_rule( ruleid, &estado, &hijo );
            
            if(heuristica(hijo) < INT_MAX) {
                // Si el estado hijo es alcanzable desde el estado objetivo, se calcula el costo para
                // alcanzar el estado hijo
                int hijo_d = d + get_fwd_rule_cost(ruleid);
                int *ant_hijo_d = state_map_get(map, &hijo);

                // Si el hijo no ha sido explorado antes, o si el nuevo costo es menor que el mejor conocido, 
                // se actualiza el costo en el mapa y se agrega el hijo a la cola de prioridad
                if((ant_hijo_d == NULL) || (*ant_hijo_d > hijo_d)) {
                    state_map_add(map, &hijo, hijo_d);
                    q.Add(hijo_d + heuristica(hijo),hijo_d,hijo);
                }
            }
        }
    }
    return 0; // Sin camino
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
    cout << "Heuristica del estado inicial: " << heuristica(init) << endl;
    a_estrella(&init);

    return 0;
}