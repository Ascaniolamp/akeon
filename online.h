#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 7834

void host_server();
void connect_server();
Snake get_player();

void host_server(){
	// PLACEHOLDER
}

void connect_server(){
	// PLACEHOLDER
}

Snake get_player(int num){

	Snake player = {
		.head_symbol = '1',
		.body_symbol = 'I',
		.color_fore = randrange(1,255),
		.color_back = randrange(1,255),
		.color_pair = num + 2,

		.ybody = {randrange(1,FIXED_LINES-2)},
		.xbody = {randrange(1,FIXED_COLS-2)},
		.size = 3,
		.ydir = randrange(-1,1),
		.xdir = randrange(-1,1),

		.alive = true
	};

	if(OPTS.colors) init_pair(player.color_pair, player.color_fore, player.color_back);

	return player;
}