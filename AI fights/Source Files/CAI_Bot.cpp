#include "stdafx.h"
#include "CAI_Bot.h"

CAI_Bot::CAI_Bot(std::string spriteName, CWindow* pWindow)
	: CBot(spriteName, pWindow)
{
	float x = pWindow->getWindowWidth() / 2;
	float y = pWindow->getWindowHeight() / 2;
	CVector2f* min = new CVector2f(x, y);
	CVector2f* max = new CVector2f(x + m_pSprite->getWidth(), y + m_pSprite->getHeight());
	m_pAABB = new CAABB_f(min, max);

	m_sAtributes.defaultVelosity_pos = 5;
	m_sAtributes.defaultVelosity_neg = -5;
	m_sAtributes.velosity_x = 10;
	m_sAtributes.velosity_y = -5;
	m_sAtributes.mass = 10;

	isMovingRight = true;
}

CAI_Bot::~CAI_Bot()
{
	CBot::~CBot();
}


void CAI_Bot::update()
{
	// General logic:
	// if (bot's next step is outside of screen)
	//		step to edge of screen;
	// else
	//		step normally

	//CVector2f* pMin = m_pAABB->getMin();

	//if (isMovingRight)
	//{
	//	m_sAtributes.velosity_x = abs(m_sAtributes.velosity_x); // positive velocity means moving right

	//	if (pMin->x + m_sAtributes.velosity_x + m_pSprite->getWidth() > m_pWindow->getWindowWidth())
	//	{
	//		m_pAABB->setMinX(m_pWindow->getWindowWidth() - m_pSprite->getWidth());
	//		isMovingRight = false;
	//	}
	//	else
	//	{
	//		m_pAABB->setMinX(pMin->x + m_sAtributes.velosity_x);
	//	}
	//}
	//else
	//{
	//	m_sAtributes.velosity_x = -abs(m_sAtributes.velosity_x); // negative velocity means moving left

	//	if (pMin->x + m_sAtributes.velosity_x < 0)
	//	{
	//		m_pAABB->setMinX(0);
	//		isMovingRight = true;
	//	}
	//	else
	//	{
	//		m_pAABB->setMinX(pMin->x + m_sAtributes.velosity_x);
	//	}
	//}

	float x = m_pAABB->getMin()->x + m_sAtributes.velosity_x;
	float y = m_pAABB->getMin()->y + m_sAtributes.velosity_y;

	m_pAABB->setMin(new CVector2f(x, y));
}