#include "stdafx.h"
#include "CUserControlled_Bot.h"

CUserControlled_Bot::CUserControlled_Bot(CWindow* window, CMap* collisionMap, std::string fileName,
        int imageWidth, int imageHeight,
        int numImages_rows, int numImages_columns)
	: CBot(window, collisionMap, fileName,
	       imageWidth, imageHeight,
	       numImages_rows, numImages_columns)
{
	float x = 10;
	float y = 10;
	CVector2<float>* min = new CVector2<float>(x, y);
	CVector2<float>* max = new CVector2<float>(x + m_pSprite->getImageWidth(), y + m_pSprite->getImageHeight());
	m_pAABB = new CAABB_f(min, max);

	m_sAtributes.defaultVelosity_pos = 3;
	m_sAtributes.defaultVelosity_neg = -3;
	m_sAtributes.nullVelosity();
	m_sAtributes.mass = 10;

	isUpPressed		= false;
	isDownPressed	= false;
	isLeftPressed	= false;
	isRightPressed	= false;

	m_sAnimationSequence = SCoords2<int>(1, 1);
	m_animationChangeMS = SecToMS(0.09);
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
	CBot::update();

	// General logic:
	// if (bot's next step is outside of screen)
	//		step to edge of screen;
	// else
	//		step normally

	CVector2<float>* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;
		
	CVector2<float>* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;


	if (isUpPressed && !isDownPressed)
	{
		if (!correctScreenEdgeCollision_up())
		{
			if (!correctMapCollision_up())
			{
				m_pAABB->setMinY(nextStepY_min);
			}
		}
	}

	if (isDownPressed && !isUpPressed)
	{
		if (!correctScreenEdgeCollision_down())
		{
			if (!correctMapCollision_down())
			{
				m_pAABB->setMinY(nextStepY_min);
			}
		}
	}

	if (isLeftPressed && !isRightPressed)
	{
		if (m_pAnimationTimer->getTime() > m_animationChangeMS)
		{
			m_sAnimationSequence.y = 1;
			if (m_sAnimationSequence.x + 1 > m_pSprite->getNumColumns())
			{
				m_sAnimationSequence.x = 1;
			}
			else
			{
				++m_sAnimationSequence.x;
			}

			m_pAnimationTimer->start();
		}

		//if (!correctScreenEdgeCollision_left())
		//{
		//	if (!correctMapCollision_left())
		//	{
				m_pAABB->setMinX(nextStepX_min);
		//	}
		//}
	}

	if (isRightPressed && !isLeftPressed)
	{
		if (m_pAnimationTimer->getTime() > m_animationChangeMS)
		{
			m_sAnimationSequence.y = 2;
			if (m_sAnimationSequence.x + 1 > m_pSprite->getNumColumns())
			{
				m_sAnimationSequence.x = 1;
			}
			else
			{
				++m_sAnimationSequence.x;
			}

			m_pAnimationTimer->start();
		}

		//if (!correctScreenEdgeCollision_right())
		//{
		//	if (!correctMapCollision_right())
		//	{
				m_pAABB->setMinX(nextStepX_min);
		//	}
		//}
	}
}


void CUserControlled_Bot::render()
{
	CVector2<float>* pMin = m_pAABB->getMin();
	m_pSprite->render(pMin->x, pMin->y,
	                  m_pSprite->getImageWidth(), m_pSprite->getImageHeight(),
	                  m_sAnimationSequence.y, m_sAnimationSequence.x);
}