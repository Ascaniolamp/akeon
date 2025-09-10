#pragma once

#include <signal.h>
#include <time.h>

int FIXED_LINES, FIXED_COLS;
int STARTLINE, STARTCOL;
int ENDLINE, ENDCOL;

int randrange(int min, int max){ return random() % (max + 1 - min) + min; }

void endprogram(int code);
void initprogram();

void update_viewport();
void colorize(int pair);

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

	FIXED_LINES = OPTS.fixed_lines;
	if(FIXED_LINES == 0) FIXED_LINES = LINES;

	FIXED_COLS = OPTS.fixed_cols;
	if(FIXED_COLS == 0) FIXED_COLS = COLS;

	update_viewport();

	OPTS.colors = OPTS.colors && has_colors();
	if(OPTS.colors){
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK); // Apple
		init_pair(2, OPTS.fore, OPTS.back); // Snake
	}
}

void update_viewport(){
	STARTLINE = (LINES - FIXED_LINES) / 2;
	STARTCOL = (COLS - FIXED_COLS) / 2;

	ENDLINE = STARTLINE + FIXED_LINES;
	ENDCOL = STARTCOL + FIXED_COLS;
}

void colorize(int pair){
	if(!OPTS.colors) return;
	attrset(COLOR_PAIR(pair));
}