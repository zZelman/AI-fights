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


bool CPhysics::collisionDetection(CBot* bot1, CBot* bot2)
{
	return false;
}


void CPhysics::collisionDetection(CBot* bot, CWindow* window)
{
	CAABB_f* pAABB = bot->getAABB();
	CVector2<float>* pMin = bot->getAABB()->getMin();
	CVector2<float>* pMax = bot->getAABB()->getMax();

	int winWidth = window->getWidth();
	int winHeight = window->getHeight();

	// General logic:
	// if (bot's next step is outside of screen)
	//		step to edge of screen;
	//		if (vertical movement)
	//			start timer to record time since last 'ground' bounce
	//		else
	//			velocity = -velocity
	// else
	//		do not change anything

	// as it stands now, this function is intended to be for
	//		passive collisions (something not user controlled)

	if (bot->m_sAtributes.velosity_x > 0) // moving right
	{
		if (pMin->x + bot->m_sAtributes.velosity_x + pAABB->getWidth() > winWidth)
		{
			pAABB->setMinX(winWidth - pAABB->getWidth());
			bot->m_sAtributes.velosity_x = -bot->m_sAtributes.velosity_x;
		}
	}
	else if (bot->m_sAtributes.velosity_x < 0) // moving left
	{
		if (pMin->x  + bot->m_sAtributes.velosity_x < 0)
		{
			pAABB->setMinX(0);
			bot->m_sAtributes.velosity_x = -bot->m_sAtributes.velosity_x;
		}
	}

	if (bot->m_sAtributes.velosity_y < 0) // moving up
	{
		if (pMin->y + bot->m_sAtributes.velosity_y < 0)
		{
			pAABB->setMinY(0);

			//bot->m_sAtributes.gravityTimer.start();
		}
	}
	else if (bot->m_sAtributes.velosity_y > 0) // moving down
	{
		if (pMin->y + bot->m_sAtributes.velosity_y + pAABB->getHeight() > winHeight)
		{
			pAABB->setMinY(winHeight - pAABB->getHeight());

			bot->m_sAtributes.gravityTimer.start();
		}
	}
}


float CPhysics::penetrationDepth(CBot* bot1, CBot* bot2)
{
	return 0.0f;
}


CVector2<float>* CPhysics::collisionNormal(CBot* bot1, CBot* bot2)
{
	return nullptr;
}


SManifold* CPhysics::generateManafold(CBot* bot1, CBot* bot2)
{
	return nullptr;
}
