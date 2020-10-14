#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <ctime>
#include "server.h"
#include "reader.h"
#include "player.h"
#include "map.h"

class Game
{
public:
    Game(Server* _server);

    int starting_map = 1;
    Server* server;
    std::vector<Player*> players;
    std::vector<Map*> maps;
    time_t time_raw;
    struct tm * timeinfo;
    char time_buffer[80];

    std::string command(int server_id, std::string message);
    Player* get_player(int server_id);
    Player* get_player(std::string username);
    int get_players_online();
    void add_player(int server_id);
    void remove_player(Player* player);
    void log(std::string name, std::string message);
};

#endif