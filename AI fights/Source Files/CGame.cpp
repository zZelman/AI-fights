#include "stdafx.h"
#include "CGame.h"

CGame::CGame()
{
	m_pGameWindow = new CWindow();
	m_pBot = new CUserControlled_Bot("redAI.png", m_pGameWindow);
	m_pAIBot = new CAI_Bot("blueAI.png", m_pGameWindow);
}


CGame::~CGame()
{
	delete m_pGameWindow;
	delete m_pBot;
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
		else
		{
			m_pBot->userInput(&event);
		}
	}
}


void CGame::gameUpdate()
{
	m_pBot->update();
	m_pAIBot->update();
}


void CGame::gameRender()
{
	// reset renderer states
	SDL_SetRenderDrawColor(m_pGameWindow->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderSetScale(m_pGameWindow->getRenderer(), 1.0f, 1.0f);
	SDL_RenderClear(m_pGameWindow->getRenderer());

	m_pBot->render();
	m_pAIBot->render();

	SDL_RenderPresent(m_pGameWindow->getRenderer());
}