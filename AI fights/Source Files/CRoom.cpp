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

	m_coord_column = spawnCoords_screen.x;
	m_coord_column = m_pCollisionMap->convertScreenToMap_X(m_coord_column);

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


void CRoom::getEverything(SCoords2<int>* pTopLeft, SCoords2<int>* pTopRight,
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


int CRoom::getColumn()
{
	return m_coord_column;
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


bool CRoom::equals(int mapColumn)
{
	if (mapColumn == m_coord_column)
		return true;

	return false;
}


bool CRoom::collision(SCoords2<int>* pPoint)
{
	int x = pPoint->x;
	int y = pPoint->y;

	if (x > m_topLeft.x && x < m_bottomRight.x &&
		y > m_topLeft.y && y < m_bottomRight.y)
		return true;

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

	// only update the adjacent room pointers when not falling
	if (!isFalling)
	{
		checkPtrs(1); // for now just 1 pixel
	}
	else // is falling - null pointers to prevent weird pathing glitches
	{
		nullPtrs();
	}
}


void CRoom::render()
{
	m_pSprite->render(m_topLeft.x, m_topLeft.y, m_width, m_height);
}


void CRoom::nullPtrs()
{
	m_pRoomUp		= NULL;
	m_pRoomDown		= NULL;
	m_pRoomLeft		= NULL;
	m_pRoomRight	= NULL;
}


void CRoom::checkPtrs(int pixelCheck)
{
	bool isRoomUp		= false; 
	bool isRoomDown		= false; 
	bool isRoomLeft		= false;
	bool isRoomRight	= false;

	for (int i = 0; i < m_pRoomVector->size(); ++i)
	{
		CRoom* pRoom = m_pRoomVector->at(i);

		if (this->equals(pRoom))
			continue;

		// general logic:
		// if not found (false)
		//		then check to see if the room is found 
		//		& set to true if found, false if not

		if (isRoomUp == false)
		{
			isRoomUp = check_up(pRoom, pixelCheck);
		}
		if (isRoomDown == false)
		{
			isRoomDown = check_down(pRoom, pixelCheck);
		}
		if (isRoomLeft == false)
		{
			isRoomLeft = check_left(pRoom, pixelCheck);
		}
		if (isRoomRight == false)
		{
			isRoomRight = check_right(pRoom, pixelCheck);
		}
	}

	// if the room hasn't been found in its respective pointer, set that pointer to NULL
	//		indicating that there is not a room in that direction to pathing

	if (isRoomUp == false)
	{
		m_pRoomUp = NULL;
	}
	if (isRoomDown == false)
	{
		m_pRoomDown = NULL;
	}
	if (isRoomLeft == false)
	{
		m_pRoomLeft = NULL;
	}
	if (isRoomRight == false)
	{
		m_pRoomRight = NULL;
	}
}


bool CRoom::check_up(CRoom* roomToCheck, int pixelCheck)
{
	// can only check up if the room is in the same column
	if (this->equals(roomToCheck->getColumn()) == false)
		return false;

	SCoords2<int> pointToCheck;
	pointToCheck.x = m_topLeft.x + m_width / 2;
	pointToCheck.y = m_topLeft.y - pixelCheck;

	if (roomToCheck->collision(&pointToCheck) == true)
	{
		m_pRoomUp = roomToCheck;
		return true;
	}
	else
	{
		return false;
	}
}


bool CRoom::check_down(CRoom* roomToCheck, int pixelCheck)
{
	// can only check down if the room is in the same column
	if (this->equals(roomToCheck->getColumn()) == false)
		return false;

	SCoords2<int> pointToCheck;
	pointToCheck.x = m_topLeft.x + m_width / 2;
	pointToCheck.y = m_bottomRight.y + pixelCheck;

	if (roomToCheck->collision(&pointToCheck) == true)
	{
		m_pRoomDown = roomToCheck;
		return true;
	}
	else
	{
		return false;
	}
}


bool CRoom::check_left(CRoom* roomToCheck, int pixelCheck)
{
	// can only be left if it is -1 column away from this one
	if (m_coord_column-1 != roomToCheck->getColumn())
		return false;

	SCoords2<int> pointToCheck;
	pointToCheck.x = m_topLeft.x - pixelCheck;
	pointToCheck.y = m_topLeft.y + m_height / 2;

	if (roomToCheck->collision(&pointToCheck) == true)
	{
		m_pRoomLeft = roomToCheck;
		return true;
	}
	else
	{
		return false;
	}
}


bool CRoom::check_right(CRoom* roomToCheck, int pixelCheck)
{
	// can only be left if it is +1 column away from this one
	if (m_coord_column+1 != roomToCheck->getColumn())
		return false;

	SCoords2<int> pointToCheck;
	pointToCheck.x = m_bottomRight.x + pixelCheck;
	pointToCheck.y = m_bottomRight.y - m_height / 2;

	if (roomToCheck->collision(&pointToCheck) == true)
	{
		m_pRoomRight = roomToCheck;
		return true;
	}
	else
	{
		return false;
	}
}


bool CRoom::collision(SCoords2<int>* pTopLeft_this, SCoords2<int>* pBottomRight_this,
                      SCoords2<int>* pTopLeft_other, SCoords2<int>* pBottomRight_other)
{
	// check topLeft of 'this'
	if (pTopLeft_this->x > pTopLeft_other->x && pTopLeft_this->x < pBottomRight_other->x &&
	        pTopLeft_this->y > pTopLeft_other->y && pTopLeft_this->y < pBottomRight_other->y)
	{
		return true;
	}

	// check bottomRight of 'this'
	if (pBottomRight_this->x > pTopLeft_other->x && pBottomRight_this->x < pBottomRight_other->x &&
	        pBottomRight_this->y > pTopLeft_other->y && pBottomRight_this->y < pBottomRight_other->y)
	{
		return true;
	}

	return false;
}


bool CRoom::correctRoomCollision_down()
{
	for (int i = 0; i < m_pRoomVector->size(); ++i)
	{
		CRoom* pRoom = m_pRoomVector->at(i);

		if (this->equals(pRoom))
		{
			continue;
		}

		SCoords2<int> other_topLeft;
		SCoords2<int> other_topRight;
		SCoords2<int> other_bottomLeft;
		SCoords2<int> other_bottomRight;
		pRoom->getEverything(&other_topLeft, &other_topRight, &other_bottomLeft, &other_bottomRight);

		// +1 on topLeft.x and -1 on bottomRight.x because technically,
		//		rooms at column cord n and n+1 or n-1 share the same bondings,
		//		so just do collision detection on something that is slightly less than the
		//		width of the room so the rooms can be right next to one another
		SCoords2<int> this_topLeft, this_bottomRight;
		this_topLeft.x		= (m_topLeft.x + 1) + m_sAtributes.velosity_x;
		this_topLeft.y		= m_topLeft.y + m_sAtributes.velosity_y;
		this_bottomRight.x	= (m_bottomRight.x - 1) + m_sAtributes.velosity_x;
		this_bottomRight.y	= m_bottomRight.y + m_sAtributes.velosity_y;

		if (collision(&this_topLeft, &this_bottomRight, &other_topLeft, &other_bottomRight) == true)
		{
			setBottomRight(other_topRight.x, other_topRight.y);
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

		SCoords2<int> room_topLeft, room_bottomRight;
		room_topLeft.x		= (m_topLeft.x + 1) + m_sAtributes.velosity_x;
		room_topLeft.y		= m_topLeft.y + m_sAtributes.velosity_y;
		room_bottomRight.x	= (m_bottomRight.x - 1) + m_sAtributes.velosity_x;
		room_bottomRight.y	= m_bottomRight.y + m_sAtributes.velosity_y;

		SCoords2<int> tile_topLeft, tile_bottomRight;
		tile_topLeft.x		= pTile->screenCoords_topLeft.x;
		tile_topLeft.y		= pTile->screenCoords_topLeft.y;
		tile_bottomRight.x	= pTile->screenCoords_bottomRight.x;
		tile_bottomRight.y	= pTile->screenCoords_bottomRight.y;

		if (collision(&room_topLeft, &room_bottomRight, &tile_topLeft, &tile_bottomRight) == true)
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