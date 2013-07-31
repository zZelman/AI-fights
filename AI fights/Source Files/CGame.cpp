#include "stdafx.h"
#include "CGame.h"

CGame::CGame()
{
	m_pGameWindow	= new CWindow();

	m_pPhysics		= new CPhysics();

	m_pMusic		= new CMusic();

	m_pMap			= new CMap(m_pGameWindow, "testing.txt");

	m_pUserBot		= new CUserControlled_Bot(m_pGameWindow, "ninja (46h 32w).png", 32, 46, 2, 6);

	//m_pAIBot		= new CAI_Bot("blueAI.png", m_pGameWindow);
}


CGame::~CGame()
{
	delete m_pGameWindow;
	m_pGameWindow = NULL;

	delete m_pPhysics;
	m_pPhysics = NULL;

	delete m_pMusic;
	m_pMusic = NULL;

	delete m_pMap;
	m_pMap = NULL;

	delete m_pUserBot;
	m_pUserBot = NULL;

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
	while (isGameRunning)
	{
		gameEvents(events);
		gameUpdate();
		gameRender();
	}
	assert(false);
}


void CGame::gameEvents(SDL_Event& event)
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			//isGameRunning = false;
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isGameRunning = false;
		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			m_pGameWindow->updateSize();
		}
		else
		{
			m_pUserBot->userInput(&event);
		}
	}
}


void CGame::gameUpdate()
{
	m_pUserBot->update();

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
	m_pUserBot->render();
	//m_pAIBot->render();

	SDL_RenderPresent(m_pGameWindow->getRenderer());
}