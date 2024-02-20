#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int randrange(int min, int max){ return random() % (max + 1 - min) + min; }

void endprogram(int code){
	endwin();

	switch(code){
		case 0: printf("You won!\n"); break;
		case 1: printf("You lost...\n"); break;
		case 2: exit(0);
		default: printf("ERROR (Exit code %d)\n",code); break;
	}

	exit(code);
}

void initprogram(){
	signal(SIGINT, endprogram);
	srandom(time(NULL));

	initscr();

	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	nonl();
	cbreak();
	echo();

	if(!has_colors()) return;
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_RED, COLOR_BLACK);
}

void borders_render();
void apple_regen(int *ypos, int *xpos);
void snake_movement(int *ypos, int *xpos, int *ydir, int *xdir);

int main(int argc, char const *argv[]){
	initprogram();

	const float DIFFICULTY = 0.95;
	const int AREA = (COLS-2)*(LINES-2);
	int delay = 200000;

	typedef struct{
		char head_symbol, body_symbol;
		int ybody[AREA], xbody[AREA];
		int ydir, xdir;
		int size;
	}Snake;

	typedef struct{
		char symbol;
		int ypos, xpos;
	}Apple;

	Snake snake;
	snake.head_symbol = '@';
	snake.body_symbol = 'x';
	snake.ybody[0] = LINES/2;
	snake.xbody[0] = COLS/2;
	snake.ydir = 0;
	snake.xdir = 0;
	snake.size = 3;

	Apple apple = {'O', 0, 0};

	apple_regen(&apple.ypos, &apple.xpos);

	while(true){
		erase();

		// BODY MOVEMENT
		for(int i=snake.size-1; i>0; i--){
			snake.ybody[i] = snake.ybody[i-1];
			snake.xbody[i] = snake.xbody[i-1];
		}

		snake_movement(&snake.ybody[0], &snake.xbody[0], &snake.ydir, &snake.xdir);

		// SNAKE DEATH
		if(snake.ybody[0] > LINES-2 || snake.ybody[0] < 1) endprogram(1);
		if(snake.xbody[0] > COLS-2 || snake.xbody[0] < 1) endprogram(1);
		for(int i=1; i<snake.size; i++){
			bool in_body = (snake.ybody[0] == snake.ybody[i]) && (snake.xbody[0] == snake.xbody[i]);
			bool is_moving = (snake.ydir != 0) || (snake.xdir !=0);
			if(in_body && is_moving){
				endprogram(1);
			}
		}

		// APPLE EAT
		if(snake.ybody[0] == apple.ypos && snake.xbody[0] == apple.xpos){
			if(snake.size++ >= AREA) endprogram(0);
			apple_regen(&apple.ypos, &apple.xpos);
			delay *= DIFFICULTY;
		}

		// RENDER SNAKE
		attrset(COLOR_PAIR(1));
		for(int i=1; i<snake.size; i++) mvaddch(snake.ybody[i], snake.xbody[i], snake.body_symbol);
		mvaddch(snake.ybody[0], snake.xbody[0], snake.head_symbol);

		// RENDER APPLE
		attrset(COLOR_PAIR(2));
		mvaddch(apple.ypos, apple.xpos, apple.symbol);

		// RENDER BORDERS
		borders_render();

		refresh();
		usleep(delay);
	}

	endprogram(0);
}

void borders_render(){
	attrset(COLOR_PAIR(0));

	for(int i=0; i<COLS; ++i){
		mvaddch(0,i,'=');
		mvaddch(LINES-1,i,'=');
	}

	for(int i=0; i<LINES; ++i){
		mvaddch(i,0,'|');
		mvaddch(i,COLS-1,'|');
	}
}

void apple_regen(int *ypos, int *xpos){
	*ypos = randrange(1,LINES-2);
	*xpos = randrange(1,COLS-2);
}

void snake_movement(int *ypos, int *xpos, int *ydir, int *xdir){
	switch(getch()){
		case KEY_UP: *ydir = -1; *xdir = 0; break;
		case KEY_DOWN: *ydir = 1; *xdir = 0; break;
		case KEY_LEFT: *ydir = 0; *xdir = -1; break;
		case KEY_RIGHT: *ydir = 0; *xdir = 1; break;
	}

	*ypos += *ydir;
	*xpos += *xdir;
}