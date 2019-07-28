#include "genetic.h"
#include "network.h"
#include "snake.h"
#include <stdlib.h>
#include <string.h>

#define POPULATION 		100
#define GENERATIONS		1000
#define MUTATION 		0.1

static Chromosome population[POPULATION];



static void genetic_init(){
	int i, j;
	for(i=0;i<POPULATION;++i){
		for(j=0;j<6;++j){
			population[i].w1[j]=rand()%100;
			population[i].w2[j]=rand()%100;
			population[i].w3[j]=rand()%100;
		}
		population[i].score=0;
	}
}

static void genetic_fitness(){
	int i, j;
	Network net;
	SnakeGame game;

	for(i=0;i<POPULATION;++i){
		network_init(&net, population[i].w1, population[i].w2, population[i].w3);
		snake_init(&game);

		for(j=0;j<20000;++j){
			if(!game.status) break;

			float in[6];
    		float out[3];
    		snake_getparam(&game, in);
    		network_output(&net, in, out);

		    if(out[1]>out[0] && out[1]>out[2]) snake_right(&game);
    		else if(out[2]>out[0] && out[2]>out[1]) snake_left(&game);
			snake_step(&game);
		}
	}
}

static Chromosome* genetic_get_best(){
	int i, max_score=population[0].score, best_i=0;
	for(i=1;i<POPULATION;++i){
		if(population[i].score>max_score){
			best_i=i;
			max_score=population[i].score;
		}
	}
	return &population[best_i];
}

static void genetic_mutation(){
	int i;
	for(i=0;i<POPULATION/10;++i){
		int x=rand()%POPULATION;
		int y=rand()%6;
		population[x].w1[y] *= 0.9;
		population[x].w2[y] *= 0.8;
		population[x].w3[y] *= 0.95;

		x=rand()%POPULATION;
		y=rand()%6;
		population[x].w1[y] *= 1.1;
		population[x].w2[y] *= 1.2;
		population[x].w3[y] *= 1.05;
	}
}

static void genetic_selection(){
	Chromosome* c=genetic_get_best();

	int i;
	for(i=0;i<POPULATION/10;++i){
		int r=rand()%POPULATION;

		memcpy(&population[r], c, sizeof(Chromosome));

		c=genetic_get_best();
	}
}

Chromosome* genetic_run(){
	genetic_init();

	int i;
	for(i=0;i<GENERATIONS;++i){
		genetic_fitness();
		genetic_selection();
		genetic_mutation();
	}
	return genetic_get_best();
}
