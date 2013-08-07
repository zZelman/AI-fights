#ifndef CGENERATOR_H
#define CGENERATOR_H


#include "stdafx.h"
#include "CWindow.h"
#include "CMap.h"
#include "CPhysics.h"

// * Acts as the base class for all generator classes
// * All methods are dummy methods and must be overridden
class CGenerator
{
public:
	CGenerator(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS);
	virtual ~CGenerator();

	// removes all rooms from roomVector
	virtual void clear();

	// * checks if 'e' is a mouse event and then checks to see if it is able to spawn (< spawnTime)
	// * returns true if a room was spawned, false if not
	virtual bool generate(SDL_Event& e);

	// applies physics to all of the rooms & calls their updates
	virtual void update();

	// renders all of the rooms by calling their render function
	virtual void render();

protected:
	// window everything will be drawn to
	CWindow* m_pWindow;

	// the tile map that the rooms will stop when they detect a collision
	CMap* m_pCollisionMap;

	// physics engine responsible for the rooms falling with gravity
	CPhysics* m_pPhysics;

	// timer to keep track of when a thing can spawn
	CTimer* m_pSpawnTimer;

	// times between clicks has to be > than this in order to spawn a room
	Uint32 m_spawnTime_MS;

	// if (currentTime - prevTimeSpawn > spawnTime) then spawn room
	//		else, do nothing
	Uint32 m_prevTimeSpawn;
};



#endif // !CGENERATOR_H
