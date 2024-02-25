#include <argp.h>

struct Options{
	int predef;
	bool colors, corpses, trash;
};

struct Options OPTS = {
	.colors = true,
	.predef = 2,

	.corpses = false,
	.trash = false
};

static int parse_opt(int key, char *arg, struct argp_state *state);
int getargs(int argc, char **argv);

static int parse_opt(int key, char *arg, struct argp_state *state){
	switch(key){
		case 'n': OPTS.colors = false; break;
		case 'd': OPTS.predef = atoi(arg); break;
	}

	return 0;
}

int getargs(int argc, char **argv){
	struct argp_option options[] = {
		{"no-colors", 'n', 0, 0, "Run program without colors"},
		{"default", 'd', "NUM", 0, "Use NUM default snake color scheme"},
		{0}
	};
	struct argp argp = {options, parse_opt};

	argp_program_version = "AkeOnline 0.2";
	argp_program_bug_address = "ascaniolamp@gmail.com";

	return argp_parse(&argp, argc, argv, 0, 0, 0);
}