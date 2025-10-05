#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "data.h"
#include "options.h"
#include "utils.h"
#include "multiplayer.h"
#include "networking.h"
#include "game.h"

int main(int argc, char **argv){
	if(argc > 1) getargs(argc, argv);
	initprogram();

	Snake gamer = {OPTS.head, OPTS.body, OPTS.fore, OPTS.back, OPTS.pair, {XCENTER}, {YCENTER}, LOBBY.startlen, 0, 0, true};
	LOBBY.players[0] = gamer;

	if(LOBBY.multiplayer){
		lobby_await();
	}

	countdown(LOBBY.countdown);

	Apple apple = {'O', 0, 0};
	apple_regen(&apple);

	while(true){
		erase();
		update_viewport();

		snake_input(&LOBBY.players[0]);

		for(int i = 0; i < LOBBY.players_num; i++){
			if(!LOBBY.players[i].alive) continue;

			snake_movement(&LOBBY.players[i]);
			apple_eat(&apple, &LOBBY.players[i]);
			snake_deathwin(&LOBBY.players[i]);

			for(int j = 0; j < LOBBY.players_num; j++)
				if(LOBBY.players[j].alive)
					snake_collision(&LOBBY.players[i], &LOBBY.players[j]);

			if(LOBBY.players[i].alive) snake_render(&LOBBY.players[i]);
		}

		apple_render(&apple);
		borders_render();

		refresh();
		usleep(LOBBY.delay);
	}

	endprogram(2);
}