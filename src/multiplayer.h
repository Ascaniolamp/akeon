#pragma once

#include <stdlib.h>
#include <math.h>

xy generate_startpos(int num);
xy generate_startdir(int num);
Snake create_player(int num);

xy generate_startpos(int num){
	xy startpos;

	if(LOBBY.random_startpos){
		startpos.x = randrange(1, GAMECOLS);
		startpos.y = randrange(1, GAMELINES);
	}else{
		startpos.x = randrange(1, GAMECOLS);
		startpos.y = randrange(1, GAMELINES);

//		TODO: fix grid
//		int num_sudlin = (int)sqrt(round_even(LOBBY.players_num));
//		int num_sudcol = round_even(LOBBY.players_num / num_sudlin);
//		startpos.x = get_section(GAMECOLS, num_sudcol, ???);
//		startpos.y = get_section(GAMELINES, num_sudlin, ???);
	}

	return startpos;
}

xy generate_startdir(int num){
	xy startdir;

	if(!LOBBY.random_startdir){
		startdir.x = 0;
		startdir.y = 0;
	}else{
		startdir.x = randrange(0, 1);
		startdir.y = randrange(0, 1);

		if(startdir.x == 0) startdir.x = -1;
		if(startdir.y == 0) startdir.y = -1;

		bool start_diagonal = (startdir.x != 0 && startdir.y != 0);
		if(!LOBBY.diagonal && start_diagonal){
			int xory = randrange(0, 1);

			if(xory == 0) startdir.x = 0;
			else startdir.y = 0;
		}
	}

	return startdir;
}

Snake create_player(int num){
	xy startpos = generate_startpos(num);
	xy startdir = generate_startdir(num);

	Snake player = {
		.head_symbol = num + 48,
		.body_symbol = num + 48,
		.color_fore = randrange(1,255),
		.color_back = randrange(1,255),
		.color_pair = num + 2,

		.ybody = {startpos.y},
		.xbody = {startpos.x},
		.size = LOBBY.startlen,
		.xdir = startdir.x,
		.ydir = startdir.y,

		.alive = true
	};

	if(OPTS.colors) init_pair(player.color_pair, player.color_fore, player.color_back);

	return player;
}