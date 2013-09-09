#include "stdafx.h"
#include "CGenerator.h"


CGenerator::CGenerator(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS)
{
	m_pWindow			= window;
	m_pCollisionMap		= collisionMap;
	m_pPhysics			= physics;
	m_spawnTime_MS		= spawnTime_MS;

	m_pSpawnTimer		= new CTimer();
	m_pSpawnTimer->start();
	m_prevTimeSpawn = 0;
}


CGenerator::~CGenerator()
{
	delete m_pSpawnTimer;
}


void CGenerator::clear() {} // virtual


bool CGenerator::generate(SDL_Event& e)
{
	// virtual
	return false;
}


void CGenerator::update() {} // virtual


void CGenerator::render() {} // virtual