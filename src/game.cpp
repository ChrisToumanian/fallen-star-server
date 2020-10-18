#include "game.h"

Game::Game(Server* _server)
{
    Map::load_maps(&maps);
    std::cout << "Map loaded: " << maps[0]->name << std::endl;
    server = _server;
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

void Game::add_player(int server_id, std::string uid)
{
    if (!uid.empty()) // existing player
    {
        std::vector<std::string> settings = Reader::get_file_lines(players_filename);
        for (int i = 0; i < settings.size(); i++)
        {
            std::vector<std::string> setting = Reader::split(settings[i], ",");
            if (setting[0] == uid)
            {
                Player* player = new Player();
                player->username = setting[1];
                player->server_id = server_id;
                player->map = maps[starting_map - 1];
                server->broadcast("[" + player->username + "] joined the game.");
                log(player->username, "connected");
                server->send_to(server_id, player->map->message);
                server->send_to(server_id, "Players online: " + std::to_string(get_players_online()));
                players.push_back(player);
            }
        }
    }
    else // new player
    {
        Player* player = new Player();
        player->username = "player#" + std::to_string(server_id);
        player->server_id = server_id;
        player->map = maps[starting_map - 1];
        server->broadcast("[" + player->username + "] joined the game.");
        log(player->username, "connected");
        server->send_to(server_id, player->map->message);
        server->send_to(server_id, "Players online: " + std::to_string(get_players_online()));
        players.push_back(player);
    }
}

void Game::remove_player(Player* player)
{
    int i = 0;
    for (auto& p : players)
    {
        if (p->server_id == player->server_id)
        {
            players.erase(players.begin() + i);
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

std::string Game::command(int server_id, std::string message)
{
    Player* player = get_player(server_id);

    // Break into vector
    std::vector<std::string> cmd = Reader::split(message, " ");

    // Iterate through words
    if (cmd[0] == "/uid")
    {
        if (cmd.size() > 1)
        {
            add_player(server_id, cmd[1]);
        }
        else
        {
            add_player(server_id, "");
        }
    }
    else if (player == NULL)
    {
        return "";
    }
    else if (cmd[0] == "/help") // help
    {
        return "/disconnect, /quit, /exit\r\n/help\r\n/yell\r\n/name\r\n/say\r\n/teleport, /tp\r\n/emote, /me\r\n/whisper\r\n/coordinates, /coords";
    }
    else if (cmd[0] == "/connected")
    {
        add_player(server_id, "");
    }
    else if (cmd[0] == "/disconnected")
    {
        server->broadcast("[" + player->username + "] logged out.");
        log(player->username, "disconnected");
    }
    else if (cmd[0] == "/disconnect" || cmd[0] == "/quit" || cmd[0] == "/exit") // disconnect
    {
        server->disconnect(player->server_id);
    }
    else if (cmd[0] == "/name" && cmd.size() > 1) // change username
    {
        std::string original_name = player->username;
        player->username = cmd[1];
        server->broadcast("[" + original_name + "] changed name to " + cmd[1]);
        log(player->username, "changed name to " + cmd[1]);
    }
    else if (cmd[0] == "/coordinates" || cmd[0] == "/coords")
    {
        return(std::to_string((int)player->transform.position.x) + ", " + std::to_string((int)player->transform.position.y));
    }
    else if (cmd[0] == "/teleport" || cmd[0] == "/tp") // teleport to another player
    {
        return("You teleport to " + cmd[1]);
    }
    else if (cmd[0] == "/emote" || cmd[0] == "/me") // emote
    {
        std::string msg = Reader::join(cmd, 1);
        server->broadcast(player->username + " " + msg);
        log(player->username, "emotes " + msg);
    }
    else if (cmd[0] == "/whisper") // whisper
    {
        std::string msg = Reader::join(cmd, 2);
        server->send_to(get_player(cmd[1])->server_id, player->username + " whispers " + msg);
    }
    else if (cmd[0] == "/yell") // yell
    {
        std::string msg = Reader::join(cmd, 1);
        server->broadcast("[" + player->username + "] yells " + msg);
        log(player->username, "yells " + msg);
    }
    else if (cmd[0] == "/say") // say
    {
        std::string msg = Reader::join(cmd, 1);
        server->broadcast("[" + player->username + "] " + msg);
        log(player->username, msg);
    }
    else if (cmd[0][0] != '/') // default to say
    {
        std::string msg = Reader::join(cmd);
        server->broadcast("[" + player->username + "] " + msg);
        log(player->username, msg);
    }
	else if (cmd[0] == "/stats")
	{
		std::string stats = "Lvl " + std::to_string(player->level) + " " + player->race + " " + player->game_class + "\r\n";
		return stats;
	}
    else
    {
        return "Unknown command. Type \"/help\" for help.";
    }

    return "";
}