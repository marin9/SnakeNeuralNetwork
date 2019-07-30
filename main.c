#include <stdio.h>
#include <stdlib.h>
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
static int level;
static NetworkParams netparam;


void graphic_init();
void game_step();
void game_render();
void game_exit();
void wait_for_key();



int main (int argc, char** argv){

    if(argc==2){
        genetic_run(20000, 200);
        return 0;
    }

    srand(time(0));
	graphic_init();
    snake_init(&game);
    game_render();
    SDL_Delay(2000);
    level=1;

    FILE *fd=fopen("netdat", "rb");
    if(!fd){
        printf("ERROR: main: fopen\n");
        exit(1);
    }
    fread(&netparam, sizeof(NetworkParams), 1, fd);
    network_init(&netparam);

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
    /*
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
	snake_step(&game);
    */

    float in[6];
    float out[3];

    snake_getparam(&game, in);
printf("%f %f %f %f %f %f\n", in[0], in[1], in[2], in[3], in[4], in[5]);
    network_output(in, out);
printf("%f %f %f\n\n", out[0], out[1], out[2]);
 
    if(out[1]>out[0] && out[1]>out[2]){
        snake_right(&game);
    }else if(out[2]>out[0] && out[2]>out[1]){
        snake_left(&game);
    }
    snake_step(&game);

}

void game_render(){
    int i;
    Snake *s;
	SDL_Rect r;
    r.w=W_WIDTH/SG_WIDTH;
    r.h=W_HEIGHT/SG_HEIGHT;
    s=&(game.snake);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for(i=0;i<s->length;++i){
    	r.x=s->x[i]*r.w;
    	r.y=s->y[i]*r.h;
    	if(i) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    	else SDL_SetRenderDrawColor(renderer, 255, 155, 0, 0);
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
