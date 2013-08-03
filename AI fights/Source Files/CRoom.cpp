#include "stdafx.h"
#include "CRoom.h"


CRoom::CRoom(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
			 SCoords2<int> spawnCoords_screen,
			 std::string filePath, int imageWidth, int imageHeight,
			 int numImages_rows, int numImages_columns)
{
	m_pWindow = window;
	m_pCollisionMap = collisionMap;
	m_filePath = filePath;

	m_width = imageWidth;
	m_height = imageHeight;

	setTopLeft(spawnCoords_screen);

	m_pRoomVector = collisionRoom;

	m_pSprite = new CSprite(window, filePath, 
		imageWidth, imageHeight, 
		numImages_rows, numImages_columns);

	isFirstUpdate = true;

	m_sAtributes.defaultVelosity_neg = -2;
	m_sAtributes.defaultVelosity_pos = 2;
	m_sAtributes.nullVelosity();
}


CRoom::~CRoom()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


void CRoom::getEverything(	SCoords2<int>* pTopLeft, SCoords2<int>* pTopRight,
							 SCoords2<int>* pBottomLeft, SCoords2<int>* pBottomRight)
{
	pTopLeft->setCoords(m_topLeft.x, m_topLeft.y);
	pTopRight->setCoords(m_topRight.x, m_topRight.y);
	pBottomLeft->setCoords(m_bottomLeft.x, m_bottomLeft.y);
	pBottomRight->setCoords(m_bottomRight.x, m_bottomRight.y);
}


void CRoom::getMinMax(SCoords2<int>* pTopLeft, SCoords2<int>* pBottomRight)
{
	*pTopLeft = m_topLeft;
	*pBottomRight = m_bottomRight;
}


int CRoom::getWidth()
{
	return m_width;
}


int CRoom::getHeight()
{
	return m_height;
}


void CRoom::setEverything(SCoords2<int> topLeft, SCoords2<int> topRight, 
						  SCoords2<int> bottomLeft, SCoords2<int> bottomRight)
{
	// not implemented yet
	assert(false);
}


void CRoom::setTopLeft(SCoords2<int> topLeft)
{
	m_topLeft.setCoords(topLeft.x, topLeft.y);

	m_topRight.setCoords(topLeft.x + m_width, topLeft.y);

	m_bottomLeft.setCoords(topLeft.x, topLeft.y + m_height);

	m_bottomRight.setCoords(topLeft.x + m_width, topLeft.y + m_height);
}


void CRoom::setTopLeft(int x, int y)
{
	m_topLeft.setCoords(x, y);

	m_topRight.setCoords(x + m_width, y);

	m_bottomLeft.setCoords(x, y + m_height);

	m_bottomRight.setCoords(x + m_width, y + m_height);
}


void CRoom::setBottomRight(SCoords2<int> bottomRight)
{
	m_topLeft.setCoords(bottomRight.x - m_width, bottomRight.y - m_height);

	m_topRight.setCoords(bottomRight.x, bottomRight.y - m_height);

	m_bottomLeft.setCoords(bottomRight.x - m_width, bottomRight.y);

	m_bottomRight.setCoords(bottomRight.x, bottomRight.y);
}


void CRoom::setBottomRight(int x, int y)
{
	m_topLeft.setCoords(x - m_width, y - m_height);

	m_topRight.setCoords(x, y - m_height);

	m_bottomLeft.setCoords(x - m_width, y);

	m_bottomRight.setCoords(x, y);
}


bool CRoom::equals(CRoom* other)
{
	SCoords2<int> other_min;
	SCoords2<int> other_max;
	other->getMinMax(&other_min, &other_max);

	if (m_topLeft.equals(other_min) && m_bottomRight.equals(other_max))
	{
		return true;
	}
	return false;
}


void CRoom::update()
{
	// just to make sure that the first tick of time based things are not messy
	if (isFirstUpdate == true)
	{
		m_sAtributes.gravityTimer.start();
		isFirstUpdate = false;
	}

	if (!correctWindowCollision_down())
	{
		if (!correctRoomCollision_down())
		{
			if (!correctMapCollision_down())
			{
				m_topLeft.x += (int) m_sAtributes.velosity_x;
				m_topLeft.y += (int) m_sAtributes.velosity_y;

				setTopLeft(m_topLeft);

				isFalling = true;
			}
		}
	}
}


void CRoom::render()
{
	m_pSprite->render(m_topLeft.x, m_topLeft.y, m_width, m_height);
}


void CRoom::checkPtrs()
{
	check_up(m_pRoomUp);
	check_down(m_pRoomDown);
	check_left(m_pRoomLeft);
	check_right(m_pRoomRight);
}


void CRoom::check_up(CRoom* oldPtr)
{

}


void CRoom::check_down(CRoom* oldPtr)
{

}


void CRoom::check_left(CRoom* oldPtr)
{

}


void CRoom::check_right(CRoom* oldPtr)
{

}


bool CRoom::correctRoomCollision_down()
{
	for (int i = 0; i < m_pRoomVector->size(); ++i)
	{
		CRoom* pRoom = m_pRoomVector->at(i);

		if (this->equals(pRoom))
			continue;

		SCoords2<int> other_topLeft;
		SCoords2<int> other_topRight;
		SCoords2<int> other_bottomLeft;
		SCoords2<int> other_bottomRight;
		pRoom->getEverything(&other_topLeft, &other_topRight, &other_bottomLeft, &other_bottomRight);

		CAABB_f aabb_other;
		aabb_other.setEverything(&other_topLeft, &other_bottomRight);

		CAABB_f aabb_this; // TODO: have collision detection for NEXT STEP
		aabb_this.setEverything(
			m_topLeft.x + m_sAtributes.velosity_x, m_topLeft.y + m_sAtributes.velosity_y,
			m_bottomRight.x + m_sAtributes.velosity_x, m_bottomRight.y + m_sAtributes.velosity_y);

		if (aabb_this.collision(&aabb_other))
		{
			setBottomRight(other_topLeft.x + pRoom->getWidth(), other_topLeft.y);
			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
	}

	return false;
}


bool CRoom::correctMapCollision_down()
{
	// get the x coord in map space for a fast search
	int column = m_topLeft.x + m_sAtributes.velosity_x;
	int row = m_topLeft.y + m_sAtributes.velosity_y;
	m_pCollisionMap->convertScreenToMap(&column, &row);

	const std::vector<STileData<int>*>* pMapTiles = m_pCollisionMap->getMapTiles();
	for (int i = 0; i < pMapTiles->size(); ++i)
	{
		STileData<int>* pTile = pMapTiles->at(i);

		// we are only looking for a specific column (falling down), no need to search needlessly
		if (pTile->mapCoords.x != column)
		{
			continue;
		}

		// + velocities because we are checking the NEXT step
		CVector2<float> min_room(m_topLeft.x + m_sAtributes.velosity_x, m_topLeft.y + m_sAtributes.velosity_y);
		CVector2<float> max_room(m_bottomRight.x + m_sAtributes.velosity_x, m_bottomRight.y + m_sAtributes.velosity_y);
		CAABB_f aabb_room(&min_room, &max_room);

		CVector2<float> min_tile(pTile->screenCoords_topLeft.x, pTile->screenCoords_topLeft.y);
		CVector2<float> max_tile(pTile->screenCoords_bottomRight.x, pTile->screenCoords_bottomRight.y);
		CAABB_f aabb_tile(&min_tile, &max_tile);

		if (aabb_room.collision(&aabb_tile))
		{
			// want to set the room bottom right to the tile top right
			setBottomRight(pTile->screenCoords_topLeft.x + pTile->width, pTile->screenCoords_topLeft.y);

			isFalling = false;
			m_sAtributes.gravityTimer.start();
			return true;
		}
		
	}

	return false;
}


bool CRoom::correctWindowCollision_down()
{
	if (m_bottomLeft.y + m_sAtributes.velosity_y > m_pWindow->getHeight() ||
		m_bottomRight.y + m_sAtributes.velosity_y > m_pWindow->getHeight())
	{
		setBottomRight(m_bottomRight.x, m_pWindow->getHeight());
		m_sAtributes.gravityTimer.start();
		isFalling = false;
		return true;
	}
	return false;
}