#include<iostream>
#include<vector>
#include"priority_queue.hpp"
#include<climits>

using namespace std;

int a_estrella(state_t *init, unsigned (*heuristica) (state_t)){
    PriorityQueue<state_t> q;
    state_t estado, hijo;
    int d, ruleid;
    ruleid_iterator_t iter;
    state_map_t *map = new_state_map();
    // Agrega el estado inicial a el state map y a la cola de prioridad 
    state_map_add(map, init, 0);
    //q.Add(heuristic(*init), 0, *init);
    q.Add(0, 0, *init);
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

        // Si el estado actual es el objetivo, retornamos el costo para alcanzarlo
        if (is_goal(&estado)){
            return d;
        }
        // Pasamos al siguiente elemento del while si el mejor costo conocido
        // es menor que el costo actual
        const int *best_dist = state_map_get(map,&estado);
        if(*best_dist < d){
            continue;
        }
        // Actualizamos el costo del estado actual en el mapa
        state_map_add(map, &estado, d);
        // Iteramos por las posibles reglas que pueden ser aplicadas a el estado actual
        init_fwd_iter(&iter,&estado);     
        while(( ruleid = next_ruleid(&iter)) >= 0 ) {
            // Aplicamos la regla al estado actual para generar un estado hijo
            apply_fwd_rule( ruleid, &estado, &hijo );
            // Si el estado hijo es alcanzable desde el estado objetivo, se calcula el costo para
            // alcanzar el estado hijo
            int hijo_d = d + get_fwd_rule_cost(ruleid);
            int *ant_hijo_d = state_map_get(map, &hijo);

            if(heuristica(hijo) < INT_MAX) {
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
