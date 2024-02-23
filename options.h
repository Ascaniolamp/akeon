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
	.colors = true, // --no-colors
	.predef = false, // --default

	.corpses = false,
	.trash = false
};

void getargs(int argc, char const *argv[]);

void getargs(int argc, char const *argv[]){
	
}