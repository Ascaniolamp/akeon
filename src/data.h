#pragma once

#define MAXLENGTH 150
#define MAXPLAYERS 10
float multiplier = 1;
int delay = 200000;

typedef struct{
	char head_symbol, body_symbol;
	int color_fore, color_back, color_pair;

	int ybody[MAXLENGTH], xbody[MAXLENGTH], size;
	int ydir, xdir;

	bool alive;
}Snake;

typedef struct{
	char symbol;
	int ypos, xpos;
}Apple;