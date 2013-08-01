#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CSprite.h"
#include "Math2D.h"
#include "CTimer.h"
#include "CMap.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

// these declarations/definitions are here because CBot.h cant find them in Math2D.h for whatever reason

class CAABB_f;
struct SCoords2i;

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


struct SCoords2i
{
	int x, y;

	SCoords2i() {}
	SCoords2i(int _x, int _y)
	{
		x = _x;
		y = _y;
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

	// * holds the sprite sheet coords for animation/successive images to be played by the bot
	// * SPRITE SHEET COORDS (lengths -> top left is 1,1)
	SCoords2i m_sAnimationSequence;

	CBot(CWindow* window, CMap* collisionMap, std::string fileName, 
		int imageWidth, int imageHeight,
		int numImages_rows = 1, int numImages_columns = 1);
	virtual ~CBot();

	CAABB_f* getAABB();

	virtual void update(); // serves as a dummy function
	virtual void render();

	// * checks collision against the given map
	// * ATM it only checks the top left as for collisions -> possible [BUG]
	virtual bool mapCollision(CMap* map);

protected:
	CWindow* m_pWindow; // window everything happens in
	CMap* m_pCollisionMap; // the map that will serve as collision detection/resolution
	CSprite* m_pSprite; // holds the entire sprite sheet for this Bot
	std::string m_spriteName; // file name (not path) of the sprite used for this bot

	CAABB_f* m_pAABB; // axis aligned bonding box

	// if the NEXT AABB (based off of the respective x-y velocities) of this bot is within a MAP tile,
	//		move to the edge of the MAP tile, else do step normally
	// return true if the step was altered
	bool correctMapCollision_up();
	bool correctMapCollision_down();
	bool correctMapCollision_left();
	bool correctMapCollision_right();

	// loads everything (separate from constructor b/c constructor sets data values)
	virtual void init();

	// if the NEXT AABB (based off of the respective x-y velocities) of this bot is off of the SCREEN,
	//		move to the edge of the SCREEN, else do step normally
	// return true if the step was altered
	bool correctScreenEdgeCollision_up();
	bool correctScreenEdgeCollision_down();
	bool correctScreenEdgeCollision_left();
	bool correctScreenEdgeCollision_right();
};