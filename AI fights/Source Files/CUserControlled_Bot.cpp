#include "stdafx.h"
#include "CUserControlled_Bot.h"

CUserControlled_Bot::CUserControlled_Bot(CWindow* window, std::string fileName, 
										 int imageWidth, int imageHeight,
										 int numImages_rows, int numImages_columns)
	: CBot(window, fileName, 
	imageWidth, imageHeight, 
	numImages_rows, numImages_columns)
{
	float x = 10;
	float y = 10;
	CVector2f* min = new CVector2f(x, y);
	CVector2f* max = new CVector2f(x + m_pSprite->getImageWidth(), y + m_pSprite->getImageHeight());
	m_pAABB = new CAABB_f(min, max);

	m_sAtributes.defaultVelosity_pos = 5;
	m_sAtributes.defaultVelosity_neg = -5;
	m_sAtributes.nullVelosity();
	m_sAtributes.mass = 10;

	isUpPressed		= false;
	isDownPressed	= false;
	isLeftPressed	= false;
	isRightPressed	= false;

	m_sAnimationSequence.x = 1;
	m_sAnimationSequence.y = 1;
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
			m_sAtributes.velosity_y = m_sAtributes.defaultVelosity_neg;
			return true;
			break;

		case SDLK_DOWN:
			isDownPressed = true;
			m_sAtributes.velosity_y = m_sAtributes.defaultVelosity_pos;
			return true;
			break;

		case SDLK_LEFT:
			isLeftPressed = true;
			m_sAtributes.velosity_x = m_sAtributes.defaultVelosity_neg;
			return true;
			break;

		case SDLK_RIGHT:
			isRightPressed = true;
			m_sAtributes.velosity_x = m_sAtributes.defaultVelosity_pos;
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
			m_sAtributes.nullVelosity_y();
			return true;
			break;

		case SDLK_DOWN:
			isDownPressed = false;
			m_sAtributes.nullVelosity_y();
			return true;
			break;

		case SDLK_LEFT:
			isLeftPressed = false;
			m_sAtributes.nullVelosity_x();
			return true;
			break;

		case SDLK_RIGHT:
			isRightPressed = false;
			m_sAtributes.nullVelosity_x();
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
		if (m_sAnimationSequence.y - 1 < 1)
		{
			m_sAnimationSequence.y = 1;
		}
		else
		{
			--m_sAnimationSequence.y;
		}

		if (pMin->y + m_sAtributes.velosity_y < 0)
		{
			m_pAABB->setMinY(0);
		}
		else
		{
			m_pAABB->setMinY(pMin->y + m_sAtributes.velosity_y);
		}
	}
	if (isDownPressed)
	{
		if (m_sAnimationSequence.y + 1 > m_pSprite->getNumRows())
		{
			m_sAnimationSequence.y = m_pSprite->getNumRows();
		}
		else
		{
			++m_sAnimationSequence.y;
		}

		if (pMin->y + m_sAtributes.velosity_y + m_pSprite->getImageHeight() > m_pWindow->getHeight())
		{
			m_pAABB->setMinY(m_pWindow->getHeight() - m_pSprite->getImageHeight());
		}
		else
		{
			m_pAABB->setMinY(pMin->y + m_sAtributes.velosity_y);
		}
	}
	if (isLeftPressed)
	{
		if (m_sAnimationSequence.x - 1 < 1)
		{
			m_sAnimationSequence.x = 1;
		} 
		else
		{
			--m_sAnimationSequence.x;
		}

		if (pMin->x + m_sAtributes.velosity_x < 0)
		{
			m_pAABB->setMinX(0);
		}
		else
		{
			m_pAABB->setMinX(pMin->x + m_sAtributes.velosity_x);
		}
	}
	if (isRightPressed)
	{
		if (m_sAnimationSequence.x + 1 > m_pSprite->getNumColumns())
		{
			m_sAnimationSequence.x = m_pSprite->getNumColumns();
		} 
		else
		{
			++m_sAnimationSequence.x;
		}

		if (pMin->x + m_sAtributes.velosity_x + m_pSprite->getImageWidth() > m_pWindow->getWidth())
		{
			m_pAABB->setMinX(m_pWindow->getWidth() - m_pSprite->getImageWidth());
		}
		else
		{
			m_pAABB->setMinX(pMin->x + m_sAtributes.velosity_x);
		}
	}
}


void CUserControlled_Bot::render()
{
	CVector2f* pMin = m_pAABB->getMin();
	m_pSprite->render(pMin->x, pMin->y, 
		m_pSprite->getImageWidth(), m_pSprite->getImageHeight(), 
		m_sAnimationSequence.y, m_sAnimationSequence.x);
}