#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>

#include "options.h"
#include "utils.h"
#include "game.h"

int main(int argc, char const *argv[]){
	getargs(argc, argv);
	initprogram();

	Snake snake = {'@', 'x', COLOR_WHITE, COLOR_BLUE, {LINES/2}, {COLS/2}, 3, 0, 0};
	Apple apple = {'O', 0, 0};

	apple_regen(&apple);

	while(true){
		erase();

		snake_movement(&snake);

		bool in_apple = (snake.ybody[0] == apple.ypos) && (snake.xbody[0] == apple.xpos);
		if(in_apple) apple_eat(&apple, &snake);

		snake_deathwin(&snake);

		apple_render(&apple);
		snake_render(&snake);
		borders_render();

		refresh();
		usleep(delay);
	}

	endprogram(2);
}