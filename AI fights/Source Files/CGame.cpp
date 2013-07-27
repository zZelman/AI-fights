#include "stdafx.h"
#include "CGame.h"

CGame::CGame()
{
	m_pGameWindow = new CWindow();
	m_pBot = new CBot("redAI.png", m_pGameWindow);
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
		userInput(events);
		gameUpdate();
		gameRender();
	}
	//assert(false);
}


void CGame::userInput(SDL_Event& event)
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
		else 
		{
			m_pBot->userInput(&event);
		}
	}
}


void CGame::gameUpdate()
{
	m_pBot->update();
}


void CGame::gameRender()
{
	// reset renderer states
	SDL_SetRenderDrawColor(m_pGameWindow->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderSetScale(m_pGameWindow->getRenderer(), 1.0f, 1.0f);
	SDL_RenderClear(m_pGameWindow->getRenderer());

	m_pBot->render();

	SDL_RenderPresent(m_pGameWindow->getRenderer());
}