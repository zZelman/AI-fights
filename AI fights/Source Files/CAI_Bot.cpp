#include "stdafx.h"
#include "CAI_Bot.h"

CAI_Bot::CAI_Bot(CWindow* window, CMap* map, std::string fileName,
                 int imageWidth, int imageHeight,
                 int numImages_rows, int numImages_columns)
	: CBot(window, map, fileName,
	       imageWidth, imageHeight,
	       numImages_rows, numImages_columns)
{
	float x = window->getWidth() / 2;
	float y = window->getHeight() / 2;
	CVector2f* min = new CVector2f(x, y);
	CVector2f* max = new CVector2f(x + m_pSprite->getImageWidth(), y + m_pSprite->getImageHeight());
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