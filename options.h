#include <argp.h>

struct Options{
	char head, body;
	int fore, back, pair, fixed_lines, fixed_cols;
	bool colors, corpses, trash;
};

struct Options OPTS = {
	.head = '@',
	.body = 'x',

	.fore = COLOR_WHITE,
	.back = COLOR_BLUE,
	.pair = 2,

	.fixed_lines = 0,
	.fixed_cols = 0,
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

		case 'F': OPTS.fore = atoi(arg); break;
		case 'B': OPTS.back = atoi(arg); break;
		case 'p':
			switch(atoi(arg)){
				case 1: OPTS.fore = COLOR_WHITE; OPTS.back = COLOR_GREEN; break;
				case 2: OPTS.fore = COLOR_BLACK; OPTS.back = COLOR_WHITE; break;
				case 3: OPTS.fore = COLOR_GREEN; OPTS.back = COLOR_RED; break;
			} break;

		case 'S': OPTS.fixed_lines = atoi(arg); break;
		case 's': OPTS.fixed_cols = atoi(arg); break;
		case 'n': OPTS.colors = false; break;

		case 'c': OPTS.corpses = true; break;
		case 't': OPTS.trash = true; break;
	}

	return 0;
}

int getargs(int argc, char **argv){
	struct argp_option options[] = {
		{"head-symbol", 'h', "SYM", 0, "Use SYM as snake's head"},
		{"body-symbol", 'b', "SYM", 0, "Use SYM as snake's body"},

		{"foreground", 'F', "COLOR", 0, "Use COLOR as the snake's foreground color"},
		{"background", 'B', "COLOR", 0, "Use COLOR as the snake's background color"},
		{"color-pair", 'p', "NUM", 0, "Use NUM default snake color scheme"},

		{"fixed-lines", 'S', "LINES", 0, "Specify LINES as the game's vertical size"},
		{"fixed-cols", 's', "COLS", 0, "Specify COLS as the game's horizontal size"},
		{"no-colors", 'n', 0, 0, "Run program without colors"},

		{"corpses", 'c', 0, 0, "Enable corpse as trash after snake death"},
		{"trash", 't', 0, 0, "Enable trash generation during game"},
		{0}
	};
	struct argp argp = {options, parse_opt};

	argp_program_version = "AkeOnline 0.2";
	argp_program_bug_address = "ascaniolamp@gmail.com";

	return argp_parse(&argp, argc, argv, 0, 0, 0);
}