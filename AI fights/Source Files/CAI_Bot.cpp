#include "stdafx.h"
#include "CAI_Bot.h"

CAI_Bot::CAI_Bot(std::string spriteName, CWindow* pWindow)
	: CBot(spriteName, pWindow)
{
	float x = pWindow->getWidth() / 2;
	float y = pWindow->getHeight() / 2;
	CVector2f* min = new CVector2f(x, y);
	CVector2f* max = new CVector2f(x + m_pSprite->getWidth(), y + m_pSprite->getHeight());
	m_pAABB = new CAABB_f(min, max);

	m_sAtributes.defaultVelosity_pos = 5;
	m_sAtributes.defaultVelosity_neg = -5;
	m_sAtributes.velosity_x = 5;
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
	float x = m_pAABB->getMin()->x + m_sAtributes.velosity_x;
	float y = m_pAABB->getMin()->y + m_sAtributes.velosity_y;

	m_pAABB->setMinX(x);
	m_pAABB->setMinY(y);
}