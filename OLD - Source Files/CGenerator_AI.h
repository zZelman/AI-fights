#ifndef CGENERATOR_AI_H
#define CGENERATOR_AI_H

#include "stdafx.h"

#include "CGenerator.h"
#include "CAI.h"

class CGenerator_AI : public CGenerator
{
public:
	CGenerator_AI(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS,
	              std::vector<CRoom*>* collisionRoom);
	~CGenerator_AI();

	// returns the container for the ai
	const std::vector<CAI*>* getAI();

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
	// container for all ai in the game
	std::vector<CAI*> m_aiVector;

	// container pointer for all room collisions
	std::vector<CRoom*>* m_pRoom_collision;

	// movement control for ai, ARROW KEYS
	bool isUpPressed, isDownPressed;
	bool isLeftPressed, isRightPressed;

	// sets/unsets the bools that control how the ai move
	void checkMoveKeys(SDL_Event& e);
};


#endif // !CGENERATOR_AI_H