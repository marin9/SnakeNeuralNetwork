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
static int run;


void graphic_init();
void graphic_clear();
void game_step();
void game_exit();
void game_status();
void game_render();
void wait_for_key();



//TODO main.c snake.c(rand collision)
int main (int argc, char** argv){
	srand(time(0));
	graphic_init();
    snake_init(&game);


    run=1;
    game_render();
    SDL_Delay(2000);

    while(run){
    	game_step();
    	game_render();
    	SDL_Delay(200);
    	game_status();
    }

    SDL_Delay(2000);
    wait_for_key();

    game_exit();
    return 0;
}


void graphic_init(){
	window=SDL_CreateWindow("Snake game", 
    	SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        W_WIDTH,
        W_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    graphic_clear();
}

void graphic_clear(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void game_exit(){
	SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

void game_status(){
	if(snake_get_status(&game)!=SG_RUN){
		run=0;
	}
}

void game_step(){
	SDL_Event event;

	while(SDL_PollEvent(&event)){
    	if(event.type==SDL_KEYDOWN){
    		int key=event.key.keysym.sym;

    		if(key==SDLK_LEFT){
    			snake_left(&game);
    		}else if(key==SDLK_RIGHT){
    			snake_right(&game);
    		}


		}else if(event.type==SDL_QUIT){
			game_exit();
		}
	}
	snake_step(&game);
}

void game_render(){
	SDL_Rect r;
    r.w=W_WIDTH/SG_WIDTH;
    r.h=W_HEIGHT/SG_HEIGHT;

    int i;
    int len=game.length;
    Snake *s=&(game.snake);

    graphic_clear();

    for(i=0;i<len;++i){
    	r.x=s->x[i]*r.w;
    	r.y=s->y[i]*r.h;
    	if(i) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    	else SDL_SetRenderDrawColor(renderer, 0, 255, 155, 0);
		SDL_RenderFillRect(renderer, &r);
    }

    r.x=game.food.x*r.w;
    r.y=game.food.y*r.h;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &r);

    SDL_RenderPresent(renderer);
}

void wait_for_key(){
	SDL_Event event;

	while(SDL_PollEvent(&event)){
    	if(event.type==SDL_KEYDOWN || event.type==SDL_QUIT){
			return;
		}
	}
}
