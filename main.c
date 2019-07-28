#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "snake.h"
#include "network.h"

#define W_WIDTH		800
#define W_HEIGHT	600


static SDL_Window *window;
static SDL_Renderer *renderer;
static SnakeGame game;
static Network nnet;
static float w1[]={1, 2, 3, 4, 5, 6};
static float w2[]={0.2, 0.5, 0.1, 0.4, 10, 4};
static float w3[]={6, 2, 3, 3, 1, 5};


void graphic_init();
void game_step();
void game_render();
void game_exit();
void wait_for_key();
void get_args(int argc, char** argv);



//TODO main.c snake.c(rand collision)
int main (int argc, char** argv){
    get_args(argc, argv);
	srand(time(0));
	graphic_init();
    snake_init(&game);
    network_init(&nnet, w1, w2, w3);

    game_render();
    SDL_Delay(2000);

    while(game.status){
    	game_step();
    	game_render();
    	SDL_Delay(200);
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
	/*SDL_Event event;
    
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
    */

    float in[6];
    float out[3];
    snake_getparam(&game, in);
    network_output(&nnet, in, out);

    if(out[1]>out[0] && out[1]>out[2]) snake_right(&game);
    else if(out[2]>out[0] && out[2]>out[1]) snake_left(&game);


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

void get_args(int argc, char** argv){
    argc=argc;
    argv=argv;
}
