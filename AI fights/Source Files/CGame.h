#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CUserControlled_Bot.h"
#include "CAI_Bot.h"
#include "CPhysics.h"

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
	CPhysics* m_pPhysics; // phisics that control the game movements

	CUserControlled_Bot* m_pUserBot; // first bot to be played :D
	CAI_Bot* m_pAIBot; // first atempt at AI :D

	void gameLoop(); // main game loop
	void gameEvents(SDL_Event& event); // redirects user input appropriately
	void gameUpdate(); // update variables in objects
	void gameRender(); // render everything to the screen
};
