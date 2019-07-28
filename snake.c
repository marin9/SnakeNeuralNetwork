#include "snake.h"

#define ORT_UP		0
#define ORT_LEFT	1
#define ORT_DOWN	2
#define ORT_RIGHT	3


static void snake_locate_food(SnakeGame *game){







}

static void snake_move(SnakeGame *game){
	switch(game->ort){
	case ORT_UP:
		--(game->snake.x[0]);
		break;
	case ORT_DOWN:
		++(game->snake.y[0]);
		break;
	case ORT_LEFT:
		--(game->snake.y[0]);
		break;
	case ORT_RIGHT:
		++(game->snake.y[0]);
		break;
	}

	int i;
	for(i=1;i<game->length;++i){
		game->snake.x[i]=
		game->snake.y[i]=
	}
}

static void snake_collision(SnakeGame *game){







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
