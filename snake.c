#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "data.h"
#include "options.h"
#include "utils.h"
#include "online.h"
#include "game.h"

int main(int argc, char **argv){
	if(argc > 1) getargs(argc, argv);
	initprogram();

	int YCENTER = (LINES-2)/2, XCENTER = (COLS-2)/2;
	int players = 4;

	Snake snakes[MAXPLAYERS] = {
		{OPTS.head, OPTS.body, OPTS.fore, OPTS.back, OPTS.pair, {YCENTER}, {XCENTER}, 3, 0, 0, true},
		get_player(),
		get_player(),
		get_player()
	};

	// init snakes colors
	if(OPTS.colors){
		for(int i=1; i<players; i++){
			int pair = i+2;
			init_pair(pair, snakes[i].color_fore, snakes[i].color_back);
			snakes[i].color_pair = pair;

			snakes[i].ybody[0] = randrange(1,FIXED_LINES-2);
			snakes[i].xbody[0] = randrange(1,FIXED_COLS-2);
		}
	}

	Apple apple = {'O', 0, 0};
	apple_regen(&apple);

	while(true){
		erase();
		update_viewport();

		if(snakes[0].alive) snake_input(&snakes[0]);

		for(int i=0; i<players; i++){
			if(!snakes[i].alive) continue;

			snake_movement(&snakes[i]);
			apple_eat(&apple, &snakes[i]);
			snake_deathwin(&snakes[i]);

			for(int j=0; j<players; j++)
				if(snakes[j].alive)
					snake_collision(&snakes[i], &snakes[j]);

			if(snakes[i].alive) snake_render(&snakes[i]);
		}

		apple_render(&apple);
		borders_render();

		refresh();
		usleep(delay);
	}

	endprogram(2);
}