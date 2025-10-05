#pragma once

#define MAXLENGTH 150
#define MAXPLAYERS 10

typedef struct{
	int x,y;
}xy;

typedef struct{
	char head_symbol, body_symbol;
	int color_fore, color_back, color_pair;

	int xbody[MAXLENGTH], ybody[MAXLENGTH], size;
	int xdir, ydir;

	bool alive;
}Snake;

typedef struct{
	char symbol;
	int ypos, xpos;
}Apple;
