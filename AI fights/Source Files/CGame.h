#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CBot.h"

class CGame
{
public:
	CGame();
	~CGame();

	void startGame(); // enters the main game loop
	void stopGame(); // exits the main game loop

private:
	bool isGameRunning; // boolean that controlles continued exicution of the main game loop
	CWindow* m_pGameWindow; // the window were everything is drawn
	CBot* m_pBot; // first bot to be played :D

	void gameLoop(); // main game loop
	void userInput(SDL_Event& event); // redirects user input appropriately
	void gameUpdate(); // update variables in objects
	void gameRender(); // render everything to the screen
};
