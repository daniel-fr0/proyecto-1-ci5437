#include <iostream>

state_map_t *esqW_map, *esqY_map, *borW_map, *borY_map;
abstraction_t *esqW_abst, *esqY_abst, *borW_abst, *borY_abst;

void init_heuristica() {
	FILE *esquinasW = fopen("esquinasW.pdb", "r");
	FILE *esquinasY = fopen("esquinasY.pdb", "r");
	FILE *bordesW = fopen("bordesW.pdb", "r");
	FILE *bordesY = fopen("bordesY.pdb", "r");

	// Se leen los mapas de los PDBs
	esqW_map = read_state_map(esquinasW);
	esqY_map = read_state_map(esquinasY);
	borW_map = read_state_map(bordesW);
	borY_map = read_state_map(bordesY);

	fclose(esquinasW);
	fclose(esquinasY);
	fclose(bordesW);
	fclose(bordesY);

	// Se leen las abstracciones de los PDBs para poder calcular la heuristica
	esqW_abst = read_abstraction_from_file("esquinasW.abst");
	esqY_abst = read_abstraction_from_file("esquinasY.abst");
	borW_abst = read_abstraction_from_file("bordesW.abst");
	borY_abst = read_abstraction_from_file("bordesY.abst");
}

unsigned heuristica(state_t estado) {
	// Se obtienen los estados abstractos de cada PDB
	state_t esqW, esqY, borW, borY;
	abstract_state(esqW_abst, &estado, &esqW);
	abstract_state(esqY_abst, &estado, &esqY);
	abstract_state(borW_abst, &estado, &borW);
	abstract_state(borY_abst, &estado, &borY);

	// Se obtienen las distancias a los estados abstractos
	const int *esqW_dist = state_map_get(esqW_map, &esqW);
	const int *esqY_dist = state_map_get(esqY_map, &esqY);
	const int *borW_dist = state_map_get(borW_map, &borW);
	const int *borY_dist = state_map_get(borY_map, &borY);

	// Estas distancias no deberian ser nulas
	if (esqW_dist == NULL || esqY_dist == NULL || borW_dist == NULL || borY_dist == NULL) {
		std::cerr << "Error: No se encontro la distancia en el PDB" << std::endl;
		exit(1);
	}

	// Se retorna el maximo de las distancias
	return std::max(
		std::max(*esqW_dist, *esqY_dist),
		std::max(*borW_dist, *borY_dist)
	);
}