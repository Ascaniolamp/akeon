void endprogram(int code);
void initprogram();

void endprogram(int code){
	endwin();

	switch(code){
		case 0: printf("You won!\n"); break;
		case 1: printf("You lost...\n"); break;
		case 2: exit(0);
		default: printf("ERROR (Exit code %d)\n",code); break;
	}

	exit(code);
}

void initprogram(){
	signal(SIGINT, endprogram);
	srandom(time(NULL));

	initscr();

	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	nonl();
	cbreak();
	echo();

	if(!has_colors()) return;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK); // Apple
	init_pair(2, COLOR_WHITE, COLOR_BLUE); // Snake
}