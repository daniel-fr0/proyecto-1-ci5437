#include <iostream>

state_map_t *esq_map, *borW_map, *borY_map;
abstraction_t *esq_abst, *borW_abst, *borY_abst;

void init_heuristica() {
	FILE *esquinas = fopen("ESQUINAS.pdb", "r");
	FILE *bordesW = fopen("bordesW.pdb", "r");
	FILE *bordesY = fopen("bordesY.pdb", "r");

	if (esquinas == NULL || bordesW == NULL || bordesY == NULL) {
		std::cerr << "Error: No se pudieron abrir los PDB" << std::endl;
		exit(1);
	}

	// Se leen los mapas de los PDBs
	esq_map = read_state_map(esquinas);
	borW_map = read_state_map(bordesW);
	borY_map = read_state_map(bordesY);

	fclose(esquinas);
	fclose(bordesW);
	fclose(bordesY);

	// Se leen las abstracciones de los PDBs para poder calcular la heuristica
	esq_abst = read_abstraction_from_file("ESQUINAS.abst");
	borW_abst = read_abstraction_from_file("bordesW.abst");
	borY_abst = read_abstraction_from_file("bordesY.abst");
}

unsigned heuristica(state_t estado) {
	// Se obtienen los estados abstractos de cada PDB
	state_t esq, borW, borY;
	abstract_state(esq_abst, &estado, &esq);
	abstract_state(borW_abst, &estado, &borW);
	abstract_state(borY_abst, &estado, &borY);

	// Se obtienen las distancias a los estados abstractos
	const int *esq_dist = state_map_get(esq_map, &esq);
	const int *borW_dist = state_map_get(borW_map, &borW);
	const int *borY_dist = state_map_get(borY_map, &borY);

	// Estas distancias no deberian ser nulas
	if (esq_dist == NULL || borW_dist == NULL || borY_dist == NULL) {
		std::cerr << "Error: No se encontro la distancia en el PDB" << std::endl;
		exit(1);
	}

	// Se retorna el maximo de las distancias
	return std::max(
		*esq_dist,
		std::max(*borW_dist, *borY_dist)
	);
}