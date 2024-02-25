#include <iostream>

state_map_t *map1, *map2, *map3;
abstraction_t *abst1, *abst2, *abst3;

void init_heuristica() {
	FILE *f1 = fopen("part1.pdb", "r");
	FILE *f2 = fopen("part2.pdb", "r");
	FILE *f3 = fopen("part3.pdb", "r");

	if (f1 == NULL || f2 == NULL || f3 == NULL) {
		std::cerr << "Error: No se pudieron abrir los PDB" << std::endl;
		exit(1);
	}

	// Se leen los mapas de los PDBs
	map1 = read_state_map(f1);
	map2 = read_state_map(f2);
	map3 = read_state_map(f3);

	fclose(f1);
	fclose(f2);
	fclose(f3);

	// Se leen las abstracciones de los PDBs para poder calcular la heuristica
	abst1 = read_abstraction_from_file("part1.abst");
	abst2 = read_abstraction_from_file("part2.abst");
	abst3 = read_abstraction_from_file("part3.abst");
}

unsigned heuristica(state_t estado) {
	// Se obtienen los estados abstractos de cada PDB
	state_t s1, s2, s3;
	abstract_state(abst1, &estado, &s1);
	abstract_state(abst2, &estado, &s2);
	abstract_state(abst3, &estado, &s3);

	// Se obtienen las distancias a los estados abstractos
	const int *dist1 = state_map_get(map1, &s1);
	const int *dist2 = state_map_get(map2, &s2);
	const int *dist3 = state_map_get(map3, &s3);

	// Estas distancias no deberian ser nulas
	if (dist1 == NULL || dist2 == NULL || dist3 == NULL) {
		std::cerr << "Error: No se encontro la distancia en el PDB" << std::endl;
		exit(1);
	}

	// Se retorna el maximo de las distancias
	return std::max(
		std::max(*dist1, *dist2),
		*dist3
	);
}