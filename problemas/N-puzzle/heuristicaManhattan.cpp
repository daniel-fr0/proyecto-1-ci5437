#include <iostream>
#include <sstream>
#include <array>

// tabla de distancias Manhattan para el 15-puzzle
int manhattan15[16][16];
// tabla de distancias Manhattan para el 24-puzzle
int manhattan24[25][25];

int size = -1;

void init_heuristica() {
	// Se inicializan la tabla de distancias Manhattan para el 15-puzzle
	for (int ficha = 0; ficha < 16; ficha++) {
		for (int pos = 0; pos < 16; pos++) {
			if (ficha == 0 || ficha == pos) {
				manhattan15[ficha][pos] = 0;
				continue;
			}
			int x1 = pos / 4;
			int y1 = pos % 4;
			int x2 = ficha / 4;
			int y2 = ficha % 4;
			manhattan15[ficha][pos] = abs(x1 - x2) + abs(y1 - y2);
		}
	}

	// Se inicializan la tabla de distancias Manhattan para el 24-puzzle
	for (int ficha = 0; ficha < 25; ficha++) {
		for (int pos = 0; pos < 25; pos++) {
			if (ficha == 0 || ficha == pos) {
				manhattan24[ficha][pos] = 0;
				continue;
			}
			int x1 = pos / 5;
			int y1 = pos % 5;
			int x2 = ficha / 5;
			int y2 = ficha % 5;
			manhattan24[ficha][pos] = abs(x1 - x2) + abs(y1 - y2);
		}
	}

}

void get_puzzle_size(state_t estado) {
	// obtengo el estado en forma de string
	char buffer[100];
	sprint_state(buffer, 100, &estado);

	// reviso si tiene 16 variables o 25
	std::istringstream iss(buffer);
	for (std::string s; iss >> s;) size++;
}

std::array<int, 15> estado_de_15_puzzle(state_t estado) {
	std::array<int, 15> fichas;

	char buffer[100];
	sprint_state(buffer, 100, &estado);

	std::istringstream iss(buffer);
	for (int i = 0; i < 15; i++) {
		iss >> fichas[i];
	}

	return fichas;
}

std::array<int, 24> estado_de_24_puzzle(state_t estado) {
	std::array<int, 24> fichas;

	char buffer[100];
	sprint_state(buffer, 100, &estado);
	
	std::istringstream iss(buffer);
	for (int i = 0; i < 24; i++) {
		iss >> fichas[i];
	}

	return fichas;
}

unsigned heuristica(state_t estado) {
	if (size == -1) get_puzzle_size(estado);

	if (size != 15 && size != 24) {
		std::cerr << "Error: Tamaño de puzzle no soportado" << std::endl;
		exit(1);
	}

	if (size == 15) {
		std::array<int, 15> fichas = estado_de_15_puzzle(estado);
		int h = 0;
		for (int i = 0; i < 15; i++) {
			if (fichas[i] == 0) continue;
			h += manhattan15[fichas[i]][i];
		}
		return h;
	}

	std::array<int, 24> fichas = estado_de_24_puzzle(estado);
	int h = 0;
	for (int i = 0; i < 24; i++) {
		if (fichas[i] == 0) continue;
		h += manhattan24[fichas[i]][i];
	}
	return h;
}