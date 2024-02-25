#include <iostream>

state_map_t *map1, *map2;
abstraction_t *abst1, *abst2;

void init_heuristica() {
	FILE *f1 = fopen("part1.pdb", "r");
	FILE *f2 = fopen("part2.pdb", "r");

	if (f1 == NULL || f2 == NULL) {
		std::cerr << "Error: No se pudieron abrir los PDB" << std::endl;
		exit(1);
	}

	// Se leen los mapas de los PDBs
	map1 = read_state_map(f1);
	map2 = read_state_map(f2);

	fclose(f1);
	fclose(f2);

	// Se leen las abstracciones de los PDBs para poder calcular la heuristica
	abst1 = read_abstraction_from_file("part1.abst");
	abst2 = read_abstraction_from_file("part2.abst");
}

unsigned heuristica(state_t estado) {
	// Se obtienen los estados abstractos de cada PDB
	state_t s1, s2;
	abstract_state(abst1, &estado, &s1);
	abstract_state(abst2, &estado, &s2);

	// Se obtienen las distancias a los estados abstractos
	const int *dist1 = state_map_get(map1, &s1);
	const int *dist2 = state_map_get(map2, &s2);

	// Estas distancias no deberian ser nulas
	if (dist1 == NULL || dist2 == NULL) {
		std::cerr << "Error: No se encontro la distancia en el PDB" << std::endl;
		exit(1);
	}

	// Se retorna el maximo de las distancias
	return std::max(
		*dist1,
		*dist2
	);
}