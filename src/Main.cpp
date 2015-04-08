#include "Game.hpp"

int main(int argc, char *argv[])
{
	std::unique_ptr<Game> game(new Game);
	game->Run();
	
	return 0;
}
