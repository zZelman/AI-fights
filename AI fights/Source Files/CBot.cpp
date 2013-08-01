#include "stdafx.h"
#include "CBot.h"

CBot::CBot(CWindow* window, CMap* collisionMap, std::string fileName,
           int imageWidth, int imageHeight,
           int numImages_rows, int numImages_columns)
{
	// position is not initalized here because each bot has different values

	m_spriteName = fileName;
	m_pWindow = window;
	m_pCollisionMap = collisionMap;

	m_sAtributes.gravityTimer.start();

	m_pSprite = new CSprite(m_pWindow, fileName,
	                        imageWidth, imageHeight,
	                        numImages_rows, numImages_columns);
	m_pSprite->load();

}


CBot::~CBot()
{
	// don't delete m_pWindow when the bot is deleted

	delete m_pSprite;
	m_pSprite = NULL;

	delete m_pAABB;
	m_pAABB = NULL;
}


CAABB_f* CBot::getAABB()
{
	return m_pAABB;
}


void CBot::update() {}


void CBot::render() {}


bool CBot::mapCollision(CMap* map)
{
	return map->collision_screenToMap(m_pAABB);
}


bool CBot::correctMapCollision_up()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;


	CVector2f min(minPosX, nextStepY_min);
	CVector2f max(maxPosX, nextStepY_max);
	CAABB_f aabb(&min, &max);

	CAABB_f tileAABB;

	// just set everything within the tileAABB with arbitrary NEW values
	// they will be changed later, just need to have them, but not have tileAABB equal to something
	//		else (no pointers)
	tileAABB.setEverything(minPosX, minPosY, maxPosX, maxPosY);

	if (m_pCollisionMap->collision_screenToMap(&aabb, &tileAABB) == true)
	{
		m_pAABB->setMin(minPosX, tileAABB.getMax()->y+0.5);
		return true;
	}
	return false;
}


bool CBot::correctMapCollision_down()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;


	CVector2f min(minPosX, nextStepY_min);
	CVector2f max(maxPosX, nextStepY_max);
	CAABB_f aabb(&min, &max);

	CAABB_f tileAABB;

	// just set everything within the tileAABB with arbitrary NEW values
	// they will be changed later, just need to have them, but not have tileAABB equal to something
	//		else (no pointers)
	tileAABB.setEverything(minPosX, minPosY, maxPosX, maxPosY);

	if (m_pCollisionMap->collision_screenToMap(&aabb, &tileAABB) == true)
	{
		m_pAABB->setMax(maxPosX, tileAABB.getMin()->y-0.5);
		return true;
	}
	return false;
}


bool CBot::correctMapCollision_left()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;


	CVector2f min(nextStepX_min, minPosY);
	CVector2f max(nextStepX_max, maxPosY);
	CAABB_f aabb(&min, &max);

	CAABB_f tileAABB;

	// just set everything within the tileAABB with arbitrary NEW values
	// they will be changed later, just need to have them, but not have tileAABB equal to something
	//		else (no pointers)
	tileAABB.setEverything(minPosX, minPosY, maxPosX, maxPosY);

	if (m_pCollisionMap->collision_screenToMap(&aabb, &tileAABB) == true)
	{
		m_pAABB->setMin(tileAABB.getMax()->x+0.5, minPosY);
		return true;
	}
	return false;
}


bool CBot::correctMapCollision_right()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;


	CVector2f min(nextStepX_min, minPosY);
	CVector2f max(nextStepX_max, maxPosY);
	CAABB_f aabb(&min, &max);

	CAABB_f tileAABB;

	// just set everything within the tileAABB with arbitrary NEW values
	// they will be changed later, just need to have them, but not have tileAABB equal to something
	//		else (no pointers)
	tileAABB.setEverything(minPosX, minPosY, maxPosX, maxPosY);

	if (m_pCollisionMap->collision_screenToMap(&aabb, &tileAABB) == true)
	{
		m_pAABB->setMax(tileAABB.getMin()->x-0.5, maxPosY);
		return true;
	}
	return false;
}


void CBot::init() {}


bool CBot::correctScreenEdgeCollision_up()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;


	CVector2f min(minPosX, nextStepY_min);
	CVector2f max(maxPosX, nextStepY_max);
	CAABB_f aabb(&min, &max);

	if (m_pWindow->isOutsideWindow(&aabb))
	{
		m_pAABB->setMinY(0);
		return true;
	}
	return false;
}


bool CBot::correctScreenEdgeCollision_down()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;


	CVector2f min(minPosX, nextStepY_min);
	CVector2f max(maxPosX, nextStepY_max);
	CAABB_f aabb(&min, &max);

	if (m_pWindow->isOutsideWindow(&aabb))
	{
		m_pAABB->setMinY(m_pWindow->getHeight() - m_pSprite->getImageHeight());
		return true;
	}
	else
	{
		m_pAABB->setMinY(nextStepY_min);
		return false;
	}
}


bool CBot::correctScreenEdgeCollision_left()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;

	CVector2f min(nextStepX_min, minPosY);
	CVector2f max(nextStepX_max, maxPosY);
	CAABB_f aabb(&min, &max);

	if (m_pWindow->isOutsideWindow(&aabb))
	{
		m_pAABB->setMinX(0);
		return true;
	}
	else
	{
		m_pAABB->setMinX(nextStepX_min);
		return false;
	}
}


bool CBot::correctScreenEdgeCollision_right()
{
	CVector2f* pMin = m_pAABB->getMin();
	float minPosX			= pMin->x;
	float minPosY			= pMin->y;
	float nextStepX_min		= minPosX + m_sAtributes.velosity_x;
	float nextStepY_min		= minPosY + m_sAtributes.velosity_y;

	CVector2f* pMax = m_pAABB->getMax();
	float maxPosX			= pMax->x;
	float maxPosY			= pMax->y;
	float nextStepX_max		= maxPosX + m_sAtributes.velosity_x;
	float nextStepY_max		= maxPosY + m_sAtributes.velosity_y;

	CVector2f min(nextStepX_min, minPosY);
	CVector2f max(nextStepX_max, maxPosY);
	CAABB_f aabb(&min, &max);

	if (m_pWindow->isOutsideWindow(&aabb))
	{
		m_pAABB->setMinX(m_pWindow->getWidth() - m_pSprite->getImageWidth());
		return true;
	}
	else
	{
		m_pAABB->setMinX(nextStepX_min);
		return false;
	}
}