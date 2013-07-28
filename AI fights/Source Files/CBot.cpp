#include "stdafx.h"
#include "CBot.h"

CBot::CBot(std::string spriteName, CWindow* pWindow)
{
	// position is not initalized here because each bot has different values

	m_spriteName = spriteName;
	m_pWindow = pWindow;

	m_sAtributes.gravityTimer.start();

	init();
}


CBot::~CBot()
{
	// don't delete m_pWindow when the bot is deleted

	delete m_pSprite;
	m_pSprite = NULL;

	delete m_pAABB;
	m_pAABB = NULL;
}


CAABB_f* CBot::getAABB()
{
	return m_pAABB;
}


void CBot::init()
{
	m_pSprite = new CSprite(m_spriteName, m_pWindow);
	m_pSprite->load();
}


void CBot::update() {}


void CBot::render()
{
	CVector2f* pMin = m_pAABB->getMin();
	m_pSprite->render(pMin->x, pMin->y);
}