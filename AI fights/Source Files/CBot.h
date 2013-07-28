#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CSprite.h"


// serves as the base class for all movable 'bot's in the game
class CBot
{
public:
	CBot(std::string spriteName, CWindow* pWindow);
	virtual ~CBot();

	CAABB_f* getAABB();

	virtual void update(); // serves as a dummy function
	virtual void render();

protected:
	CWindow* m_pWindow; // window everything happens in
	CSprite* m_pSprite; // holds the entire sprite sheet for this Bot
	std::string m_spriteName; // file name (not path) of the sprite used for this bot

	CAABB_f* m_pAABB; // axis aligned bonding box
	int m_stepSize; // size of each increment

	// loads everything (separate from constructor b/c constructor sets data values)
	virtual void init();
};