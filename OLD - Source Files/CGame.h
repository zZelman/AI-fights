#ifndef CGAME_H
#define CGAME_H


#include "stdafx.h"
#include "CWindow.h"
#include "CPhysics.h"
#include "CMusic.h"
#include "CMap.h"
#include "CGenerator_Room.h"
#include "CGenerator_AI.h"

class CGame
{
public:
	CGame();
	~CGame();

	void startGame(); // enters the main game loop
	void stopGame(); // exits the main game loop

private:
	bool isGameRunning; // boolean that controls continued execution of the main game loop
	float fps_MS; // frames per second in ms
	int MAX_FRAME_SKIPS;

	CWindow* m_pGameWindow; // the window were everything is drawn
	CPhysics* m_pPhysics; // physics that control the game movements
	CMusic* m_pMusic; // game music
	CMap* m_pMap; // game map
	CTimer* m_pGameTimer;
	CGenerator_room* m_pRoomGenerator; // wrapper class for the rooms.
	CGenerator_AI* m_pAIGenerator; // wrapper class for the AI


	void gameLoop(); // main game loop
	void gameEvents(SDL_Event& event); // redirects user input appropriately
	void gameUpdate(); // update variables in objects
	void gameRender(); // render everything to the screen
};



#endif // !CGAME_H