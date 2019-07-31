#include <math.h>
#include <stdlib.h>
#include "snake.h"

#define ORT_UP		0
#define ORT_LEFT	1
#define ORT_DOWN	2
#define ORT_RIGHT	3


static void snake_locate_food(SnakeGame *game){
	int i, ret, rx, ry, sx, sy;

	do{
		ret=0;
		rx=rand()%SG_WIDTH; 
		ry=rand()%SG_HEIGHT;

		for(i=0;i<game->snake.length;++i){
			sx=game->snake.x[i];
			sy=game->snake.y[i];

			if(rx==sx && ry==sy){
				ret=1;
				break;
			}
		}
	}while(ret);

	game->food.x=rx;
	game->food.y=ry;
}

static void snake_move(SnakeGame *game){
	int lastX=game->snake.x[game->snake.length-1];
	int lastY=game->snake.y[game->snake.length-1];
	int i;

	for(i=game->snake.length-1;i>0;--i){
		game->snake.x[i]=game->snake.x[i-1];
		game->snake.y[i]=game->snake.y[i-1];
	}

	switch(game->snake.ort){
	case ORT_UP:
		game->snake.x[0]=game->snake.x[1];
		game->snake.y[0]=game->snake.y[1]-1;
		break;
	case ORT_DOWN:
		game->snake.x[0]=game->snake.x[1];
		game->snake.y[0]=game->snake.y[1]+1;
		break;
	case ORT_LEFT:
		game->snake.x[0]=game->snake.x[1]-1;
		game->snake.y[0]=game->snake.y[1];
		break;
	case ORT_RIGHT:
		game->snake.x[0]=game->snake.x[1]+1;
		game->snake.y[0]=game->snake.y[1];
		break;
	}

	if((game->snake.x[0]==game->food.x) && (game->snake.y[0]==game->food.y)){
		game->scores += 100;
		game->snake.x[game->snake.length]=lastX;
		game->snake.y[game->snake.length]=lastY;
		game->snake.length += 1;
		snake_locate_food(game);
	}
}

static void snake_collision(SnakeGame *game){
	int i, x, y, hx, hy;

	hx=game->snake.x[0];
	hy=game->snake.y[0];

	for(i=0;i<game->snake.length;++i){
		x=game->snake.x[i];
		y=game->snake.y[i];

		if(i==0 && (x<0 || y<0 || x>=SG_WIDTH || y>=SG_HEIGHT)){
			game->status=0;
			return;
		}

		if(i!=0 && x==hx && y==hy){
			game->status=0;
			return;
		}
	}
}

void snake_init(SnakeGame* game){
	game->snake.ort=ORT_UP;
	game->status=1;
	game->scores=0;
	
	game->snake.x[0]=SG_WIDTH/2;
	game->snake.y[0]=SG_HEIGHT/2;

	int i;
	for(i=1;i<5;++i){
		game->snake.x[i]=game->snake.x[i-1];
		game->snake.y[i]=game->snake.y[i-1]+1;
	}
	game->snake.length=i;

	snake_locate_food(game);
}

void snake_step(SnakeGame* game){
	if(!game->status){
		return;
	}

	int sx, sy, fx, fy;
	float d1, d2;

	sx=game->snake.x[0];
	sy=game->snake.y[0];
	fx=game->food.x;
	fy=game->food.y;
	d1=sqrt((sx-fx)*(sx-fx)+(sy-fy)*(sy-fy));

	snake_move(game);
	snake_collision(game);
	
	sx=game->snake.x[0];
	sy=game->snake.y[0];
	fx=game->food.x;
	fy=game->food.y;
	d2=sqrt((sx-fx)*(sx-fx)+(sy-fy)*(sy-fy));

	if(d2<d1){
		game->scores += 1;
	}else if(d2>d1){
		game->scores -= 2;
	}
}

void snake_left(SnakeGame* game){
	switch(game->snake.ort){
	case ORT_UP:
		game->snake.ort=ORT_LEFT;
		break;
	case ORT_LEFT:
		game->snake.ort=ORT_DOWN;
		break;
	case ORT_DOWN:
		game->snake.ort=ORT_RIGHT;
		break;
	case ORT_RIGHT:
		game->snake.ort=ORT_UP;
		break;
	}
}

void snake_right(SnakeGame* game){
	switch(game->snake.ort){
	case ORT_UP:
		game->snake.ort=ORT_RIGHT;
		break;
	case ORT_LEFT:
		game->snake.ort=ORT_UP;
		break;
	case ORT_DOWN:
		game->snake.ort=ORT_LEFT;
		break;
	case ORT_RIGHT:
		game->snake.ort=ORT_DOWN;
		break;
	}
}



static int snake_forward_blocked(SnakeGame *game){
	int hx=game->snake.x[0];
	int hy=game->snake.y[0];
	int i;

	switch(game->snake.ort){
	case ORT_UP:
		--hy;
		break;
	case ORT_DOWN:
		++hy;
		break;
	case ORT_RIGHT:
		++hx;
		break;
	case ORT_LEFT:
		--hx;
		break;
	}

	if(hx<0 || hy<0 || hx>=SG_WIDTH || hy>=SG_HEIGHT){
		return 1;
	}

	for(i=0;i<game->snake.length;++i){
		if(game->snake.x[i]==hx && game->snake.y[i]==hy){
			return 1;
		}
	}
	return 0;
}

static int snake_right_blocked(SnakeGame *game){
	int hx=game->snake.x[0];
	int hy=game->snake.y[0];
	int i;

	switch(game->snake.ort){
	case ORT_UP:
		++hx;
		break;
	case ORT_DOWN:
		--hx;
		break;
	case ORT_RIGHT:
		++hy;
		break;
	case ORT_LEFT:
		--hy;
		break;
	}

	if(hx<0 || hy<0 || hx>=SG_WIDTH || hy>=SG_HEIGHT){
		return 1;
	}

	for(i=0;i<game->snake.length;++i){
		if(game->snake.x[i]==hx && game->snake.y[i]==hy){
			return 1;
		}
	}
	return 0;
}

static int snake_left_blocked(SnakeGame *game){
	int hx=game->snake.x[0];
	int hy=game->snake.y[0];
	int i;

	switch(game->snake.ort){
	case ORT_UP:
		--hx;
		break;
	case ORT_DOWN:
		++hx;
		break;
	case ORT_RIGHT:
		--hy;
		break;
	case ORT_LEFT:
		++hy;
		break;
	}

	if(hx<0 || hy<0 || hx>=SG_WIDTH || hy>=SG_HEIGHT){
		return 1;
	}

	for(i=0;i<game->snake.length;++i){
		if(game->snake.x[i]==hx && game->snake.y[i]==hy){
			return 1;
		}
	}
	return 0;
}

static int snake_food_forward(SnakeGame *game){
	int hx=game->snake.x[0];
	int hy=game->snake.y[0];
	int fx=game->food.x;
	int fy=game->food.y;
	int ort=game->snake.ort;

	if(ort==ORT_UP && fy<hy)
		return 1;

	if(ort==ORT_DOWN && fy>hy)
		return 1;

	if(ort==ORT_RIGHT && fx>hx)
		return 1;

	if(ort==ORT_LEFT && fx<hx)
		return 1;

	return 0;
}

static int snake_food_right(SnakeGame *game){
	int hx=game->snake.x[0];
	int hy=game->snake.y[0];
	int fx=game->food.x;
	int fy=game->food.y;
	int ort=game->snake.ort;

	if(ort==ORT_UP && fx>hx)
		return 1;

	if(ort==ORT_DOWN && fx<hx)
		return 1;

	if(ort==ORT_RIGHT && fy>hy)
		return 1;

	if(ort==ORT_LEFT && fy<hy)
		return 1;

	return 0;
}

static int snake_food_left(SnakeGame *game){
	int hx=game->snake.x[0];
	int hy=game->snake.y[0];
	int fx=game->food.x;
	int fy=game->food.y;
	int ort=game->snake.ort;

	if(ort==ORT_UP && fx<hx)
		return 1;

	if(ort==ORT_DOWN && fx>hx)
		return 1;

	if(ort==ORT_RIGHT && fy<hy)
		return 1;

	if(ort==ORT_LEFT && fy>hy)
		return 1;

	return 0;
}

void snake_getparam(SnakeGame *game, SnakeParam *p){
	if(snake_forward_blocked(game))
		p->blocked_f=1.0;
	else
		p->blocked_f=0.0;

	if(snake_right_blocked(game))
		p->blocked_r=1.0;
	else
		p->blocked_r=0.0;

	if(snake_left_blocked(game))
		p->blocked_l=1.0;
	else
		p->blocked_l=0.0;

	if(snake_food_forward(game))
		p->food_f=1.0;
	else
		p->food_f=0.0;

	if(snake_food_right(game))
		p->food_r=1.0;
	else
		p->food_r=0.0;

	if(snake_food_left(game))
		p->food_l=1.0;
	else
		p->food_l=0.0;
}
