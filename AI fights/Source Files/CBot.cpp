#include "stdafx.h"
#include "CBot.h"

CBot::CBot(CWindow* window, std::string fileName, 
		   int imageWidth, int imageHeight,
		   int numImages_rows, int numImages_columns)
{
	// position is not initalized here because each bot has different values

	m_spriteName = fileName;
	m_pWindow = window;

	m_sAtributes.gravityTimer.start();

	m_pSprite = new CSprite(m_pWindow, fileName, 
		imageWidth, imageHeight, 
		numImages_rows, numImages_columns);
	m_pSprite->load();

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


void CBot::update() {}


void CBot::render() {}


void CBot::init() {}