#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "options.h"
#include "utils.h"
#include "game.h"

int main(int argc, char **argv){
	getargs(argc, argv);
	initprogram();

	int YCENTER = (LINES-2)/2, XCENTER = (COLS-2)/2;
	int players = 4;

	Snake snakes[MAXPLAYERS] = {
		{OPTS.head, OPTS.body, OPTS.fore, OPTS.back, OPTS.pair, {YCENTER}, {XCENTER}, 3, 0, 0, true},
		{'1', 'c', COLOR_RED, COLOR_MAGENTA, -1, {10}, {13}, 3, 0, 0, true},
		{'2', 'c', COLOR_CYAN, COLOR_YELLOW, -1, {20}, {10}, 3, 0, 0, true},
		{'3', 'c', COLOR_MAGENTA, COLOR_BLUE, -1, {18}, {16}, 3, 0, 0, true}
	};

	// assign colors
	if(OPTS.colors){
		for(int i=1; i<players; i++){
			int pair = i+10;
			init_pair(pair, snakes[i].color_fore, snakes[i].color_back);
			snakes[i].color_pair = pair;
		}
	}

	Apple apple = {'O', 0, 0};
	apple_regen(&apple);

	while(true){
		erase();
		update_viewport();

		snake_movement(&snakes[0]);

		for(int i=0; i<players; i++){
			if(!snakes[i].alive) continue;

			bool in_apple = (snakes[i].ybody[0] == apple.ypos) && (snakes[i].xbody[0] == apple.xpos);
			if(in_apple) apple_eat(&apple, &snakes[i]);

			snake_deathwin(&snakes[i]);

			for(int j=0; j<players; j++) snake_collision(&snakes[i], &snakes[j]);

			if(snakes[i].alive) snake_render(&snakes[i]);
		}

		apple_render(&apple);
		borders_render();

		refresh();
		usleep(delay);
	}

	endprogram(2);
}