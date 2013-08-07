#include "stdafx.h"
#include "CGame.h"

CGame::CGame()
{
	int fps = 80;
	fps_MS = SecToMS(1 / fps);

	MAX_FRAME_SKIPS = 1000;

	m_pGameWindow	= new CWindow();

	m_pPhysics		= new CPhysics();

	m_pGameTimer	= new CTimer();

	m_pMusic		= new CMusic();

	m_pMap			= new CMap(m_pGameWindow, "Resource Files/Maps/testing.txt");

	m_pRoomGenerator = new CGenerator_room(m_pGameWindow, m_pMap, m_pPhysics, SecToMS(0));
	m_pAIGenerator	= new CGenerator_AI(m_pGameWindow, m_pMap, m_pPhysics, SecToMS(0),
	                                    m_pRoomGenerator->getRooms());

	//m_pUserBot		= new CUserControlled_Bot(m_pGameWindow, m_pMap, "Resource Files/Sprites/ninja (46h 32w).png", 32, 46, 2, 6);

	//m_pAIBot		= new CAI_Bot("blueAI.png", m_pGameWindow);
}


CGame::~CGame()
{
	delete m_pGameWindow;
	m_pGameWindow = NULL;

	delete m_pPhysics;
	m_pPhysics = NULL;

	delete m_pGameTimer;
	m_pGameTimer = NULL;

	delete m_pMusic;
	m_pMusic = NULL;

	delete m_pMap;
	m_pMap = NULL;

	delete m_pRoomGenerator;
	m_pRoomGenerator = NULL;

	delete m_pAIGenerator;
	m_pAIGenerator = NULL;

	//delete m_pUserBot;
	//m_pUserBot = NULL;

	//delete m_pAIBot;
	//m_pAIBot = NULL;
}


void CGame::startGame()
{
	isGameRunning = true;
	gameLoop();
}


void CGame::stopGame()
{
	isGameRunning = false;
}


void CGame::gameLoop()
{
	SDL_Event events;

	//Uint32 beforeTime, afterTime;
	//Sint32 timeDiff, sleepTime;
	//Sint32 excessTime = 0;
	//
	//m_pGameTimer->start();
	//beforeTime = m_pGameTimer->getTime();

	while (isGameRunning)
	{
		gameEvents(events);
		gameUpdate();
		gameRender();

		//afterTime = m_pGameTimer->getTime();

		//timeDiff = afterTime - beforeTime;

		//if (timeDiff > SecToMS(2)) // if debugging is taking place or window is not selected etc..
		//{
		//	timeDiff = fps_MS;
		//}

		//sleepTime = fps_MS - timeDiff;

		//if (sleepTime > 0) // still have time in this frame
		//{
		//	SDL_Delay(sleepTime);
		//}
		//else
		//{
		//	excessTime = sleepTime;
		//}

		//beforeTime = m_pGameTimer->getTime(); // this is here because we may be doing updates below

		//// if this while loop enters, it means that the last frame rendered
		////		took longer than the individual frame render required by the fps.
		////	So, update the game (without rendering) until we get back to the required frame render time
		////		or reach an arbitrary maximum of frame skips
		//int renderSkips = 0;
		//while ((excessTime < fps_MS) && (sleepTime <= 0) && (renderSkips < MAX_FRAME_SKIPS))
		//{
		//	excessTime += fps_MS;
		//	gameUpdate();
		//	++renderSkips;
		//}

	}
	//assert(false);
}


void CGame::gameEvents(SDL_Event& event)
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			isGameRunning = false;
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isGameRunning = false;
		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			m_pGameWindow->updateSize();
		}
		else if (event.key.keysym.sym == SDLK_b)
		{
			int p = 0;
		}
		else if (event.key.keysym.sym == SDLK_c)
		{
			m_pRoomGenerator->clear();
			//m_pAIGenerator->clear();
		}
		else if (event.key.keysym.sym == SDLK_m && event.type == SDL_KEYDOWN)
		{
			m_pMap->swapIsStretched();
		}
		else if (m_pRoomGenerator->generate(event) == true) {}
		else if (m_pAIGenerator->generate(event) == true) {}
	}
}


void CGame::gameUpdate()
{
	m_pRoomGenerator->update();
	m_pAIGenerator->update();

	//m_pUserBot->update();

	//m_pPhysics->collisionDetection(m_pAIBot, m_pGameWindow);
	//m_pPhysics->applyGravity(m_pAIBot);
	//m_pAIBot->update();
}


void CGame::gameRender()
{
	// reset renderer states
	SDL_SetRenderDrawColor(m_pGameWindow->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderSetScale(m_pGameWindow->getRenderer(), 1.0f, 1.0f);
	SDL_RenderClear(m_pGameWindow->getRenderer());

	m_pMap->render();

	m_pRoomGenerator->render();
	m_pAIGenerator->render();

	//m_pUserBot->render();
	//m_pAIBot->render();

	SDL_RenderPresent(m_pGameWindow->getRenderer());
}