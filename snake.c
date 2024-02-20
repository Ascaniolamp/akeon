#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int randrange(int min, int max){ return random() % (max + 1 - min) + min; }

void endprogram(int code){
	endwin();
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
void snake_movement(int *ypos, int *xpos);

int main(int argc, char const *argv[]){
	initprogram();

	const float DIFFICULTY = 0.95;
	const int AREA = (COLS-2)*(LINES-2);
	const int MAXLEN = AREA/2;
	int delay = 200000;

	typedef struct{
		char head_symbol, body_symbol;
		int ypos, xpos, size;
	}Snake;

	typedef struct{
		char symbol;
		int ypos, xpos;
	}Apple;

	Snake snake = {'@', 'x', LINES/2, COLS/2, 3};
	Apple apple = {'O', 0, 0};

	int body[2][MAXLEN];
	for(int i=0; i<snake.size; i++){
		body[0][i] = snake.ypos;
		body[1][i] = snake.xpos;
	}

	apple_regen(&apple.ypos, &apple.xpos);

	while(true){
		erase();

		snake_movement(&snake.ypos, &snake.xpos);

		// BODY MOVEMENT
		for(int i=snake.size+1; i>0; i--){
			body[0][i] = body[0][i-1];
			body[1][i] = body[1][i-1];
		}
		body[0][0] = snake.ypos;
		body[1][0] = snake.xpos;

		// SNAKE DEATH
		if(snake.ypos > LINES-2 || snake.ypos < 1) endprogram(1);
		if(snake.xpos > COLS-2 || snake.xpos < 1) endprogram(1);

		// APPLE EAT
		if(snake.ypos == apple.ypos && snake.xpos == apple.xpos){
			if(snake.size++ >= MAXLEN) endprogram(0);
			apple_regen(&apple.ypos, &apple.xpos);
			delay *= DIFFICULTY;
		}

		// RENDER APPLE
		attrset(COLOR_PAIR(2));
		mvaddch(apple.ypos, apple.xpos, apple.symbol);

		// RENDER SNAKE & BODY
		attrset(COLOR_PAIR(1));
		mvaddch(snake.ypos, snake.xpos, snake.head_symbol);
		for(int i=1; i<snake.size; i++) mvaddch(body[0][i], body[1][i], snake.body_symbol);

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

void snake_movement(int *ypos, int *xpos){
	static int ydir, xdir;

	switch(getch()){
		case KEY_UP:
			ydir = -1;
			xdir = 0;
			break;
		case KEY_DOWN:
			ydir = 1;
			xdir = 0;
			break;
		case KEY_LEFT:
			ydir = 0;
			xdir = -1;
			break;
		case KEY_RIGHT:
			ydir = 0;
			xdir = 1;
			break;
	}

	*ypos += ydir;
	*xpos += xdir;
}