#pragma once

#include <argp.h>
#include <uchar.h>

struct Options{
	char head, body;
	int fore, back, pair;

	int border;
	char borders[2][9];

	bool colors;
};

struct Options OPTS = {
	.head = '@',
	.body = 'x',
	.fore = COLOR_WHITE,
	.back = COLOR_BLUE,
	.pair = 2,

	.border = 0,
	.borders = { // TODO: add custom option
		{
			'+', '-', '+', // +-+
			'|', ' ', '|', // | |
			'+', '-', '+', // +-+
		},
		{
			'=', '=', '=', // ===
			'|', ' ', '|', // | |
			'=', '=', '=', // ===
		},
	},

	.colors = true,
};

struct Lobby{
	int host_addr;
	bool multiplayer;

	Snake players[MAXPLAYERS];
	int players_num;

	bool can_stop, back_die, diagonal;

	int lines, cols;
	bool random_startpos, random_startdir;
	int startlen;

	int countdown, delay;
	float multiplier;
};

struct Lobby LOBBY = {
	.host_addr = 000000000000, // TODO
	.multiplayer = false,

	.players = {},
	.players_num = 4,

	.can_stop = false,
	.back_die = false,
	.diagonal = false, // TODO: implement actual movement

	.lines = 0,
	.cols = 0,
	.random_startpos = false,
	.random_startdir = false,
	.startlen = 3,
	.countdown = 3,
	.delay = 200000,
	.multiplier = 1,
};

enum Args {
	HEADSYM_ARG = 'h',
	BODYSYM_ARG = 'b',
	FOREGROUND_ARG = 'F',
	BACKGROUND_ARG = 'B',
	COLORPAIR_ARG = 'p',

	FIXEDLINES_ARG = 'l',
	FIXEDCOLS_ARG = 'c',
	NOCOLORS_ARG = 'n',
	BORDERSTYLE_ARG = 's',

	CANSTOP_ARG = 0x001,
	BACKDIE_ARG = 0x002,
	DIAGONAL_ARG = 0x003,
	RANDOMSTARTPOS_ARG = 0x004,
	RANDOMSTARTDIR_ARG = 0x005,
	STARTLEN_ARG = 0x006,
	COUNTDOWN_ARG = 0x007,
	DELAY_ARG = 0x008,
	MULTIPLIER_ARG = 0x009,
};

static int parse_opt(int key, char *arg, struct argp_state *state);
int getargs(int argc, char **argv);

static int parse_opt(int key, char *arg, struct argp_state *state){
	switch(key){
		case HEADSYM_ARG: OPTS.head = arg[0]; break;
		case BODYSYM_ARG: OPTS.body = arg[0]; break;
		case FOREGROUND_ARG: OPTS.fore = atoi(arg); break;
		case BACKGROUND_ARG: OPTS.back = atoi(arg); break;
		case COLORPAIR_ARG:
			switch(atoi(arg)){
				case 1: OPTS.fore = COLOR_WHITE; OPTS.back = COLOR_GREEN; break;
				case 2: OPTS.fore = COLOR_BLACK; OPTS.back = COLOR_WHITE; break;
				case 3: OPTS.fore = COLOR_GREEN; OPTS.back = COLOR_RED; break;
			} break;

		case FIXEDLINES_ARG: LOBBY.lines = atoi(arg); break;
		case FIXEDCOLS_ARG: LOBBY.cols = atoi(arg); break;
		case NOCOLORS_ARG: OPTS.colors = false; break;
		case BORDERSTYLE_ARG: OPTS.border = atoi(arg); break;

		case CANSTOP_ARG: LOBBY.can_stop = !LOBBY.can_stop; break;
		case BACKDIE_ARG: LOBBY.back_die = !LOBBY.back_die; break;
		case DIAGONAL_ARG: LOBBY.diagonal = !LOBBY.diagonal; break;
		case RANDOMSTARTPOS_ARG: LOBBY.random_startpos = !LOBBY.random_startpos; break;
		case RANDOMSTARTDIR_ARG: LOBBY.random_startdir = !LOBBY.random_startdir; break;
		case STARTLEN_ARG: LOBBY.startlen = atoi(arg); break;
		case COUNTDOWN_ARG: LOBBY.countdown = atoi(arg); break;
		case DELAY_ARG: LOBBY.delay = atoi(arg); break;
		case MULTIPLIER_ARG: LOBBY.multiplier = atoi(arg); break;
	}
	return 0;
}

int getargs(int argc, char **argv){
	struct argp_option options[] = {
		{"head-symbol", HEADSYM_ARG, "SYM", 0, "Use SYM as snake's head"},
		{"body-symbol", BODYSYM_ARG, "SYM", 0, "Use SYM as snake's body"},
		{"foreground", FOREGROUND_ARG, "COLOR", 0, "Use COLOR as the snake's foreground color"},
		{"background", BACKGROUND_ARG, "COLOR", 0, "Use COLOR as the snake's background color"},
		{"color-pair", COLORPAIR_ARG, "NUM", 0, "Use NUM default snake color scheme"},

		{"fixed-lines", FIXEDLINES_ARG, "LINES", 0, "Specify LINES as the game's vertical size"},
		{"fixed-cols", FIXEDCOLS_ARG, "COLS", 0, "Specify COLS as the game's horizontal size"},
		{"no-colors", NOCOLORS_ARG, 0, 0, "Run program without colors"},
		{"border-style", BORDERSTYLE_ARG, "NUM", 0, "Use NUM style for the borders"},

		{"can-stop", CANSTOP_ARG, 0, 0, "Snakes stop when going backwards"},
		{"back-die", BACKDIE_ARG, 0, 0, "Snakes die when going backwards"},
		{"diagonal", DIAGONAL_ARG, 0, 0, "Snakes can move diagonally"},
		{"random-startpos", RANDOMSTARTPOS_ARG, 0, 0, "Snakes spawn in a random position"},
		{"random-startdir", RANDOMSTARTDIR_ARG, 0, 0, "Snakes spawn with a random starting direction"},
		{"start-length", STARTLEN_ARG, "NUM", 0, "Snakes spawn with a length of NUM"},
		{"start-countdown", COUNTDOWN_ARG, "NUM", 0, "Game starts after NUM seconds"},
		{"frame-delay", DELAY_ARG, "NUM", 0, "Frames are NUM microseconds long"},
		{"delay-multiplier", MULTIPLIER_ARG, "NUM", 0, "The rate at which the frame delay increments"},

		{0}
	};
	struct argp argp = {options, parse_opt};

	argp_program_version = "AkeOnline 0.3";
	argp_program_bug_address = "ascaniolamp@gmail.com";

	return argp_parse(&argp, argc, argv, 0, 0, 0);
}