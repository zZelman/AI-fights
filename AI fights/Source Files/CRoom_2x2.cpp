#include "stdafx.h"

#include "CRoom_2x2.h"


CRoom_2x2::CRoom_2x2(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
                     SCoords2<int> spawnCoords_screen,
                     std::string filePath, int imageWidth, int imageHeight,
                     int numImages_rows, int numImages_columns)

	: CRoom(window, collisionMap, collisionRoom,
	        spawnCoords_screen,
	        filePath, imageWidth, imageHeight,
	        numImages_rows, numImages_columns)
{
	m_layout.setCoords(2, 2);
}

CRoom_2x2::~CRoom_2x2()
{
	CRoom::~CRoom();
}


void CRoom_2x2::update()
{
	// just to make sure that the first tick of time based things are not messy
	if (isFirstUpdate == true)
	{
		m_sAtributes.gravityTimer.start();
		isFirstUpdate = false;
	}

	offCollisionMap();

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


void CRoom_2x2::render()
{
	CRoom::render();
}


void CRoom_2x2::checkPtrs(int pixelCheck)
{
	nullPtrs();

	for (int i = 0; i < m_pRoom_collision->size(); ++i)
	{
		CRoom* pRoom = m_pRoom_collision->at(i);

		if (this->equals(pRoom))
		{
			continue;
		}

		// general logic:
		// if not found (false)
		//		then check to see if the room is found
		//		& set to true if found, false if not

		// [OPTIMIZATION]: have a better checking columns algorithm for 2x2 or 2x1 or 1x2 to exit checking early

		check_up(pRoom, pixelCheck);
		check_down(pRoom, pixelCheck);
		check_left(pRoom, pixelCheck);
		check_right(pRoom, pixelCheck);
	}
}


void CRoom_2x2::check_up(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_11_up == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topLeft.x + m_width / 4;
		pointToCheck.y = m_topLeft.y - pixelCheck;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_11_up = roomToCheck;
		}
	}

	// null means not found
	if (m_pRoom_21_up == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topRight.x - m_width / 4;
		pointToCheck.y = m_topRight.y - pixelCheck;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_21_up = roomToCheck;
		}
	}
}


void CRoom_2x2::check_down(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_12_down == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_bottomLeft.x + m_width / 4;
		pointToCheck.y = m_bottomLeft.y + pixelCheck;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_12_down = roomToCheck;
		}
	}

	// null means not found
	if (m_pRoom_22_down == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_bottomRight.x - m_width / 4;
		pointToCheck.y = m_bottomRight.y + pixelCheck;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_22_down = roomToCheck;
		}
	}
}


void CRoom_2x2::check_left(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_11_left == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topLeft.x - pixelCheck;
		pointToCheck.y = m_topLeft.y + m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_11_left = roomToCheck;
		}
	}

	// null means not found
	if (m_pRoom_12_left == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_bottomLeft.x - pixelCheck;
		pointToCheck.y = m_bottomLeft.y - m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_12_left = roomToCheck;
		}
	}
}


void CRoom_2x2::check_right(CRoom* roomToCheck, int pixelCheck)
{
	// null means not found
	if (m_pRoom_21_right == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_topRight.x + pixelCheck;
		pointToCheck.y = m_topRight.y + m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_21_right = roomToCheck;
		}
	}

	// null means not found
	if (m_pRoom_22_right == NULL)
	{
		SCoords2<int> pointToCheck;
		pointToCheck.x = m_bottomRight.x + pixelCheck;
		pointToCheck.y = m_bottomRight.y - m_height / 4;

		if (roomToCheck->collision(&pointToCheck) == true)
		{
			m_pRoom_22_right = roomToCheck;
		}
	}
}


SCoords2<int> CRoom_2x2::whichSubRoom(SCoords2<int>* pPoint)
{
	SCoords2<int> subRoom;
	int x = pPoint->x;
	int y = pPoint->y;

	// top left sub room (1,1)
	if (x >= m_topLeft.x && x <= (m_topLeft.x + m_width / 2) &&
	        y >= m_topLeft.y && y <= (m_topLeft.y + m_height / 2))
	{
		subRoom.setCoords(1, 1);
		return subRoom;
	}

	// top right sub room (2,1)
	if (x >= (m_topRight.x - m_width / 2) && x <= m_topRight.x &&
	        y >= m_topRight.y && y <= (m_topRight.y + m_height / 2))
	{
		subRoom.setCoords(2, 1);
		return subRoom;
	}

	// bottom left sub room (1,2)
	if (x >= m_bottomLeft.x && x <= (m_bottomLeft.x + m_width / 2) &&
	        y >= (m_bottomLeft.y - m_height / 2) && y <= m_bottomLeft.y)
	{
		subRoom.setCoords(1, 2);
		return subRoom;
	}

	// bottom right sub room (2,2)
	if (x >= (m_bottomRight.x - m_width / 2) && x <= m_bottomRight.x &&
	        y >= (m_bottomRight.y - m_height / 2) && y <= m_bottomRight.y)
	{
		subRoom.setCoords(2, 2);
		return subRoom;
	}

	// something went wrong
#ifdef DEBUG
	//assert(false);
#endif // DEBUG

	subRoom.setCoords(-1, -1);
	return subRoom;
}


bool CRoom_2x2::correctRoomCollision_down()
{
	for (int i = 0; i < m_pRoom_collision->size(); ++i)
	{
		CRoom* pRoom = m_pRoom_collision->at(i);

		if (this->equals(pRoom))
		{
			continue;
		}

		SCoords2<int> other_topLeft;
		SCoords2<int> other_topRight;
		SCoords2<int> other_bottomLeft;
		SCoords2<int> other_bottomRight;
		pRoom->getEverything(&other_topLeft, &other_topRight, &other_bottomLeft, &other_bottomRight);

		// Here we are going to do a point collision detection on the extended midpoint
		//		from all of the sub rooms along the bottom row. If ANY of them collide with something,
		//		the respective corner is set, and this room will not fall any farther
		SCoords2<int> this_midBottomLeft, this_midBottomRight;
		this_midBottomLeft.setCoords(
		    m_bottomLeft.x + m_width / 4,
		    (int)(m_bottomLeft.y + m_sAtributes.velosity_y));
		this_midBottomRight.setCoords(
		    m_bottomRight.x - m_width / 4,
		    (int)(m_bottomLeft.y + m_sAtributes.velosity_y));

		bool collision_bottomLeft = pRoom->collision(&this_midBottomLeft);
		bool collision_bottomRight = pRoom->collision(&this_midBottomRight);

		if (collision_bottomLeft && collision_bottomRight) // dead on collision
		{
			setBottomLeft(other_topLeft);
			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
		else if (collision_bottomLeft && !collision_bottomRight) // hanging off of the right side
		{
			if (pRoom->getLayout()->x == 1)
			{
				setBottomLeft(other_topLeft);
			}
			else if (pRoom->getLayout()->x == 2)
			{
				setBottomLeft(other_topLeft.x + pRoom->getWidth() / 2, other_topLeft.y);
			}

			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
		else if (!collision_bottomLeft && collision_bottomRight) // hanging off of the left side
		{
			if (pRoom->getLayout()->x == 1)
			{
				setBottomRight(other_topRight);
			}
			else if (pRoom->getLayout()->x == 2)
			{
				setBottomRight(other_topLeft.x + pRoom->getWidth() / 2, other_topLeft.y);
			}

			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
	}

	return false;
}


bool CRoom_2x2::correctMapCollision_down()
{
	//int left_column		= m_topLeft.x;
	//int left_row		= m_topLeft.y + m_sAtributes.velosity_y;
	//m_pMap_collision->convertScreenToMap(&left_column, &left_row);

	//int right_column	= m_topRight.x;
	//int right_row		= m_topRight.y + m_sAtributes.velosity_y;
	//m_pMap_collision->convertScreenToMap(&right_column, &right_row);

	// Here we are going to do a point collision detection on the extended midpoint
	//		from all of the sub rooms along the bottom row. If ANY of them collide with something,
	//		the respective corner is set, and this room will not fall any farther
	SCoords2<int> this_midBottomLeft, this_midBottomRight;
	this_midBottomLeft.setCoords(
	    m_bottomLeft.x + m_width / 4,
	    (int)(m_bottomLeft.y + m_sAtributes.velosity_y));
	this_midBottomRight.setCoords(
	    m_bottomRight.x - m_width / 4,
	    (int)(m_bottomLeft.y + m_sAtributes.velosity_y));

	const std::vector<STileData<int>*>* pMapTiles = m_pMap_collision->getMapTiles();
	for (int i = 0; i < pMapTiles->size(); ++i)
	{
		STileData<int>* pTile = pMapTiles->at(i);

		// [OPTIMIZATION]: how to column check when this is a 2x2 room?
		//if (pTile->mapCoords.x != left_column &&
		//        pTile->mapCoords.x != right_column)
		//{
		//	continue;
		//}

		bool collision_bottomLeft = pTile->collision(&this_midBottomLeft);
		bool collision_bottomRight = pTile->collision(&this_midBottomRight);

#ifdef DEBUG
		if (collision_bottomLeft && collision_bottomRight) // dead on collision
		{
			assert(false);// this should never happen because tiles are 1x1, and this room is 2x2
		}
#endif // !DEBG
		if (collision_bottomLeft && !collision_bottomRight) // hanging off of the right side
		{
			setBottomLeft(pTile->screenCoords_topLeft.x, pTile->screenCoords_topLeft.y);

			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
		else if (!collision_bottomLeft && collision_bottomRight) // hanging off of the left side
		{
			setBottomRight(pTile->screenCoords_bottomRight.x, pTile->screenCoords_bottomRight.y - pTile->height);

			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
	}


	return false;
}