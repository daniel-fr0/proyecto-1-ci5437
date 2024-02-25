#include <iostream>

state_map_t *map1, *map2, *map3, *map4, *map5, *map6;
abstraction_t *abst1, *abst2, *abst3, *abst4, *abst5, *abst6;

void init_heuristica() {
	FILE *f1 = fopen("part1.pdb", "r");
	FILE *f2 = fopen("part2.pdb", "r");
	FILE *f3 = fopen("part3.pdb", "r");
	FILE *f4 = fopen("part4.pdb", "r");
	FILE *f5 = fopen("part5.pdb", "r");
	FILE *f6 = fopen("part6.pdb", "r");

	if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL || f5 == NULL || f6 == NULL) {
		std::cerr << "Error: No se pudieron abrir los PDB" << std::endl;
		exit(1);
	}

	// Se leen los mapas de los PDBs
	map1 = read_state_map(f1);
	map2 = read_state_map(f2);
	map3 = read_state_map(f3);
	map4 = read_state_map(f4);
	map5 = read_state_map(f5);
	map6 = read_state_map(f6);

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	fclose(f5);
	fclose(f6);

	// Se leen las abstracciones de los PDBs para poder calcular la heuristica
	abst1 = read_abstraction_from_file("part1.abst");
	abst2 = read_abstraction_from_file("part2.abst");
	abst3 = read_abstraction_from_file("part3.abst");
	abst4 = read_abstraction_from_file("part4.abst");
	abst5 = read_abstraction_from_file("part5.abst");
	abst6 = read_abstraction_from_file("part6.abst");
}

unsigned heuristica(state_t estado) {
	// Se obtienen los estados abstractos de cada PDB
	state_t s1, s2, s3, s4, s5, s6;
	abstract_state(abst1, &estado, &s1);
	abstract_state(abst2, &estado, &s2);
	abstract_state(abst3, &estado, &s3);
	abstract_state(abst4, &estado, &s4);
	abstract_state(abst5, &estado, &s5);
	abstract_state(abst6, &estado, &s6);

	// Se obtienen las distancias a los estados abstractos
	const int *dist1 = state_map_get(map1, &s1);
	const int *dist2 = state_map_get(map2, &s2);
	const int *dist3 = state_map_get(map3, &s3);
	const int *dist4 = state_map_get(map4, &s4);
	const int *dist5 = state_map_get(map5, &s5);
	const int *dist6 = state_map_get(map6, &s6);

	// Estas distancias no deberian ser nulas
	if (dist1 == NULL || dist2 == NULL || dist3 == NULL || dist4 == NULL || dist5 == NULL || dist6 == NULL) {
		std::cerr << "Error: No se encontro la distancia en el PDB" << std::endl;
		exit(1);
	}

	// Se retorna la suma de las distancias
	return *dist1 + *dist2 + *dist3 + *dist4 + *dist5 + *dist6;
}