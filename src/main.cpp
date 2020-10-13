#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include "server.h"
#include "reader.h"
#include "player.h"

int port = 25566;
int map = 0;
int max_players = 30;
time_t time_raw;
struct tm * timeinfo;
char time_buffer[80];
Server* server;
std::vector<Player*> players;
std::string server_name = "USWest";
std::string game_name = "Fallen Star 1.0";
std::string motd = "Construction Event";
std::string config_filename = "server.yml";

void read_config();
void start();
void stop();
void log(std::string name, std::string message);
std::string receive(Client* client, std::string message);
std::string command(Client* client, std::string message);
Player* get_player(int server_id);

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
    }
}

void start()
{
	// Start server
	std::cout << "Initializing server..." << std::endl;
	server = new Server(port, receive);
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

void log(std::string name, std::string message)
{
	// Get current time
	time (&time_raw);
	timeinfo = localtime(&time_raw);
	strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);
	std::string time(time_buffer);
    
    // Output log message
    std::cout << "[" << time << "] [" << name << "] " << message << std::endl;
}

std::string command(Client* client, std::string message)
{
    // Server message
	if (client == NULL)
	{
		log("Server", message);
	}
	else // Client message
	{
        Player* player = get_player(client->id);

        // Break into vector
        std::vector<std::string> words = Reader::split(message, " ");
        std::string cmd = words[0];

        // Iterate through words
        if (cmd == "/help") // help
        {
            return("/disconnect, /quit, /exit\r\n/help\r\n/yell\r\n/name\r\n/say\r\n/teleport, /tp\r\n/emote, /me\r\n/whisper");
        }
        else if (cmd == "/connected")
        {
            Player* player = new Player();
            player->server_id = client->id;
            server->broadcast("[" + player->username + "] joined the game.");
            log(player->username, "connected");
            players.push_back(player);
        }
        else if (cmd == "/disconnected")
        {
            server->broadcast("[" + player->username + "] logged out.");
            log(player->username, "disconnected");
        }
        else if (cmd == "/disconnect" || cmd == "/quit" || cmd == "/exit") // disconnect
        {
            server->disconnect(client->id);
            log(player->username, "disconnected");
        }
        else if (cmd == "/name") // change username
        {
            player->username = words[1];
            server->broadcast("[" + player->username + "] changed name to " + words[1]);
            log(player->username, "changed name to " + words[1]);
        }
        else if (cmd == "/teleport" || cmd == "/tp") // teleport to another player
        {
            return("You teleport to " + words[1]);
        }
        else if (cmd == "/emote" || cmd == "/me") // emote
        {
            std::string msg = Reader::join(words, 2);
            server->broadcast(player->username + " " + msg);
            log(player->username, "emotes " + msg);
        }
        else if (cmd == "/whisper") // whisper
        {
            std::string msg = Reader::join(words, 2);
            server->send_to(words[1], player->username + " whispers " + msg);
        }
        else if (cmd == "/yell") // yell
        {
            std::string msg = Reader::join(words, 1);
            server->broadcast("[" + player->username + "] yells " + msg);
            log(player->username, "yells " + msg);
        }
        else if (cmd == "/say") // say
        {
            std::string msg = Reader::join(words, 1);
            server->broadcast("[" + player->username + "] " + msg);
            log(player->username, msg);
        }
        else // default to say
        {
            std::string msg = Reader::join(words);
            server->broadcast("[" + player->username + "] " + msg);
            log(player->username, msg);
        }
	}

    return "";
}

Player* get_player(int server_id)
{
    for (auto& player : players)
    {
        if (player->server_id == server_id)
            return player;
    }
    return NULL;
}