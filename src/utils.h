#pragma once

#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define GAMELINES LOBBY.lines - 2
#define GAMECOLS LOBBY.cols - 2
int STARTLINE, STARTCOL;
int ENDLINE, ENDCOL;
int YCENTER, XCENTER;

int randrange(int min, int max){ return random() % (max + 1 - min) + min; }
int get_section(int size, int sections, int chosen){ return (size / sections) * chosen; }
int round_even(int num){ if(num % 2 != 0) return num + 1; else return num; }

void clearln();
void clearlny(int y);
void update_viewport();
void borders_render();
void colorize(int pair);

void centered_text(int x, int y, const char *txt);
void countdown(int seconds);

void endprogram(int code);
void initprogram();

void clearln(){
	move(getcury(stdscr), 0);
	clrtoeol();
}

void clearlny(int y){
	move(y, 0);
	clrtoeol();
}

void update_viewport(){
	STARTLINE = (LINES - LOBBY.lines) / 2;
	STARTCOL = (COLS - LOBBY.cols) / 2;

	ENDLINE = STARTLINE + LOBBY.lines;
	ENDCOL = STARTCOL + LOBBY.cols;

	YCENTER = LINES / 2;
	XCENTER = COLS / 2;
}

void borders_render(){
	attrset(COLOR_PAIR(0));

	for(int i = STARTLINE; i < ENDLINE; i++){
		mvaddch(i, STARTCOL, OPTS.borders[OPTS.border][3]);
		mvaddch(i, ENDCOL - 1, OPTS.borders[OPTS.border][5]);
	}

	for(int i = STARTCOL; i < ENDCOL; i++){
		mvaddch(STARTLINE, i, OPTS.borders[OPTS.border][1]);
		mvaddch(ENDLINE - 1, i, OPTS.borders[OPTS.border][7]);
	}

	mvaddch(STARTLINE, STARTCOL, OPTS.borders[OPTS.border][0]);
	mvaddch(STARTLINE, ENDCOL - 1, OPTS.borders[OPTS.border][2]);
	mvaddch(ENDLINE - 1, STARTCOL, OPTS.borders[OPTS.border][6]);
	mvaddch(ENDLINE - 1, ENDCOL - 1, OPTS.borders[OPTS.border][8]);
}

void colorize(int pair){
	if(!OPTS.colors) return;
	attrset(COLOR_PAIR(pair));
}

void centered_text(int x, int y, const char *txt){
	int half = (int)(strlen(txt) / 2);
	mvaddstr(y, x - half, txt);
}

void countdown(int seconds){
	for(; seconds > 0; seconds--){
		clearln();
		update_viewport();

		char numstr[4];
		sprintf(numstr, "%d", seconds);
		centered_text(XCENTER, YCENTER, numstr);

		refresh();
		usleep(1000000);
	}
}

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
	setlocale(LC_ALL, "");

	initscr();

	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	nonl();
	cbreak();
	echo();

	if(LOBBY.lines == 0) LOBBY.lines = LINES;
	if(LOBBY.cols == 0) LOBBY.cols = COLS;

	update_viewport();

	OPTS.colors = OPTS.colors && has_colors();
	if(OPTS.colors){
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK); // Apple
		init_pair(2, OPTS.fore, OPTS.back); // Snake
	}
}
