#pragma once

typedef struct{
	float w1[6];
	float w2[6];
	float w3[6];
	int score;
} Chromosome;

Chromosome* genetic_run();
