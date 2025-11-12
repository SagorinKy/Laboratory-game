#include <iostream>

#include "fight/gameManager.h"

int main()
{
	GameManager* game = new GameManager(1);
	game->chooseFighter();
	game->runFight();

	return 0;
}
