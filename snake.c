#include <stdlib.h>
#include "snake.h"

#define ORT_UP		0
#define ORT_LEFT	1
#define ORT_DOWN	2
#define ORT_RIGHT	3


static void snake_locate_food(SnakeGame *game){
	int rx, ry;
	rx=rand()%SG_WIDTH; 
	ry=rand()%SG_HEIGHT;

	game->food.x=rx;
	game->food.y=ry;
}

static void snake_move(SnakeGame *game){
	int lastX=game->snake.x[game->length-1];
	int lastY=game->snake.y[game->length-1];
	int i;

	for(i=game->length-1;i>0;--i){
		game->snake.x[i]=game->snake.x[i-1];
		game->snake.y[i]=game->snake.y[i-1];
	}

	switch(game->ort){
	case ORT_UP:
		game->snake.x[0]=game->snake.x[1]-1;
		game->snake.y[0]=game->snake.y[1];
		break;
	case ORT_DOWN:
		game->snake.x[0]=game->snake.x[1]+1;
		game->snake.y[0]=game->snake.y[1];
		break;
	case ORT_LEFT:
		game->snake.x[0]=game->snake.x[1];
		game->snake.y[0]=game->snake.y[1]-1;
		break;
	case ORT_RIGHT:
		game->snake.x[0]=game->snake.x[1];
		game->snake.y[0]=game->snake.y[1]+1;
		break;
	}

	if(game->snake.x[0]==game->food.x && game->snake.y[0]==game->food.y){
		game->scores += 10;
		game->snake.x[game->length]=lastX;
		game->snake.y[game->length]=lastY;
		game->length += 1;
		snake_locate_food(game);
	}
}

static void snake_collision(SnakeGame *game){
	int i, x, y, hx, hy;

	hx=game->snake.x[0];
	hy=game->snake.y[0];

	for(i=0;i<game->length;++i){
		x=game->snake.x[i];
		y=game->snake.y[i];
		if(x<0 || y<0 || x>=SG_WIDTH || y>=SG_HEIGHT){
			game->status=SG_END;
			return;
		}

		if(i!=0 && x==hx && y==hy){
			game->status=SG_END;
			return;
		}
	}
}

void snake_init(SnakeGame* game){
	game->ort=ORT_UP;
	game->status=SG_RUN;
	game->scores=0;
	
	game->snake.x[0]=SG_WIDTH/2;
	game->snake.y[0]=SG_HEIGHT/2;

	int i;
	for(i=1;i<5;++i){
		game->snake.x[i]=game->snake.x[i-1];
		game->snake.y[i]=game->snake.y[i-1]+1;
	}
	game->length=i;

	snake_locate_food(game);
}

void snake_step(SnakeGame* game){
	if(game->status!=SG_RUN){
		return;
	}

	snake_move(game);
	snake_collision(game);
}

void snake_left(SnakeGame* game){
	switch(game->ort){
	case ORT_UP:
		game->ort=ORT_LEFT;
		break;
	case ORT_LEFT:
		game->ort=ORT_DOWN;
		break;
	case ORT_DOWN:
		game->ort=ORT_RIGHT;
		break;
	case ORT_RIGHT:
		game->ort=ORT_UP;
		break;
	}
}

void snake_right(SnakeGame* game){
	switch(game->ort){
	case ORT_UP:
		game->ort=ORT_RIGHT;
		break;
	case ORT_LEFT:
		game->ort=ORT_UP;
		break;
	case ORT_DOWN:
		game->ort=ORT_LEFT;
		break;
	case ORT_RIGHT:
		game->ort=ORT_DOWN;
		break;
	}
}

int snake_get_ort(SnakeGame *game){
	return game->ort;
}

int snake_get_status(SnakeGame *game){
	return game->status;
}

int snake_get_scores(SnakeGame *game){
	return game->scores;
}

Food* snake_get_food(SnakeGame *game){
	return &(game->food);
}

Snake* snake_get_snake(SnakeGame *game){
	return &(game->snake);
}
