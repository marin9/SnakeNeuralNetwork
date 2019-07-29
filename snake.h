#pragma once

#define SG_HEIGHT	20
#define SG_WIDTH	25

typedef struct{
	int x;
	int y;
} Food;

typedef struct{
	int ort;
	int length;
	int x[SG_HEIGHT*SG_WIDTH];
	int y[SG_HEIGHT*SG_WIDTH];
} Snake;

typedef struct{
	Snake snake;
	Food food;
	int scores;
	int status;
} SnakeGame;


void snake_init(SnakeGame *game);
void snake_step(SnakeGame *game);
void snake_left(SnakeGame *game);
void snake_right(SnakeGame *game);
void snake_getparam(SnakeGame *game, float *param);