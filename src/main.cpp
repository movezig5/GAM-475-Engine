#include "Framework.h"
#include "Game.h"

#include "PCSNode.h"
#include "PCSTree.h"
#include "PCSTreeForwardIterator.h"
#include "PCSTreeReverseIterator.h"

Game *pGame = 0;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	pGame = new Game("Game", 800, 600);
	pGame->Run();
	delete pGame;
	return 0;
}

//--- End of File -------------------------------------------------------------
