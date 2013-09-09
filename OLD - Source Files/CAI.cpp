#include "stdafx.h"
#include "CAI.h"

CAI::CAI(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
         SCoords2<int> spawnCoords_screen,
         std::string filePath, int imageWidth, int imageHeight,
         int numImages_rows, int numImages_columns)

	: CUpdatable(window, collisionMap, collisionRoom,
	             spawnCoords_screen,
	             filePath, imageWidth, imageHeight,
	             numImages_rows, numImages_columns)
{
	isMovingUp		= false;
	isMovingDown	= false;
	isMovingLeft	= false;
	isMovingRight	= false;

	m_pCurrentRoom = NULL;
}


CAI::CAI() : CUpdatable() {}


CAI::~CAI()
{
	CUpdatable::~CUpdatable();
}


void CAI::setCurrentRoom(CRoom* pRoom)
{
	m_pCurrentRoom = pRoom;
}


void CAI::update()
{
	// change this to m_sAtributes.velosity_(x or y) to make ai dependant on physics
	int increment = m_sAtributes.defaultVelosity_pos;

	// move up
	if (isMovingUp && !isMovingDown)
	{
		// must collision detect on both the top and bottom corners so no phasing through
		SCoords2<int> left, right;
		left.setCoords(m_topLeft.x, m_topLeft.y - increment);
		right.setCoords(m_topRight.x, m_topRight.y - increment);
		if (!isCollision_up(&left, &right))
		{
			// no collisions, step normally (does not mater which corner gets updated)
			setTopLeft(left);
		}
	}

	// move down
	if (!isMovingUp && isMovingDown)
	{
		// must collision detect on both the top and bottom corners so no phasing through
		SCoords2<int> left, right;
		left.setCoords(m_bottomLeft.x, m_bottomLeft.y + increment);
		right.setCoords(m_bottomRight.x, m_bottomRight.y + increment);
		if (!isCollision_down(&left, &right))
		{
			// no collisions, step normally (does not mater which corner gets updated)
			setBottomLeft(left);
		}
	}

	// move left
	if (isMovingLeft && !isMovingRight)
	{
		// must collision detect on both the top and bottom corners so no phasing through
		SCoords2<int> top, bottom;
		top.setCoords(m_topLeft.x - increment, m_topLeft.y);
		bottom.setCoords(m_bottomLeft.x - increment, m_bottomLeft.y);
		if (!isCollision_left(&top, &bottom))
		{
			// no collisions, step normally (does not mater which corner gets updated)
			setTopLeft(top);
		}
	}

	// move right
	if (!isMovingLeft && isMovingRight)
	{
		// must collision detect on both the top and bottom corners so no phasing through
		SCoords2<int> top, bottom;
		top.setCoords(m_topRight.x + increment, m_topRight.y);
		bottom.setCoords(m_bottomRight.x + increment, m_bottomRight.y);
		if (!isCollision_right(&top, &bottom))
		{
			// no collisions, step normally (does not mater which corner gets updated)
			setTopRight(top);
		}
	}
}



void CAI::setMove(bool up, bool down, bool left, bool right)
{
	isMovingUp		= up;
	isMovingDown	= down;
	isMovingLeft	= left;
	isMovingRight	= right;
}


bool CAI::isCollision_up(SCoords2<int>* leftCorner, SCoords2<int>* rightCorner)
{
	// if next step of the bottom left corner is going out of the room
	if (m_pCurrentRoom->collision(leftCorner) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_topLeft);

		// within the top left sub room (1,1) and there is a room up
		if (currentSubRoom.x == 1 && m_pCurrentRoom->m_pRoom_11_up != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_11_up;
		}

		// within the bottom right sub room (2,1) and there is a room up
		else if (currentSubRoom.x == 2 && m_pCurrentRoom->m_pRoom_21_up != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_21_up;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomLeft;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomLeft);
			leftCorner->setCoords(leftCorner->x, room_topLeft.y);
			setTopLeft(*leftCorner);
			return true;
		}
	}

	// if next step of the bottom right corner is going out of the room
	if (m_pCurrentRoom->collision(rightCorner) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_topRight);

		// within the top left sub room (1,1) and there is a room up
		if (currentSubRoom.x == 1 && m_pCurrentRoom->m_pRoom_11_up != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_11_up;
		}

		// within the bottom right sub room (2,1) and there is a room up
		else if (currentSubRoom.x == 2 && m_pCurrentRoom->m_pRoom_21_up != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_21_up;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomRight;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomRight);
			rightCorner->setCoords(rightCorner->x, room_topLeft.y);
			setTopRight(*rightCorner);
			return true;
		}
	}

	// no collisions happend
	return false;
}


bool CAI::isCollision_down(SCoords2<int>* leftCorner, SCoords2<int>* rightCorner)
{
	// if next step of the bottom left corner is going out of the room
	if (m_pCurrentRoom->collision(leftCorner) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_bottomLeft);

		// within the top left sub room (1,2) and there is a room down
		if (currentSubRoom.x == 1 && m_pCurrentRoom->m_pRoom_12_down != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_12_down;
		}

		// within the bottom right sub room (2,2) and there is a room down
		else if (currentSubRoom.x == 2 && m_pCurrentRoom->m_pRoom_22_down != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_22_down;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomLeft;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomLeft);
			leftCorner->setCoords(leftCorner->x, room_bottomLeft.y);
			setBottomLeft(*leftCorner);
			return true;
		}
	}

	// if next step of the bottom right corner is going out of the room
	if (m_pCurrentRoom->collision(rightCorner) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_bottomRight);

		// within the top left sub room (1,2) and there is a room down
		if (currentSubRoom.x == 1 && m_pCurrentRoom->m_pRoom_12_down != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_12_down;
		}

		// within the bottom right sub room (2,2) and there is a room down
		else if (currentSubRoom.x == 2 && m_pCurrentRoom->m_pRoom_22_down != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_22_down;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomRight;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomRight);
			rightCorner->setCoords(rightCorner->x, room_bottomRight.y);
			setBottomRight(*rightCorner);
			return true;
		}
	}

	// no collisions
	return false;
}


bool CAI::isCollision_left(SCoords2<int>* top, SCoords2<int>* bottom)
{
	// if next step of the top left corner is going to go out of the room
	if (m_pCurrentRoom->collision(top) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_topLeft);

		// within the top left sub room (1,1) and there is a room to the left of that sub room
		if (currentSubRoom.y == 1 && m_pCurrentRoom->m_pRoom_11_left != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_11_left;
		}

		// within the bottom left sub room (1,2) and there is a room to the left of that sub room
		else if (currentSubRoom.y == 2 && m_pCurrentRoom->m_pRoom_12_left != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_12_left;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomRight;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomRight);
			top->setCoords(room_topLeft.x, top->y);
			setTopLeft(*top);
			return true;
		}
	}

	// if the next step of the bottom left corner is going out of the room
	if (m_pCurrentRoom->collision(bottom) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_bottomLeft);

		// within the top left sub room (1,1) and there is a room to the left of that sub room
		if (currentSubRoom.y == 1 && m_pCurrentRoom->m_pRoom_11_left != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_11_left;
		}

		// within the bottom left sub room (1,2) and there is a room to the right of that sub room
		else if (currentSubRoom.y == 2 && m_pCurrentRoom->m_pRoom_12_left != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_12_left;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomRight;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomRight);
			bottom->setCoords(room_topLeft.x, bottom->y);
			setBottomLeft(*bottom);
			return true;
		}
	}

	// no collisions
	return false;
}


bool CAI::isCollision_right(SCoords2<int>* top, SCoords2<int>* bottom)
{
	// if next step of the top right corner is going to go out of the room
	if (m_pCurrentRoom->collision(top) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_topRight);

		// within the top right sub room (2,1) and there is a room to the right of that sub room
		if (currentSubRoom.y == 1 && m_pCurrentRoom->m_pRoom_21_right != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_21_right;
		}

		// within the bottom right sub room (2,2) and there is a room to the right of that sub room
		else if (currentSubRoom.y == 2 && m_pCurrentRoom->m_pRoom_22_right != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_22_right;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomRight;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomRight);
			top->setCoords(room_bottomRight.x, top->y);
			setTopRight(*top);
			return true;
		}
	}

	// if the next step of the bottom right corner is going out of the room
	if (m_pCurrentRoom->collision(bottom) == false)
	{
		SCoords2<int> currentSubRoom = m_pCurrentRoom->whichSubRoom(&m_bottomRight);

		// within the top right sub room (2,1) and there is a room to the right of that sub room
		if (currentSubRoom.y == 1 && m_pCurrentRoom->m_pRoom_21_right != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_21_right;
		}

		// within the bottom right sub room (2,2) and there is a room to the right of that sub room
		else if (currentSubRoom.y == 2 && m_pCurrentRoom->m_pRoom_22_right != NULL)
		{
			// don't change anything on the step because nothing is obstructing
			m_pCurrentRoom = m_pCurrentRoom->m_pRoom_22_right;
		}
		else // step to the edge of the current room
		{
			SCoords2<int> room_topLeft, room_bottomRight;
			m_pCurrentRoom->getMinMax(&room_topLeft, &room_bottomRight);
			bottom->setCoords(room_bottomRight.x, bottom->y);
			setBottomRight(*bottom);
			return true;
		}
	}

	return false;
}

bool CAI::correctMapCollision_down()
{
	return CUpdatable::correctMapCollision_down();
}
