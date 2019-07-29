#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "network.h"
#include "snake.h"


static NetworkParams *population;


static int genetic_init_population(int pop){
	population=(NetworkParams*)malloc(pop*sizeof(NetworkParams));
	if(!population){
		return -1;
	}

	int i, j, k;
	for(i=0;i<pop;++i){
		population[i].score=0;
		population[i].act_func_L1=ADALINE;
		population[i].act_func_L2=SIGMOID;

		for(j=0;j<6;++j){
			for(k=0;k<6;++k){
				population[i].wL1[j][k]=rand()%100;
			}
		}
		for(j=0;j<3;++j){
			for(k=0;k<6;++k){
				population[i].wL1[j][k]=rand()%100;
			}
		}
	}
	return 0;
}

static void genetic_run_games(int pop){
	int i, s;
	float in[6];
	float out[3];
	SnakeGame game;


	for(i=0;i<pop;++i){
		snake_init(&game);
		network_init(&population[i]);

		for(s=0;s<2000;++s){
			if(!game.status){
				break;
			}

			snake_getparam(&game, in);
			network_output(in, out);
    		
		    if(out[1]>out[0] && out[1]>out[2]){
		    	snake_right(&game);
		    }else if(out[2]>out[0] && out[2]>out[1]){
		    	snake_left(&game);
		    }
			snake_step(&game);
		}
		population[i].score=game.scores;
	}
}

static void genetic_selection(int mut){
	int best[5];

	//TODO




}

static void genetic_store_best(int pop){
	FILE *fd=fopen("netdat", "wb");
	if(!fd){
		printf("ERROR: genetic_store_best: fopen\n");
		exit(1);
	}

	int best=0;
	int score=population[0].score;
	int i;
	for(i=1;i<pop;++i){
		if(population[i].score>score){
			best=i;
			score=population[i].score;
		}
	}

	fwrite(&population[best], sizeof(NetworkParams), 1, fd);
	fclose(fd);
}


int genetic_run(int iter, int pop, float mut){
	if(iter<1 || pop<1){
		return -1;
	}

	srand(time(0));
	genetic_init_population(pop);

	while(iter--){
		genetic_run_games(pop);
		genetic_selection(mut);
	}
	
	genetic_store_best(pop);
	return 0;
}

/*

static void genetic_mutation(){
	int i;
	for(i=0;i<POPULATION/10;++i){
		int x=rand()%POPULATION;
		int y=rand()%6;
		population[x].w1[y] *= 0.9;
		population[x].w2[y] *= 0.9;
		population[x].w3[y] *= 0.9;

		x=rand()%POPULATION;
		y=rand()%6;
		population[x].w1[y] *= 1.1;
		population[x].w2[y] *= 1.1;
		population[x].w3[y] *= 1.1;
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
*/
