#include "stdafx.h"
#include "CGenerator_AI.h"

CGenerator_AI::CGenerator_AI(CWindow* window, CMap* collisionMap, CPhysics* physics, Uint32 spawnTime_MS,
                             std::vector<CRoom*>* collisionRoom)

	: CGenerator(window, collisionMap, physics, spawnTime_MS)
{
	m_pRoom_collision = collisionRoom;

	isUpPressed		= false;
	isDownPressed	= false;
	isLeftPressed	= false;
	isRightPressed	= false;
}

CGenerator_AI::~CGenerator_AI()
{
	CGenerator::~CGenerator();

	clear();
}

const std::vector<CAI*>* CGenerator_AI::getAI()
{
	return &m_aiVector;
}


void CGenerator_AI::clear()
{
	m_aiVector.erase(m_aiVector.begin(), m_aiVector.end());
}


bool CGenerator_AI::generate(SDL_Event& e)
{
	checkMoveKeys(e);

	if (e.button.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT &&
	        (m_pSpawnTimer->getTime() - m_prevTimeSpawn) > m_spawnTime_MS)
	{
		int w = 10;
		int h = 10;
		int x = e.button.x;
		int y = e.button.y;
		SCoords2<int> spawnCoords;
		spawnCoords.setCoords(x, y);

		SCoords2<int> topLeft, topRight, bottomLeft, bottomRight;
		topLeft.setCoords(x, y);
		topRight.setCoords(x + w, y);
		bottomRight.setCoords(x + w, y + h);
		bottomLeft.setCoords(x, y + h);

		if (m_pRoom_collision->size() == 0)
			return false;

		bool isWithinARoom = false;
		CRoom* pSpawnRoom = NULL;
		for (int i = 0; i < m_pRoom_collision->size(); ++i)
		{
			pSpawnRoom = m_pRoom_collision->at(i);

			// want to spawn AI within rooms
			if (pSpawnRoom->collision(&topLeft) == true &&
				pSpawnRoom->collision(&topRight) == true &&
				pSpawnRoom->collision(&bottomLeft) == true &&
				pSpawnRoom->collision(&bottomRight) == true)
			{
				isWithinARoom = true;
				break;
			}
		}
		if (isWithinARoom == false)
		{
			return false;
		}

		CAI* pAI = new CAI(m_pWindow, m_pCollisionMap, m_pRoom_collision,
		                             spawnCoords, "Resource Files/AI/debug AI.png",
		                             w, h, 1, 1);
		pAI->setCurrentRoom(pSpawnRoom);

		m_aiVector.push_back(pAI);


		return true;
	}

	return false;
}

void CGenerator_AI::update()
{
	for (int i = 0; i < m_aiVector.size(); ++i)
	{
		CAI* pAI = m_aiVector.at(i);

		// delete a room if it is marked as needed to be deleted
		if (pAI->isToBeDeleted == true)
		{
			auto itr = m_aiVector.begin() + i;
			m_aiVector.erase(itr);
			continue;
		}

		pAI->setMove(isUpPressed, isDownPressed, isLeftPressed, isRightPressed);
		pAI->update();
	}
}

void CGenerator_AI::render()
{
	for (auto itr = m_aiVector.begin(); itr != m_aiVector.end(); ++itr)
	{
		(*itr)->render();
	}
}

void CGenerator_AI::checkMoveKeys(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			isUpPressed = true;
			break;
		case SDLK_DOWN:
			isDownPressed = true;
			break;
		case SDLK_LEFT:
			isLeftPressed = true;
			break;
		case SDLK_RIGHT:
			isRightPressed = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			isUpPressed = false;
			break;
		case SDLK_DOWN:
			isDownPressed = false;
			break;
		case SDLK_LEFT:
			isLeftPressed = false;
			break;
		case SDLK_RIGHT:
			isRightPressed = false;
			break;
		}
	}
}