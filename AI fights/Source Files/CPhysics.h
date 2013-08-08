#ifndef CPHYSICS_H
#define CPHYSICS_H


#include "stdafx.h"
#include "CWindow.h"
#include "CRoom.h"

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
	void applyGravity(CRoom* room);

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


#endif // !CPHYSICS_H