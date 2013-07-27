#include "stdafx.h"
#include "CBot.h"

CBot::CBot(std::string spriteName, CWindow* pWindow)
{
	m_posX = 10;
	m_posY = 10;

	m_stepSize = 5;

	isUpPressed		= false;
	isDownPressed	= false;
	isLeftPressed	= false;
	isRightPressed	= false;

	m_spriteName = spriteName;
	m_pWindow = pWindow;

	init();
}


CBot::~CBot()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


bool CBot::userInput(SDL_Event* key)
{
	if (key->type == SDL_KEYDOWN)
	{
		switch (key->key.keysym.sym)
		{
		case SDLK_UP:
			isUpPressed = true;
			return true;
			break;

		case SDLK_DOWN:
			isDownPressed = true;
			return true;
			break;

		case SDLK_LEFT:
			isLeftPressed = true;
			return true;
			break;

		case SDLK_RIGHT:
			isRightPressed = true;
			return true;
			break;
		}
	}
	else if (key->type == SDL_KEYUP)
	{
		switch (key->key.keysym.sym)
		{
		case SDLK_UP:
			isUpPressed = false;
			return true;
			break;

		case SDLK_DOWN:
			isDownPressed = false;
			return true;
			break;

		case SDLK_LEFT:
			isLeftPressed = false;
			return true;
			break;

		case SDLK_RIGHT:
			isRightPressed = false;
			return true;
			break;
		}
	}

	return false;
}


void CBot::update()
{
	// General logic:
	// if (bot's next step is outside of screen)
	//		step to edge of screen;
	// else
	//		step normally

	if (isUpPressed)
	{
		if (m_posY - m_stepSize < 0)
		{
			m_posY = 0;
		}
		else
		{
			m_posY -= m_stepSize;
		}
	}
	if (isDownPressed)
	{
		if (m_posY + m_stepSize + m_pSprite->getHeight() > m_pWindow->getWindowHeight())
		{
			m_posY = m_pWindow->getWindowHeight() - m_pSprite->getHeight();
		}
		else
		{
			m_posY += m_stepSize;
		}
	}
	if (isLeftPressed)
	{
		if (m_posX - m_stepSize < 0)
		{
			m_posX = 0;
		}
		else
		{
			m_posX -= m_stepSize;
		}
	}
	if (isRightPressed)
	{
		if (m_posX + m_stepSize + m_pSprite->getWidth() > m_pWindow->getWindowWidth())
		{
			m_posX = m_pWindow->getWindowWidth() - m_pSprite->getWidth();
		} 
		else
		{
			m_posX += m_stepSize;
		}
	}
}


void CBot::render()
{
	m_pSprite->render(m_posX, m_posY);
}


void CBot::init()
{
	m_pSprite = new CSprite(m_spriteName, m_pWindow);
	m_pSprite->load();
}