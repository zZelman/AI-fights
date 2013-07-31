// AI fights.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CGame.h"

int main(int argc, char* argv[])
{
	CGame* game = new CGame();
	game->startGame();

	//delete game;

	return EXIT_SUCCESS;
}

