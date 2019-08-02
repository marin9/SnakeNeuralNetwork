#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "snake.h"
#include "network.h"
#include "genetic.h"

#define W_WIDTH		800
#define W_HEIGHT	600


static SDL_Window *window;
static SDL_Renderer *renderer;
static SnakeGame game;
static NetworkParams netparam;
static int level;
static int player;


void print_help();
void read_netsettings();
void graphic_init();
void game_step();
void game_render();
void game_exit();
void wait_for_key();
void get_arguments(int argc, char **argv);


int main (int argc, char** argv){
    if(argc<2){
        print_help();
    }

    srand(time(0));
    get_arguments(argc, argv);
    graphic_init();
    snake_init(&game);
    game_render();
    network_init(&netparam);
   
    SDL_Delay(2000);

    while(game.status){
    	game_step();
    	game_render();
    	SDL_Delay(50*level);
    }

    SDL_Delay(1000);
    wait_for_key();
    game_exit();
    return 0;
}


void print_help(){
    printf("ERROR: Illegal arguments.\n");
    printf("Usage:\n");
    printf("p - player\nt - run training\nn - run network\n");
    printf("snake n\n");
    printf("snake p [level]\n");
    printf("snake t [iterations] [population]\n");
    exit(1);
}

void read_netsettings(){
    FILE *fd=fopen("netdat", "rb");
    if(!fd){
        printf("ERROR: read_netsettings: fopen\n");
        exit(2);
    }
    fread(&netparam, sizeof(NetworkParams), 1, fd);
    fclose(fd);
}

void graphic_init(){
	window=SDL_CreateWindow("Snake", 
    	SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        W_WIDTH,
        W_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    renderer=SDL_CreateRenderer(window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );
}

void game_exit(){
	SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

void game_step(){
    if(player){
        SDL_Event event;   
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                case SDLK_RIGHT:
                    snake_right(&game);
                    break;
                case SDLK_LEFT:
                    snake_left(&game);
                    break;
                }
            }else if(event.type==SDL_QUIT){
                game_exit();
            }
        }
    }else{
        float in[6], out[3];
        SnakeParam param;

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
	snake_step(&game);
}

void game_render(){
    Snake *s;
	SDL_Rect r;

    r.w=W_WIDTH/SG_WIDTH;
    r.h=W_HEIGHT/SG_HEIGHT;
    s=&(game.snake);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int i;
    for(i=0;i<s->length;++i){
    	r.x=s->x[i]*r.w;
    	r.y=s->y[i]*r.h;
    	if(i)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    	else
            SDL_SetRenderDrawColor(renderer, 255, 155, 0, 0);

		SDL_RenderFillRect(renderer, &r);
    }

    r.x=game.food.x*r.w;
    r.y=game.food.y*r.h;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
}

void wait_for_key(){
	SDL_Event event;
    while(1){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_KEYDOWN || event.type==SDL_QUIT){
                return;
            }
        }
        SDL_Delay(100);
    }
}

void get_arguments(int argc, char **argv){
    if(strcmp(argv[1], "p")==0){
        if(argc!=3){
            print_help();
        }
        player=1;
        level=atoi(argv[2]);
        
    }else if(strcmp(argv[1], "n")==0){
        player=0;
        level=1;
        read_netsettings();

    }else if(strcmp(argv[1], "t")==0){
        long t1, t2;

        if(argc!=4){
            print_help();
        }
        if(atoi(argv[3])<20){
            printf("ERROR: Minimal population: 20\n");
            exit(3);
        }

        t1=clock();
        genetic_run(atoi(argv[2]), atoi(argv[3]));
        t2=clock();

        printf("Training finish.\nTime: %ld s\n", (t2-t1)/CLOCKS_PER_SEC);
        exit(0);
    }else{
        print_help();
    }
}
