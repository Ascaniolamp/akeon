#include <argp.h>

struct Options{
	char head, body;
	int fore, back, pair;
	bool colors, corpses, trash;
};

struct Options OPTS = {
	.head = '@',
	.body = 'x',

	.fore = COLOR_WHITE,
	.back = COLOR_BLUE,
	.pair = 2,

	.colors = true,

	.corpses = false,
	.trash = false
};

static int parse_opt(int key, char *arg, struct argp_state *state);
int getargs(int argc, char **argv);

static int parse_opt(int key, char *arg, struct argp_state *state){
	switch(key){
		case 'h': OPTS.head = arg[0]; break;
		case 'b': OPTS.body = arg[0]; break;
		case 'n': OPTS.colors = false; break;
		case 'c': OPTS.corpses = true; break;
		case 'p':
			switch(atoi(arg)){
				case 1: OPTS.fore = COLOR_WHITE; OPTS.back = COLOR_GREEN; break;
				case 2: OPTS.fore = COLOR_BLACK; OPTS.back = COLOR_WHITE; break;
				case 3: OPTS.fore = COLOR_GREEN; OPTS.back = COLOR_RED; break;
			}
			break;
	}

	return 0;
}

int getargs(int argc, char **argv){
	struct argp_option options[] = {
		{"head-symbol", 'h', "SYM", 0, "Use SYM as snake's head"},
		{"body-symbol", 'b', "SYM", 0, "Use SYM as snake's body"},
		{"color-pair", 'p', "NUM", 0, "Use NUM default snake color scheme"},
		{"corpses", 'c', 0, 0, "Enable corpse as trash after snake death"},
		{"no-colors", 'n', 0, 0, "Run program without colors"},
		{0}
	};
	struct argp argp = {options, parse_opt};

	argp_program_version = "AkeOnline 0.2";
	argp_program_bug_address = "ascaniolamp@gmail.com";

	return argp_parse(&argp, argc, argv, 0, 0, 0);
}