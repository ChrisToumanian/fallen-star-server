#ifndef SERVER_H
#define SERVER_H

#include <string> 
#include <string.h>
#include <vector>
#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> 

#define TRUE 1
#define FALSE 0

struct Client
{
	int id;
	int socket;
	std::string address;
	std::string nickname;
};

class Server
{
public:
	Server(int _port, std::string (*_callback)(Client*, std::string));

	bool running;
	int port;
	int max_clients;
	std::vector<Client> clients;
	std::string welcome_message;
	std::string (*callback)(Client*, std::string);

	void start();
	void stop();
	void loop();
	void broadcast(std::string message);
	void send_to(int client_id, std::string message);
	void disconnect(int client_id);
};

#endif
