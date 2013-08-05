#ifndef CROOMGENERATOR_H
#define CROOMGENERATOR_H

#include "stdafx.h"

#include "CRoom.h"
#include "CMap.h"
#include "CPhysics.h"
#include "CTimer.h"

class CRoomGenerator
{
public:
	CRoomGenerator(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS);
	~CRoomGenerator();

	// * checks if 'e' is a mouse event and then checks to see if it is able to spawn (< spawnTime)
	// * returns true if a room was spawned, false if not
	bool generate(SDL_Event& e);

	// applies physics to all of the rooms & calls their updates
	void update();

	// renders all of the rooms by calling their render function
	void render();

private:
	// window everything will be drawn to
	CWindow* m_pWindow;

	// the tile map that the rooms will stop when they detect a collision
	CMap* m_pCollisionMap;

	// physics engine responsible for the rooms falling with gravity
	CPhysics* m_pPhysics;

	// container that holds all of the room pointers
	std::vector<CRoom*> m_roomVector;

	// physics that allows the rooms to fall
	CTimer* m_pSpawnTimer;

	// times between clicks has to be > than this in order to spawn a room
	Uint32 m_spawnTime_MS;

	// if (currentTime - prevTimeSpawn > spawnTime) then spawn room
	//		else, do nothing
	Uint32 m_prevTimeSpawn;

};


#endif // !CROOMGENERATOR_H
