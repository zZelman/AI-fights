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

	is1pressed = false;
	is2pressed = false;
	is3pressed = false;
	is4pressed = false;
}


CRoomGenerator::~CRoomGenerator()
{
	delete m_pSpawnTimer;

	clear();
}


void CRoomGenerator::clear()
{
	m_roomVector.erase(m_roomVector.begin(), m_roomVector.end());
	m_roomVector;
}


bool CRoomGenerator::generate(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_1:
			is1pressed = true;
			break;
		case SDLK_2:
			is2pressed = true;
			break;
		case SDLK_3:
			is3pressed = true;
			break;
		case SDLK_4:
			is4pressed = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_1:
			is1pressed = false;
			break;
		case SDLK_2:
			is2pressed = false;
			break;
		case SDLK_3:
			is3pressed = false;
			break;
		case SDLK_4:
			is4pressed = false;
			break;
		}
	}

	if (e.button.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT &&
	        (m_pSpawnTimer->getTime() - m_prevTimeSpawn) > m_spawnTime_MS)
	{
		int x = e.button.x;
		int y = e.button.y;

		SCoords2<int> spawnCoords;
		spawnCoords.setCoords(x, y);

		// [BUG]: how to stop a 2xn from spawning in a 1xm spot?

		// don't let a room be spawned in a tile
		if (m_pCollisionMap->collision_screenToMap(&spawnCoords) == true)
		{
			return false;
		}

		// this is to make the room appear with the grid
		m_pCollisionMap->convertScreenToMap(&x, &y);
		x = x * m_pCollisionMap->getWidth_tile();
		y = y * m_pCollisionMap->getHeight_tile();
		spawnCoords.setCoords(x, y);

		if (is1pressed && !is2pressed && !is3pressed && !is4pressed) // generate 1x1
		{
			int offset = 1;
			int w = 32;
			int h = 32;

			SCoords2<int> topLeft, topRight, bottomLeft, bottomRight;
			topLeft.setCoords(spawnCoords.x + offset, spawnCoords.y + offset);
			topRight.setCoords(spawnCoords.x + w - offset, spawnCoords.y + offset);
			bottomLeft.setCoords(spawnCoords.x + 1, spawnCoords.y + h - 1);
			bottomRight.setCoords(spawnCoords.x + w - offset, spawnCoords.y + h - offset);

			// don't let a room spawn on another room
			for (int i = 0; i < m_roomVector.size(); ++i)
			{
				if (m_roomVector.at(i)->collision(&topLeft) == true)
				{
					return false;
				}

				if (m_roomVector.at(i)->collision(&topRight) == true)
				{
					return false;
				}

				if (m_roomVector.at(i)->collision(&bottomLeft) == true)
				{
					return false;
				}

				if (m_roomVector.at(i)->collision(&bottomRight) == true)
				{
					return false;
				}
			}

			m_roomVector.push_back(new CRoom_1x1(m_pWindow, m_pCollisionMap, &m_roomVector,
			                                     spawnCoords, "Resource Files/Rooms/room 1x1.png",
			                                     w, h, 1, 1));
		}
		else if (!is1pressed && is2pressed && !is3pressed && !is4pressed) // generate 1x2
		{
		}
		else if (!is1pressed && !is2pressed && is3pressed && !is4pressed) // generate 2x1
		{
		}
		else if (!is1pressed && !is2pressed && !is3pressed && is4pressed) // generate 2x2
		{
			int offset = 1;
			int w = 64;
			int h = 64;

			SCoords2<int> topLeft, topRight, bottomLeft, bottomRight;
			topLeft.setCoords(spawnCoords.x + offset, spawnCoords.y + offset);
			topRight.setCoords(spawnCoords.x + w - offset, spawnCoords.y + offset);
			bottomLeft.setCoords(spawnCoords.x + 1, spawnCoords.y + h - 1);
			bottomRight.setCoords(spawnCoords.x + w - offset, spawnCoords.y + h - offset);

			// don't let a room spawn on another room
			for (int i = 0; i < m_roomVector.size(); ++i)
			{
				if (m_roomVector.at(i)->collision(&topLeft) == true)
				{
					return false;
				}

				if (m_roomVector.at(i)->collision(&topRight) == true)
				{
					return false;
				}

				if (m_roomVector.at(i)->collision(&bottomLeft) == true)
				{
					return false;
				}

				if (m_roomVector.at(i)->collision(&bottomRight) == true)
				{
					return false;
				}
			}

			m_roomVector.push_back(new CRoom_2x2(m_pWindow, m_pCollisionMap, &m_roomVector,
			                                     spawnCoords, "Resource Files/Rooms/room 2x2.png",
			                                     w, h, 1, 1));
		}

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