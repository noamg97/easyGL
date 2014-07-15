#include "Game.h"

int main()
{
	Game game;
	if(game.Initialize())
		return 1;

	return game.Run();
}