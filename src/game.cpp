#include "game.h"

Game::Game(Server* _server)
{
    Map::load_maps(maps);
    server = _server;
}

std::string Game::command(int server_id, std::string message)
{
    Player* player = get_player(server_id);

    // Break into vector
    std::vector<std::string> words = Reader::split(message, " ");
    std::string cmd = words[0];

    // Iterate through words
    if (cmd == "/help") // help
    {
        return "/disconnect, /quit, /exit\r\n/help\r\n/yell\r\n/name\r\n/say\r\n/teleport, /tp\r\n/emote, /me\r\n/whisper\r\n/coordinates, /coords";
    }
    else if (cmd == "/connected")
    {
        add_player(server_id);
    }
    else if (cmd == "/disconnected")
    {
        server->broadcast("[" + player->username + "] logged out.");
        log(player->username, "disconnected");
        remove_player(player);
    }
    else if (cmd == "/disconnect" || cmd == "/quit" || cmd == "/exit") // disconnect
    {
        server->disconnect(player->server_id);
        remove_player(player);
    }
    else if (cmd == "/name") // change username
    {
        std::string original_name = player->username;
        player->username = words[1];
        server->broadcast("[" + original_name + "] changed name to " + words[1]);
        log(player->username, "changed name to " + words[1]);
    }
    else if (cmd == "/coordinates" || cmd == "/coords")
    {
        return(std::to_string((int)player->transform.position.x) + ", " + std::to_string((int)player->transform.position.y));
    }
    else if (cmd == "/teleport" || cmd == "/tp") // teleport to another player
    {
        return("You teleport to " + words[1]);
    }
    else if (cmd == "/emote" || cmd == "/me") // emote
    {
        std::string msg = Reader::join(words, 1);
        server->broadcast(player->username + " " + msg);
        log(player->username, "emotes " + msg);
    }
    else if (cmd == "/whisper") // whisper
    {
        std::string msg = Reader::join(words, 2);
        server->send_to(get_player(words[1])->server_id, player->username + " whispers " + msg);
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
    else if (cmd[0] != '/') // default to say
    {
        std::string msg = Reader::join(words);
        server->broadcast("[" + player->username + "] " + msg);
        log(player->username, msg);
    }
    else
    {
        return "Unknown command. Type \"/help\" for help.";
    }

    return "";
}

Player* Game::get_player(int server_id)
{
    for (auto& player : players)
    {
        if (player->server_id == server_id)
            return player;
    }
    return NULL;
}

Player* Game::get_player(std::string username)
{
    for (auto& player : players)
    {
        if (player->username == username)
            return player;
    }
    return NULL;
}

int Game::get_players_online()
{
    if (players.size() > 0)
        return players.size();
    return 0;
}

void Game::add_player(int server_id)
{
    Player* player = new Player();
    player->server_id = server_id;
    player->username = "player#" + std::to_string(server_id);
    server->broadcast("[" + player->username + "] joined the game.");
    log(player->username, "connected");
    server->send_to(server_id, "Players online: " + std::to_string(get_players_online()));
    players.push_back(player);
}

void Game::remove_player(Player* player)
{
    int i = -1;
    for (auto& p : players)
    {
        if (p->server_id == player->server_id)
        {
            //players.erase(players.begin() + i);
            //delete player;
        }
        i++;
    }
}

void Game::log(std::string name, std::string message)
{
	// Get current time
	time (&time_raw);
	timeinfo = localtime(&time_raw);
	strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);
	std::string time(time_buffer);
    
    // Output log message
    std::cout << "[" << time << "] [" << name << "] " << message << std::endl;
}