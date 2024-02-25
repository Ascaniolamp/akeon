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

	Snake snakes[MAXPLAYERS] = {
		{OPTS.head, OPTS.body, OPTS.fore, OPTS.back, OPTS.pair, {YCENTER}, {XCENTER}, 3, 0, 0, true}
	};

	Apple apple = {'O', 0, 0};
	apple_regen(&apple);

	while(true){
		erase();

		snake_movement(&snakes[0]);

		for(int i=0; i<MAXPLAYERS; i++){
			if(!snakes[i].alive) continue;

			bool in_apple = (snakes[i].ybody[0] == apple.ypos) && (snakes[i].xbody[0] == apple.xpos);
			if(in_apple) apple_eat(&apple, &snakes[i]);

			snake_deathwin(&snakes[i]);
			if(!snakes[i].alive) continue;

			snake_render(&snakes[i]);
		}

		apple_render(&apple);
		borders_render();

		refresh();
		usleep(delay);
	}

	endprogram(2);
}