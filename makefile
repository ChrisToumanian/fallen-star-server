make:
	g++ -o bin/server -L/lib src/main.cpp src/server.cpp src/entity.cpp src/player.cpp src/reader.cpp src/transform.cpp src/map.cpp src/game.cpp