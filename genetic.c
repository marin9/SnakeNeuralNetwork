#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "snake.h"


static NetworkParams *population;
static NetworkParams *population_tmp;


static int genetic_init_population(int pop){
	population=(NetworkParams*)malloc(pop*sizeof(NetworkParams));
	population_tmp=(NetworkParams*)malloc(pop*sizeof(NetworkParams));
	if(!population || !population_tmp){
		return -1;
	}

	int i, j, k;
	for(i=0;i<pop;++i){
		population[i].score=0;
		population[i].act_func_L1=SIGMOID;
		population[i].act_func_L2=SIGMOID;

		for(j=0;j<LAYER1_OUT;++j){
			for(k=0;k<LAYER1_IN;++k){
				if(rand()%2==0){
					population[i].wL1[j][k]=rand()%100;
				}else{
					population[i].wL1[j][k]=-(rand()%100);
				}
			}
		}
		for(j=0;j<LAYER2_OUT;++j){
			for(k=0;k<LAYER2_IN;++k){
				if(rand()%2==0){
					population[i].wL1[j][k]=rand()%100;
				}else{
					population[i].wL1[j][k]=-(rand()%100);
				}
			}
		}
	}
	return 0;
}

static void genetic_run_units(int pop){
	int i, s;
	float in[6];
	float out[3];
	SnakeGame game;
	SnakeParam param;

	for(i=0;i<pop;++i){
		snake_init(&game);
		network_init(&population[i]);

		for(s=0;s<20000;++s){
			if(!game.status){
				break;
			}        

    	    snake_getparam(&game, &param);
        	in[0]=param.blocked_f;
        	in[1]=param.blocked_r;
        	in[2]=param.blocked_l;
        	in[3]=param.food_f;
        	in[4]=param.food_r;
        	in[5]=param.food_l;
        	network_output(in, out);
 
        	if(out[1]>out[0] && out[1]>out[2]){
	            snake_right(&game);
    	    }else if(out[2]>out[0] && out[2]>out[1]){
        	    snake_left(&game);
        	}
		}
		population[i].score=game.scores;
	}
}

static void genetic_selection(int pop){//TODO
	int i;
	int b=0;
	int bs=population[0].score;

	for(i=0;i<pop;++i){
		if(population[i].score>bs){
			b=i;
			bs=population[i].score;
		}
	}

	for(i=0;i<pop;++i){
		if(i==b){
			continue;
		}

		int a=rand()%6;
		int b=rand()%6;
		int c=rand()%3;
		int d=rand()%6;

		if(rand()%10==0){
			population[i].wL1[a][b] = population[b].wL1[a][b];
			population[i].wL2[c][d] = population[b].wL1[c][d];
		}
		if(rand()%5==0){
			population[i].wL1[a][b] *= 1.01;
			population[i].wL2[c][d] *= 1.01;
		}else{
			population[i].wL1[a][b] *= 0.09;
			population[i].wL2[c][d] *= 0.09;
		}
	}
}

static void genetic_store_best(int pop){
	int i, score, best;

	FILE *fd=fopen("netdat", "wb");
	if(!fd){
		printf("ERROR: genetic_store_best: fopen\n");
		exit(1);
	}

	best=0;
	score=population[0].score;

	for(i=1;i<pop;++i){
		if(population[i].score>score){
			best=i;
			score=population[i].score;
		}
	}

	fwrite(&population[best], sizeof(NetworkParams), 1, fd);
	fclose(fd);
}


int genetic_run(int iter, int pop){
	if(iter<1 || pop<1){
		return -1;
	}

	genetic_init_population(pop);

	while(iter--){
		genetic_run_units(pop);
		genetic_selection(pop);
	}
	
	genetic_store_best(pop);
	return 0;
}

