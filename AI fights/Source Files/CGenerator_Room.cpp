#include "stdafx.h"

#include "CGenerator_Room.h"

CGenerator_room::CGenerator_room(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS)
	: CGenerator(window, collisionMap, physics, spawnTime_MS)
{
	is1pressed = false;
	is2pressed = false;
	is3pressed = false;
	is4pressed = false;
}


CGenerator_room::~CGenerator_room()
{
	CGenerator::~CGenerator();

	clear();
}


std::vector<CRoom*>* CGenerator_room::getRooms()
{
	return &m_roomVector;
}


void CGenerator_room::clear()
{
	m_roomVector.erase(m_roomVector.begin(), m_roomVector.end());
}


bool CGenerator_room::generate(SDL_Event& e)
{
	checkSpawnKeys(e);

	if (e.button.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT &&
	        (m_pSpawnTimer->getTime() - m_prevTimeSpawn) > m_spawnTime_MS)
	{
		int x = e.button.x;
		int y = e.button.y;

		//// debug testing
		//int x = 32;
		//int y = 32;

		SCoords2<int> spawnCoords;
		spawnCoords.setCoords(x, y);

		// * this is to make the room appear with the grid
		// * NOTE!!!! in order for rooms to be spawned correctly they must STAY on the inate map grid
		//		so, if the screen cuts one row/column in to sections, then the rooms will fall OFF
		//		map grid, or be misaligned to to it.
		//		FIX: do not let rooms fall onto the window edges and stop -> falling off of window destroys room
		m_pCollisionMap->convertScreenToMap(&x, &y);
		x = x * m_pCollisionMap->getWidth_tile();
		y = y * m_pCollisionMap->getHeight_tile();
		spawnCoords.setCoords(x, y);

		if (is1pressed && !is2pressed && !is3pressed && !is4pressed) // 1: generate 1x1
		{
			if (!spawn_1x1(e, &spawnCoords))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (!is1pressed && is2pressed && !is3pressed && !is4pressed) // 2: generate 1x2
		{
			if (!spawn_1x2(e, &spawnCoords))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (!is1pressed && !is2pressed && is3pressed && !is4pressed) // 3: generate 2x1
		{
			if (!spawn_2x1(e, &spawnCoords))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (!is1pressed && !is2pressed && !is3pressed && is4pressed) // 4: generate 2x2
		{
			if (!spawn_2x2(e, &spawnCoords))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}


void CGenerator_room::checkSpawnKeys(SDL_Event& e)
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
}


bool CGenerator_room::spawn_1x1(SDL_Event& e, SCoords2<int>* spawnCoords)
{
	int offset = 3;
	int w = 32;
	int h = 32;

	SCoords2<int> topLeft, topRight, bottomLeft, bottomRight;
	topLeft.setCoords(spawnCoords->x + offset, spawnCoords->y + offset);
	topRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + offset);
	bottomLeft.setCoords(spawnCoords->x + 1, spawnCoords->y + h - offset);
	bottomRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + h - offset);

	// something is preventing the spawn
	if (!preventCollisions(&topLeft, &topRight, &bottomLeft, &bottomRight))
	{
		return false;
	}

	m_roomVector.push_back(new CRoom_1x1(m_pWindow, m_pCollisionMap, &m_roomVector,
	                                     *spawnCoords, "Resource Files/Rooms/room 1x1.png",
	                                     w, h, 1, 1));

	m_prevTimeSpawn = m_pSpawnTimer->getTime();
	return true;
}


bool CGenerator_room::spawn_1x2(SDL_Event& e, SCoords2<int>* spawnCoords)
{
	int offset = 3;
	int w = 32;
	int h = 64;

	SCoords2<int> topLeft, topRight, bottomLeft, bottomRight;
	topLeft.setCoords(spawnCoords->x + offset, spawnCoords->y + offset);
	topRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + offset);
	bottomLeft.setCoords(spawnCoords->x + 1, spawnCoords->y + h - offset);
	bottomRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + h - offset);

	// something is preventing the spawn
	if (!preventCollisions(&topLeft, &topRight, &bottomLeft, &bottomRight))
	{
		return false;
	}

	m_roomVector.push_back(new CRoom_1x2(m_pWindow, m_pCollisionMap, &m_roomVector,
	                                     *spawnCoords, "Resource Files/Rooms/room 1x2.png",
	                                     w, h, 1, 1));

	m_prevTimeSpawn = m_pSpawnTimer->getTime();
	return true;
}


bool CGenerator_room::spawn_2x1(SDL_Event& e, SCoords2<int>* spawnCoords)
{
	int offset = 3;
	int w = 64;
	int h = 32;

	SCoords2<int> topLeft, topRight, bottomLeft, bottomRight;
	topLeft.setCoords(spawnCoords->x + offset, spawnCoords->y + offset);
	topRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + offset);
	bottomLeft.setCoords(spawnCoords->x + 1, spawnCoords->y + h - offset);
	bottomRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + h - offset);

	// something is preventing the spawn
	if (!preventCollisions(&topLeft, &topRight, &bottomLeft, &bottomRight))
	{
		return false;
	}

	m_roomVector.push_back(new CRoom_2x1(m_pWindow, m_pCollisionMap, &m_roomVector,
	                                     *spawnCoords, "Resource Files/Rooms/room 2x1.png",
	                                     w, h, 1, 1));

	m_prevTimeSpawn = m_pSpawnTimer->getTime();
	return true;
}


bool CGenerator_room::spawn_2x2(SDL_Event& e, SCoords2<int>* spawnCoords)
{
	int offset = 3;
	int w = 64;
	int h = 64;

	SCoords2<int> topLeft, topRight, bottomLeft, bottomRight;
	topLeft.setCoords(spawnCoords->x + offset, spawnCoords->y + offset);
	topRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + offset);
	bottomLeft.setCoords(spawnCoords->x + 1, spawnCoords->y + h - offset);
	bottomRight.setCoords(spawnCoords->x + w - offset, spawnCoords->y + h - offset);

	// something is preventing the spawn
	if (!preventCollisions(&topLeft, &topRight, &bottomLeft, &bottomRight))
	{
		return false;
	}

	m_roomVector.push_back(new CRoom_2x2(m_pWindow, m_pCollisionMap, &m_roomVector,
	                                     *spawnCoords, "Resource Files/Rooms/room 2x2.png",
	                                     w, h, 1, 1));

	m_prevTimeSpawn = m_pSpawnTimer->getTime();
	return true;
}


bool CGenerator_room::preventCollisions(SCoords2<int>* topLeft, SCoords2<int>* topRight,
                                        SCoords2<int>* bottomLeft, SCoords2<int>* bottomRight)
{
	// dont let a room spawn anywhere inside of a tile
	const std::vector<STileData<int>*>* pMapTiles = m_pCollisionMap->getMapTiles();
	for (int i = 0; i < pMapTiles->size(); ++i)
	{
		STileData<int>* pTile = pMapTiles->at(i);
		if (pTile->collision(topLeft) == true)
		{
			return false;
		}

		if (pTile->collision(topRight) == true)
		{
			return false;
		}

		if (pTile->collision(bottomLeft) == true)
		{
			return false;
		}

		if (pTile->collision(bottomRight) == true)
		{
			return false;
		}
	}

	// don't let a room spawn on another room
	for (int i = 0; i < m_roomVector.size(); ++i)
	{
		CRoom* pRoom = m_roomVector.at(i);
		if (pRoom->collision(topLeft) == true)
		{
			return false;
		}

		if (pRoom->collision(topRight) == true)
		{
			return false;
		}

		if (pRoom->collision(bottomLeft) == true)
		{
			return false;
		}

		if (pRoom->collision(bottomRight) == true)
		{
			return false;
		}
	}

	return true;
}


void CGenerator_room::update()
{
	for (int i = 0; i < m_roomVector.size(); ++i)
	{
		CRoom* pRoom = m_roomVector.at(i);

		// delete a room if it is marked as needed to be deleted
		if (pRoom->isToBeDeleted == true)
		{
			auto itr = m_roomVector.begin() + i;
			m_roomVector.erase(itr);
			continue;
		}

		m_pPhysics->applyGravity(pRoom);
		pRoom->update();
	}
}


void CGenerator_room::render()
{
	for (auto itr = m_roomVector.begin(); itr != m_roomVector.end(); ++itr)
	{
		(*itr)->render();
	}
}