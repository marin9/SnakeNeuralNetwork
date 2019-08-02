#pragma once

#define GAME_HEIGHT	20
#define GAME_WIDTH	25

typedef struct{
	int x;
	int y;
} Food;

typedef struct{
	int ort;
	int length;
	int x[GAME_HEIGHT*GAME_WIDTH];
	int y[GAME_HEIGHT*GAME_WIDTH];
} Snake;

typedef struct{
	int status;
	int scores;
	Snake snake;
	Food food;
} SnakeGame;

typedef struct{
	float blocked_f;
	float blocked_r;
	float blocked_l;
	float food_f;
	float food_r;
	float food_l;
} SnakeParam;


void snake_init(SnakeGame *game);
void snake_step(SnakeGame *game);
void snake_left(SnakeGame *game);
void snake_right(SnakeGame *game);
void snake_getparam(SnakeGame *game, SnakeParam *p);
