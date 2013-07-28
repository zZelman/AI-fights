#include "stdafx.h"
#include "CPhysics.h"

CPhysics::CPhysics() {}
CPhysics::~CPhysics() {}


bool CPhysics::collisionDetection(CBot* bot1, CBot* bot2)
{
	return false;
}


void CPhysics::collisionDetection(CBot* bot, CWindow* window)
{
	// General logic:
	// if (bot's next step is outside of screen)
	//		step to edge of screen;
	//		velosity = -velosity
	// else
	//		do not change anything

	// as it stands now, this function is intended to be for 
	//		passive collisions (something not user controlled)

	CAABB_f* pAABB = bot->getAABB();
	CVector2f* pMin = bot->getAABB()->getMin();

	int winWidth = window->getWindowWidth();
	int winHeight = window->getWindowHeight();

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
			bot->m_sAtributes.velosity_y = -bot->m_sAtributes.velosity_y;
		}
	}
	else if (bot->m_sAtributes.velosity_y > 0) // moving down
	{
		if (pMin->y + bot->m_sAtributes.velosity_y + pAABB->getHeight() > winHeight)
		{
			pAABB->setMinY(winHeight - pAABB->getHeight());
			bot->m_sAtributes.velosity_y = -bot->m_sAtributes.velosity_y;
		} 
	}
}


float CPhysics::penetrationDepth(CBot* bot1, CBot* bot2)
{
	return 0.0f;
}


CVector2f* CPhysics::collisionNormal(CBot* bot1, CBot* bot2)
{
	return nullptr;
}


SManifold* CPhysics::generateManafold(CBot* bot1, CBot* bot2)
{
	return nullptr;
}
