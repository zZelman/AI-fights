#pragma once

#include "stdafx.h"
#include "CBot.h"
#include "CWindow.h"

// * This class is the 'physics engine' for the game
// * It is intended to be used at the same level as the data structure that houses
//		the movable pieces / map. As such, all it does is provide calculations on OTHER
//		data, and does not hold anything meaningful for a long period of time
class CPhysics
{
public:
	CPhysics();
	~CPhysics();

	// * applies gravity to bot
	// * does not move bot, only changes the velocities within the bot to reflect gravity
	void applyGravity(CBot* bot);

	// * returns true if yes, false if no
	bool collisionDetection(CBot* bot1, CBot* bot2);

	// * checks the bot's collision against the window edges
	// * calculates against the bot's NEXT move
	void collisionDetection(CBot* bot, CWindow* window);

	// * calculates how much bot1 has collided with bot2
	// * NOTE: does not check collision detection, it is assumed as true
	float penetrationDepth(CBot* bot1, CBot* bot2);

	// * calculates the normal produced from the collision between bot1 and bot2
	// * NOTE: does not check collision detection, it is assumed as true
	CVector2f* collisionNormal(CBot* bot1, CBot* bot2);

	// * Generates a manifold
	// * a manifold is a small object that contains information about a collision between two objects
	SManifold* generateManafold(CBot* bot1, CBot* bot2);

private:
	// * 'a' in the parabolic formula ax^2 + bx + c
	// * should always be positive because the positive y axis extends downward
	//		(top left to bottom left)
	float m_gravityA;

	// * 'b' in the parabolic formula ax^2 + bx + c
	// * should always be negative because the positive y axis extends downward
	//		(top left to bottom left)
	float m_gravityB;
};