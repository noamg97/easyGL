#include "Game.h"

Game game;

int main()
{
	if(game.Initialize())
		return 1;

	return game.Run();
}