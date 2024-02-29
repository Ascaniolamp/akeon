#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

void host_server();
Snake get_player();

void host_server(){
	#define PORTNUM 7834

	int mysocket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("192.168.0.8");
	dest.sin_port = htons(PORTNUM);

	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
}

Snake get_player(){
	Snake player = {'1', 'I', randrange(1,255), randrange(1,255), 0, {10}, {13}, 3, randrange(-1,1), randrange(-1,1), true};
	return player;
}