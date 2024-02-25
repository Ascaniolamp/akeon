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

void apple_regen(Apple *apple);
void apple_eat(Apple *apple, Snake *snake);

void snake_movement(Snake *snake);
void snake_deathwin(Snake *snake);
void snake_collision(Snake *snake, Snake *s2);
void snake_die(Snake *snake);

void apple_render(Apple *apple);
void snake_render(Snake *snake);
void borders_render();

void borders_render(){
	attrset(COLOR_PAIR(0));

	for(int i=STARTLINE; i<ENDLINE; i++){
		mvaddch(i,STARTCOL,'|');
		mvaddch(i,ENDCOL-1,'|');
	}

	for(int i=STARTCOL; i<ENDCOL; i++){
		mvaddch(STARTLINE,i,'=');
		mvaddch(ENDLINE-1,i,'=');
	}
}

void apple_regen(Apple *apple){
	apple->ypos = randrange(STARTLINE+1,FIXED_LINES-2);
	apple->xpos = randrange(STARTCOL+1,FIXED_COLS-2);
}

void apple_eat(Apple *apple, Snake *snake){
	snake->size++;

	bool bad_apple;
	do{
		bad_apple = false;
		apple_regen(apple);
		
		for(int i=0; i<snake->size; i++)
			if((apple->ypos == snake->ybody[i]) && (apple->xpos == snake->xbody[i]))
				bad_apple = true;
	}while(bad_apple);

	delay *= multiplier;
}

void apple_render(Apple *apple){
	attrset(COLOR_PAIR(1));

	mvaddch(apple->ypos + STARTLINE, apple->xpos + STARTCOL, apple->symbol);

	attrset(COLOR_PAIR(0));
}

void snake_movement(Snake *snake){
	for(int i=snake->size-1; i>0; i--){
		snake->ybody[i] = snake->ybody[i-1];
		snake->xbody[i] = snake->xbody[i-1];
	}

	switch(getch()){
		case 'k': snake->ydir = -1; snake->xdir = 0; break;
		case 'j': snake->ydir = 1; snake->xdir = 0; break;
		case 'h': snake->ydir = 0; snake->xdir = -1; break;
		case 'l': snake->ydir = 0; snake->xdir = 1; break;
	}

	snake->ybody[0] += snake->ydir;
	snake->xbody[0] += snake->xdir;
}

void snake_deathwin(Snake *snake){
	bool out_borders = (snake->ybody[0] > FIXED_LINES-2 || snake->ybody[0] < 1) || (snake->xbody[0] > FIXED_COLS-2 || snake->xbody[0] < 1);
	if(out_borders) snake_die(snake);

	if(snake->size >= MAXLENGTH) endprogram(5);
}

void snake_collision(Snake *snake, Snake *s2){
	int i = 0;
	if(snake == s2) i = 1;

	for(i; i<s2->size; i++){
		bool in_body = (snake->ybody[0] == s2->ybody[i]) && (snake->xbody[0] == s2->xbody[i]);
		bool is_moving = (snake->ydir != 0) || (snake->xdir !=0);

		if(in_body && is_moving) snake_die(snake);
	}
}

void snake_die(Snake *snake){
	snake->alive = false;
	snake->size = -1;
}

void snake_render(Snake *snake){
	colorize(snake->color_pair);

	for(int i=1; i<snake->size; i++) mvaddch(snake->ybody[i] + STARTLINE, snake->xbody[i] + STARTCOL, snake->body_symbol);
	mvaddch(snake->ybody[0] + STARTLINE, snake->xbody[0] + STARTCOL, snake->head_symbol);

	attrset(COLOR_PAIR(0));
}