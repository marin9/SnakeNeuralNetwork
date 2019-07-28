#pragma once

#define SG_HEIGHT	15
#define SG_WIDTH	20

#define SG_RUN		0
#define SG_OVER		1
#define SG_FINISH	2


typedef struct{
	int x;
	int y;
} Food;

typedef struct{
	int x[SG_HEIGHT*SG_WIDTH];
	int y[SG_HEIGHT*SG_WIDTH];
} Snake;

typedef struct{
	Snake snake;
	Food food;
	int length;
	int scores;
	int status;
	int ort;
} SnakeGame;


void snake_init(SnakeGame* game);
void snake_step(SnakeGame* game);
void snake_left(SnakeGame* game);
void snake_right(SnakeGame* game);

int snake_get_status(SnakeGame *game);
int snake_get_scores(SnakeGame *game);
Food* snake_get_food(SnakeGame *game);
Snake* snake_get_snake(SnakeGame *game);
