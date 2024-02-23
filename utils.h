#include <signal.h>
#include <time.h>

int randrange(int min, int max){ return random() % (max + 1 - min) + min; }
void endprogram(int code);
void initprogram();
void colorize(int fore, int back);

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

	OPTS.colors = OPTS.colors && has_colors();
	if(!OPTS.colors) return;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK); // Apple
	init_pair(2, COLOR_WHITE, COLOR_BLUE); // Snake
}

void colorize(int fore, int back){
	if(!OPTS.colors) return;
	init_pair(3, fore, back);
	attrset(COLOR_PAIR(3));
}