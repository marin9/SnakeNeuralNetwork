#pragma once
#include "network.h"

typedef struct{
	int iterations;
	int population;
	float mutation;
} GeneticParams;


int genetic_run(NetworkParams *pn, GeneticParams *pg);
