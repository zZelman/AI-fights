#include "stdafx.h"

#include "CRoomGenerator.h"

CRoomGenerator::CRoomGenerator(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS)
{
	m_pWindow			= window;
	m_pCollisionMap		= collisionMap;
	m_pPhysics			= physics;
	m_spawnTime_MS		= spawnTime_MS;

	m_pSpawnTimer		= new CTimer();
	m_pSpawnTimer->start();
	m_prevTimeSpawn = 0;
}


CRoomGenerator::~CRoomGenerator()
{
	delete m_pSpawnTimer;

	m_roomVector.erase(m_roomVector.begin(), m_roomVector.end());
}


bool CRoomGenerator::generate(SDL_Event& e)
{
	if (e.button.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT &&
		(m_pSpawnTimer->getTime() - m_prevTimeSpawn) > m_spawnTime_MS)
	{
		int x = e.button.x;
		int y = e.button.y;

		// this is to make the room appear with the grid
		m_pCollisionMap->convertScreenToMap(&x, &y);
		x = x * m_pCollisionMap->getWidth_tile();
		y = e.button.y;

		SCoords2<int> spawnCoords;
		spawnCoords.setCoords(x, y);
		m_roomVector.push_back(new CRoom(m_pWindow, m_pCollisionMap, &m_roomVector,
			spawnCoords, "Resource Files/Rooms/room.png",
			32, 32, 1, 1));

		m_prevTimeSpawn = m_pSpawnTimer->getTime();
		return true;
	}

	return false;
}


void CRoomGenerator::update()
{
	for (auto itr = m_roomVector.begin(); itr != m_roomVector.end(); ++itr)
	{
		m_pPhysics->applyGravity(*itr);
		(*itr)->update();
	}
}


void CRoomGenerator::render()
{
	for (auto itr = m_roomVector.begin(); itr != m_roomVector.end(); ++itr)
	{
		(*itr)->render();
	}
}