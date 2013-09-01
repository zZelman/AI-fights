#ifndef CGENERATOR_ROOM_H
#define CGENERATOR_ROOM_H

#include "stdafx.h"

#include "CGenerator.h"

#include "CRoom.h"
#include "CRoom_1x1.h"
#include "CRoom_2x2.h"
#include "CRoom_2x1.h"
#include "CRoom_1x2.h"
#include "CMap.h"
#include "CPhysics.h"
#include "CTimer.h"

class CGenerator_room : public CGenerator
{
public:
	CGenerator_room(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS);
	~CGenerator_room();

	// returns the container for the rooms
	std::vector<CRoom*>* getRooms();

	// removes all rooms from roomVector
	void clear();

	// * checks if 'e' is a mouse event and then checks to see if it is able to spawn (< spawnTime)
	// * returns true if a room was spawned, false if not
	bool generate(SDL_Event& e);

	// applies physics to all of the rooms & calls their updates
	void update();

	// renders all of the rooms by calling their render function
	void render();

private:
	// if true, each respective room is generated
	bool is1pressed; // 1x1
	bool is2pressed; // 1x2
	bool is3pressed; // 2x1
	bool is4pressed; // 2x2

	// container that holds all of the room pointers
	std::vector<CRoom*> m_roomVector;

	// sets/unsets the bools that control what room is spawns
	void checkSpawnKeys(SDL_Event& e);

	// * create a room and add it to the room vector
	// * separated from the generate method for readability
	bool spawn_1x1(SDL_Event& e, SCoords2<int>* spawnCoords);
	bool spawn_1x2(SDL_Event& e, SCoords2<int>* spawnCoords);
	bool spawn_2x1(SDL_Event& e, SCoords2<int>* spawnCoords);
	bool spawn_2x2(SDL_Event& e, SCoords2<int>* spawnCoords);

	// checks the coords against both the map tiles and rooms present
	bool preventCollisions(SCoords2<int>* topLeft, SCoords2<int>* topRight,
	                       SCoords2<int>* bottomLeft, SCoords2<int>* bottomRight);

};


#endif // !CROOMGENERATOR_H
