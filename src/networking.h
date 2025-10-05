#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 7834

void server_host();
void client_connect();
void lobby_await();

void server_host(){
	// TODO
}

void client_connect(){
	// TODO
}

void lobby_await(){
	// TODO
	for(int i = 1; i < LOBBY.players_num; i++) LOBBY.players[i] = create_player(i);
	// TODO
}
