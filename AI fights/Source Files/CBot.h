#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CSprite.h"
#include "Math2D.h"
#include "CTimer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

// these declarations/definitions are here because CBot.h cant find them in Math2D.h for whatever reason

class CAABB_f;

// Holds physics information about the object
struct SAtributes
{
	float defaultVelosity_pos; // DEFAULT movement size each update
	float defaultVelosity_neg; // DEFAULT movement size each update

	float velosity_x; // change in the x axis each update
	float velosity_y; // change in the y axis each update

	float mass;

	CTimer gravityTimer; // how long has gravity been affecting this object since last collision

	void nullVelosity()
	{
		velosity_x = 0;
		velosity_y = 0;
	}

	void nullVelosity_x()
	{
		velosity_x = 0;
	}

	void nullVelosity_y()
	{
		velosity_y = 0;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////

// serves as the base class for all movable 'bot's in the game
class CBot
{
public:
	// * holds all of the physics data for this object
	// * public because there are no bounds atm for data, so why use getters/setters?
	SAtributes m_sAtributes;

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

	// loads everything (separate from constructor b/c constructor sets data values)
	virtual void init();
};