#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include "server.h"

int port = 25566;
Server* server;
std::string server_name = "USWest";
std::string game_name = "Fallen Star 1.0";
std::string motd = "Events: Construction Chaos";

time_t time_raw;
struct tm * timeinfo;
char time_buffer[80];

void start();
void stop();
std::string receive(Client* client, std::string message);
std::string command(Client* client, std::string message);
void log(std::string name, std::string message);

int main(int argc, char *argv[])
{
	start();
}

void start()
{
	// Start server
	std::cout << "Initializing server..." << std::endl;
	server = new Server(port, receive);
    server->welcome_message = "Connected to " + server_name + "!\r\n" + game_name + "\r\n" + motd;
	server->start();
}

void stop()
{
	server->stop();
}

std::string receive(Client* client, std::string message)
{
    return command(client, message);
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
        // Break into vector
        bool command_added = false;
        std::string log_message = ""; 
        std::string end_message = "";
        std::string tmp;
        std::stringstream stream(message);
        std::vector<std::string> words;
        while (stream >> tmp)
        {
            words.push_back(tmp);
            if (command_added == true)
                end_message += tmp + " ";
            log_message += tmp + " ";
            command_added = true;
        }

        // Iterate through words
        std::string cmd = words[0];
        if (cmd == "/help") // help
        {
            return("/disconnect, /quit, /exit\r\n/help\r\n/yell\r\n/name\r\n/say\r\n/teleport, /tp\r\n/emote, /me\r\n/whisper");
        }
        else if (cmd == "/connected")
        {
            server->broadcast("[" + client->nickname + "] joined the game.");
            log(client->nickname, "connected");
        }
        else if (cmd == "/disconnected")
        {
            server->broadcast("[" + client->nickname + "] logged out.");
            log(client->nickname, "disconnected");
        }
        else if (cmd == "/disconnect" || cmd == "/quit" || cmd == "/exit") // disconnect
        {
            server->disconnect(client->id);
            log(client->nickname, "connected");
        }
        else if (cmd == "/name") // change username
        {
            client->nickname = words[1];
            server->broadcast("[" + client->nickname + "] changed name to " + words[1]);
            log(client->nickname, "changed name to " + words[1]);
        }
        else if (cmd == "/teleport" || cmd == "/tp") // teleport to another player
        {
            return("You teleport to " + words[1]);
        }
        else if (cmd == "/emote" || cmd == "/me") // emote
        {
            server->broadcast(client->nickname + " " + end_message);
            log(client->nickname, "emotes " + end_message);
        }
        else if (cmd == "/whisper") // whisper
        {
            std::string msg = "";
            for (int i = 2; i < words.size(); i++)
                msg += words[i] + " ";

            server->send_to(words[1], client->nickname + " whispers " + msg);
        }
        else if (cmd == "/yell") // yell
        {
            std::string msg = "";
            for (int i = 2; i < words.size(); i++)
                msg += words[i] + " ";

            server->broadcast("[" + client->nickname + "] yells " + end_message);
            log(client->nickname, "yells " + end_message);
        }
        else if (cmd == "/say") // say
        {
            server->broadcast("[" + client->nickname + "] " + end_message);
            log(client->nickname, end_message);
        }
        else // default to say
        {
            server->broadcast("[" + client->nickname + "] " + log_message);
            log(client->nickname, log_message);
        }
	}

    return "";
}