#include "stdafx.h"
#include "CGame.h"

CGame::CGame()
{
	m_pGameWindow = new CWindow();
	m_pTexture = new CTexture("foo.png", m_pGameWindow);
	m_pTexture->load();
}


CGame::~CGame()
{
	delete m_pGameWindow;
	delete m_pTexture;
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
	assert(false);
}


void CGame::userInput(SDL_Event& event)
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			isGameRunning = false;
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isGameRunning = false;
		}
	}
}


void CGame::gameUpdate()
{
	
}


void CGame::gameRender()
{
	// reset renderer states
	SDL_SetRenderDrawColor(m_pGameWindow->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderSetScale(m_pGameWindow->getRenderer(), 1.0f, 1.0f);
	SDL_RenderClear(m_pGameWindow->getRenderer());

	m_pTexture->setColor(255-32, 255-32, 255-32);
	m_pTexture->render(10, 10);

	SDL_RenderPresent(m_pGameWindow->getRenderer());
}