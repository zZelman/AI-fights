#include "stdafx.h"
#include "CUserControlled_Bot.h"

CUserControlled_Bot::CUserControlled_Bot(std::string spriteName, CWindow* pWindow)
	: CBot(spriteName, pWindow)
{
	float x = 10;
	float y = 10;
	CVector2f* min = new CVector2f(x, y);
	CVector2f* max = new CVector2f(x + m_pSprite->getWidth(), y + m_pSprite->getHeight());
	m_pAABB = new CAABB_f(min, max);

	m_stepSize = 5;

	isUpPressed		= false;
	isDownPressed	= false;
	isLeftPressed	= false;
	isRightPressed	= false;
}


CUserControlled_Bot::~CUserControlled_Bot()
{
	CBot::~CBot();
}


bool CUserControlled_Bot::userInput(SDL_Event* key)
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


void CUserControlled_Bot::update()
{
	// General logic:
	// if (bot's next step is outside of screen)
	//		step to edge of screen;
	// else
	//		step normally

	CVector2f* pMin = m_pAABB->getMin();

	if (isUpPressed)
	{
		if (pMin->y - m_stepSize < 0)
		{
			m_pAABB->setMinY(0);
		}
		else
		{
			m_pAABB->setMinY(pMin->y - m_stepSize);
		}
	}
	if (isDownPressed)
	{
		if (pMin->y + m_stepSize + m_pSprite->getHeight() > m_pWindow->getWindowHeight())
		{
			m_pAABB->setMinY(m_pWindow->getWindowHeight() - m_pSprite->getHeight());
		}
		else
		{
			m_pAABB->setMinY(pMin->y + m_stepSize);
		}
	}
	if (isLeftPressed)
	{
		if (pMin->x - m_stepSize < 0)
		{
			m_pAABB->setMinX(0);
		}
		else
		{
			m_pAABB->setMinX(pMin->x - m_stepSize);
		}
	}
	if (isRightPressed)
	{
		if (pMin->x + m_stepSize + m_pSprite->getWidth() > m_pWindow->getWindowWidth())
		{
			m_pAABB->setMinX(m_pWindow->getWindowWidth() - m_pSprite->getWidth());
		}
		else
		{
			m_pAABB->setMinX(pMin->x + m_stepSize);
		}
	}
}