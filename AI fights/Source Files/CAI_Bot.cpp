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

	m_stepSize = 5;

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

	CVector2f* pMin = m_pAABB->getMin();

	if (isMovingRight)
	{
		if (pMin->x + m_stepSize + m_pSprite->getWidth() > m_pWindow->getWindowWidth())
		{
			m_pAABB->setMinX(m_pWindow->getWindowWidth() - m_pSprite->getWidth());
			isMovingRight = false;
		}
		else
		{
			m_pAABB->setMinX(pMin->x + m_stepSize);
		}
	}
	else
	{
		if (pMin->x - m_stepSize < 0)
		{
			m_pAABB->setMinX(0);
			isMovingRight = true;
		}
		else
		{
			m_pAABB->setMinX(pMin->x - m_stepSize);
		}
	}
}