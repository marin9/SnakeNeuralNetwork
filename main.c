#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "snake.h"

#define W_WIDTH		800
#define W_HEIGHT	600


static SDL_Window *window;
static SDL_Renderer *renderer;
static SnakeGame game;
static int level;


void graphic_init();
void game_step();
void game_render();
void game_exit();
void wait_for_key();
void get_args(int argc, char** argv);


//TODO main.c genetic.c
int main (int argc, char** argv){
    get_args(argc, argv);
	graphic_init();
    snake_init(&game);
    game_render();
    SDL_Delay(2000);
    level=4;

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
    //TODO genetic run if -g






}
