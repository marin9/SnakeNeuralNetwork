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

	if(game->snake.x[0]==game->food.x && game->snake.y[0]==game->food.y){
		game->scores += 10;
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
		if(x<0 || y<0 || x>=SG_WIDTH || y>=SG_HEIGHT){
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

	snake_move(game);
	snake_collision(game);
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

void snake_getparam(SnakeGame *game, float *in){
	//0 zid ispred
	//1 zid desno
	//2 zid lijevo

	//3 hrana ispred
	//4 hrana desno
	//5 hrana lijevo

	switch(game->snake.ort){
	case ORT_UP:
		if(game->snake.x[0]-1<0){
			in[0]=1.0;
			in[1]=0.0;
			in[2]=0.0;
		}else if(game->snake.y[0]+1>=SG_WIDTH){
			in[0]=0.0;
			in[1]=1.0;
			in[2]=0.0;			
		}else if(game->snake.y[0]-1<0){
			in[0]=0.0;
			in[1]=0.0;
			in[2]=1.0;
		}else{
			in[0]=0.0;
			in[1]=0.0;
			in[2]=0.0;
		}

		if(game->food.y==game->snake.y[0]){
			in[3]=1.0;
			in[4]=0.0;
			in[5]=0.0;
		}else if(game->food.x<game->snake.x[0]){
			in[3]=0.0;
			in[4]=1.0;
			in[5]=0.0;
		}else if(game->food.x>game->snake.x[0]){
			in[3]=0.0;
			in[4]=0.0;
			in[5]=1.0;
		}else{
			in[3]=0.0;
			in[4]=0.0;
			in[5]=0.0;
		}
		break;


	case ORT_DOWN:



	case ORT_RIGHT:




	case ORT_LEFT:
		if(game->snake.y[0]-1<0){
			in[0]=1.0;
			in[1]=0.0;
			in[2]=0.0;
		}else if(game->snake.x[0]-1<0){
			in[0]=0.0;
			in[1]=1.0;
			in[2]=0.0;			
		}else if(game->snake.x[0]+1>=SG_HEIGHT){
			in[0]=0.0;
			in[1]=0.0;
			in[2]=1.0;
		}else{
			in[0]=0.0;
			in[1]=0.0;
			in[2]=0.0;
		}

		if(game->food.y==game->snake.y[0]){
			in[3]=1.0;
			in[4]=0.0;
			in[5]=0.0;
		}else if(game->food.x<game->snake.x[0]){
			in[3]=0.0;
			in[4]=1.0;
			in[5]=0.0;
		}else if(game->food.x>game->snake.x[0]){
			in[3]=0.0;
			in[4]=0.0;
			in[5]=1.0;
		}else{
			in[3]=0.0;
			in[4]=0.0;
			in[5]=0.0;
		}
		break;
	}
}
