#include <argp.h>

struct Options{
	bool
		colors,
		predef,

		corpses,
		trash
	;
};

struct Options OPTS = {
	.colors = true, // false = --no-colors
	.predef = false, // true = --default

	.corpses = false,
	.trash = false
};

void getargs(int argc, char **argv);

void getargs(int argc, char **argv){
	argp_program_version = "AkeOnline 0.2";
	argp_program_bug_address = "ascaniolamp@gmail.com";

	argp_parse(0, argc, argv, 0, 0, 0);
}