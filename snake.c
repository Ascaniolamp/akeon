#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define MAXLEN 150
float multiplier = 1;
int delay = 200000;

typedef struct{
	char head_symbol, body_symbol;
	int ybody[MAXLEN], xbody[MAXLEN];
	int ydir, xdir;
	int size;
}Snake;

typedef struct{
	char symbol;
	int ypos, xpos;
}Apple;

int randrange(int min, int max){ return random() % (max + 1 - min) + min; }

void endprogram(int code){
	endwin();

	switch(code){
		case 0: printf("You won!\n"); break;
		case 1: printf("You lost...\n"); break;
		case 2: exit(0);
		default: printf("ERROR (Exit code %d)\n",code); break;
	}

	exit(code);}
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
	init_pair(2, COLOR_RED, COLOR_BLACK);}
void borders_render(){
	attrset(COLOR_PAIR(0));

	for(int i=0; i<COLS; ++i){
		mvaddch(0,i,'=');
		mvaddch(LINES-1,i,'=');
	}

	for(int i=0; i<LINES; ++i){
		mvaddch(i,0,'|');
		mvaddch(i,COLS-1,'|');
	}}

void apple_regen(Apple *apple);
void snake_movement(Snake *snake);
void snake_death(Snake *snake);

int main(int argc, char const *argv[]){
	initprogram();

	Snake snake = {'@', 'x', {LINES/2}, {COLS/2}, 0, 0, 3};
	Apple apple = {'O', 0, 0};

	apple_regen(&apple);

	while(true){
		erase();

		snake_movement(&snake);
		snake_death(&snake);

		// APPLE EAT
		if(snake.ybody[0] == apple.ypos && snake.xbody[0] == apple.xpos){
			snake.size++;

			bool bad_apple;
			do{
				bad_apple = false;
				apple_regen(&apple);
				for(int i=0; i<snake.size; i++)
					if((apple.ypos == snake.ybody[i]) && (apple.xpos == snake.xbody[i]))
						bad_apple = true;
			}
			while(bad_apple);

			delay *= multiplier;
		}

		// CHECK WIN
		if(snake.size >= MAXLEN) endprogram(0);

		// RENDER SNAKE
		attrset(COLOR_PAIR(1));
		for(int i=1; i<snake.size; i++) mvaddch(snake.ybody[i], snake.xbody[i], snake.body_symbol);
		mvaddch(snake.ybody[0], snake.xbody[0], snake.head_symbol);

		// RENDER APPLE
		attrset(COLOR_PAIR(2));
		mvaddch(apple.ypos, apple.xpos, apple.symbol);

		borders_render();

		refresh();
		usleep(delay);
	}

	endprogram(0);
}

void apple_regen(Apple *apple){
	apple->ypos = randrange(1,LINES-2);
	apple->xpos = randrange(1,COLS-2);
}

void snake_movement(Snake *snake){
	for(int i=snake->size-1; i>0; i--){
		snake->ybody[i] = snake->ybody[i-1];
		snake->xbody[i] = snake->xbody[i-1];
	}

	switch(getch()){
		case KEY_UP: snake->ydir = -1; snake->xdir = 0; break;
		case KEY_DOWN: snake->ydir = 1; snake->xdir = 0; break;
		case KEY_LEFT: snake->ydir = 0; snake->xdir = -1; break;
		case KEY_RIGHT: snake->ydir = 0; snake->xdir = 1; break;
	}

	snake->ybody[0] += snake->ydir;
	snake->xbody[0] += snake->xdir;
}

void snake_death(Snake *snake){
	if(snake->ybody[0] > LINES-2 || snake->ybody[0] < 1) endprogram(1);
	if(snake->xbody[0] > COLS-2 || snake->xbody[0] < 1) endprogram(1);
	for(int i=1; i<snake->size; i++){
		bool in_body = (snake->ybody[0] == snake->ybody[i]) && (snake->xbody[0] == snake->xbody[i]);
		bool is_moving = (snake->ydir != 0) || (snake->xdir !=0);
		if(in_body && is_moving) endprogram(1);
	}
}