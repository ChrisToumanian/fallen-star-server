#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "server.h"
#include "game.h"
#include "reader.h"
#include "player.h"

int port = 25566;
int max_players = 30;
int map = 1;
Server* server;
Game* game;
std::string server_name = "USWest";
std::string game_name = "Fallen Star 1.0";
std::string motd = "Construction Event";
std::string config_filename = "server.yml";

void read_config();
void start();
void stop();
std::string receive(Client* client, std::string message);
std::string command(Client* client, std::string message);

int main(int argc, char *argv[])
{
    read_config();
	start();
}

void read_config()
{
    std::vector<std::string> settings = Reader::get_file_lines(config_filename);
    for (int i = 0; i < settings.size(); i++)
    {
        std::vector<std::string> setting = Reader::split(settings[i], ": ");
        if (setting[0] == "server-name")
            server_name = setting[1];
        else if (setting[0] == "motd")
            motd = setting[1];
        else if (setting[0] == "port")
            port = std::stoi(setting[1]);
        else if (setting[0] == "map")
            map = std::stoi(setting[1]);
    }
}

void start()
{
	// Start server
	std::cout << "Initializing server..." << std::endl;
	server = new Server(port, receive);
    game = new Game(server);
    game->starting_map = map;
    server->welcome_message = "Connected to " + server_name + "!\r\n" + game_name + "\r\n" + motd;
    server->port = port;
	server->start();
}

void stop()
{
	server->stop();
}

std::string receive(Client* client, std::string message)
{
    if (message.length() > 2)
    {
        Reader::rtrim(message);
        return command(client, message);
    }
    else
    {
        return "";
    }
}

std::string command(Client* client, std::string message)
{
    // Server message
	if (client == NULL)
	{
		game->log("Server", message);
	}
	else // Client message
	{
        return game->command(client->id, message);
    }
    return "";
}