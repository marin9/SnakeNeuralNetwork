#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "snake.h"

#define W_WIDTH		800
#define W_HEIGHT	600



static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Event event;
static SnakeGame game;


void graphic_init();
void graphic_clear();


//TODO main.c snake.c
int main (int argc, char** argv){
	
	srand(time(0));
	graphic_init();
    snake_init(&game);

    SDL_Delay(2000);

    while(1){
    	//get input
    	//step
    	//draw
    	SDL_Delay(200);
    	//check status
    }



while(1){
  while( SDL_PollEvent( &event ) ){
    /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
    switch( event.type ){
      case SDL_KEYDOWN:
        printf( "Key press detected\n" );
        break;

      case SDL_KEYUP:
        printf( "Key release detected\n" );
        break;

      default:
        break;
    }
  }




    SDL_Delay(20);
}
    SDL_DestroyWindow(window);
    SDL_Quit();
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

/*  SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
SDL_RenderFillRect(renderer, &r);
*/