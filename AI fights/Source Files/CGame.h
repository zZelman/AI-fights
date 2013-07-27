#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CTexture.h"

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
	CTexture* m_pTexture; // test texture rendering

	void gameLoop(); // main game loop
	void userInput(SDL_Event& event); // redirects user input appropriately
	void gameUpdate(); // update variables in objects
	void gameRender(); // render everything to the screen
};
