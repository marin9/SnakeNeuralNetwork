#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
		for(j=0;j<NET_INPUTS;++j){
			for(k=0;k<NET_INPUTS;++k){
				population[i].w[j][k]=rand()%10;
			}
		}
		population[i].score=0;
	}
	return 0;
}

static void genetic_run_units(int pop, int steps){
	int i, s;
	float in[NET_INPUTS];
	float out[NET_OUTPUTS];
	SnakeGame game;
	SnakeParam param;

	for(i=0;i<pop;++i){
		snake_init(&game);
		network_init(&population[i]);

		for(s=0;s<steps;++s){
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
        	//out[0] - forward
 			//out[1] - right
 			//out[2] - left

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

static int genetic_get_best(int pop){
	int i, best=0;
	int score=population[0].score;

	for(i=1;i<pop;++i){
		if(population[i].score>score){
			best=i;
			score=population[i].score;
		}
	}
	return best;
}

static int genetic_get_worst(int pop){
	int i, worst=0;
	int score=population[0].score;

	for(i=1;i<pop;++i){
		if(population[i].score<score){
			worst=i;
			score=population[i].score;
		}
	}
	return worst;
}

static void genetic_selection(int pop, int iter){
	int i, select, N=5;
	NetworkParams best;

	for(i=0;i<N;++i){
		select=genetic_get_best(pop);
		memcpy(&population_tmp[i], &population[select], sizeof(NetworkParams));
		if(i==0){
			memcpy(&best, &population[select], sizeof(NetworkParams));
		}
	}

	for(i=0;i<N;++i){
		select=genetic_get_worst(pop);
		memcpy(&population[select], &population_tmp[i], sizeof(NetworkParams));

		int x, y;
		for(x=0;x<NET_INPUTS;++x){
			for(y=0;y<NET_INPUTS;++y){
				population[select].w[x][y]=(population[select].w[x][y]+best.w[x][y])/2;
			}
		}

		int a=rand()%NET_INPUTS;
		int b=rand()%NET_INPUTS;

		if(rand()%2==0){
			population[select].w[a][b] *= 1.5;
		}else{
			population[select].w[a][b] *= 0.5;
		}			
	}
}

static void genetic_store_best(int pop){
	int best;

	FILE *fd=fopen("netdat", "wb");
	if(!fd){
		printf("ERROR: genetic_store_best: fopen\n");
		exit(1);
	}

	best=genetic_get_best(pop);
	fwrite(&population[best], sizeof(NetworkParams), 1, fd);
	fclose(fd);
}


int genetic_run(int iter, int pop, int steps){
	if(iter<1 || pop<1){
		return -1;
	}

	genetic_init_population(pop);

	while(iter--){
		genetic_run_units(pop, steps);
		genetic_selection(pop, iter);
	}
	
	genetic_store_best(pop);
	return 0;
}

