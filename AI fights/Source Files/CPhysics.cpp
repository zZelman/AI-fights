#include "stdafx.h"
#include "CPhysics.h"

CPhysics::CPhysics()
{
	float bounceTime = 2; // seconds

	m_gravityA = 10;
	m_gravityB = -(m_gravityA * bounceTime);
}


CPhysics::~CPhysics() {}


void CPhysics::applyGravity(CRoom* room)
{
	Uint32 time = room->m_sAtributes.gravityTimer.getTime();

	float timef = MStoSec(time);

	// * use the first derivative of the parabolic formula to account for changes in velocity
	// * uncomment m_gravityB to have the object go up then down, instead of just start its decent asap
	room->m_sAtributes.velosity_y = ((2 * m_gravityA) * timef)/* + m_gravityB*/;
}
