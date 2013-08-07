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
}


CAI::CAI() : CUpdatable() {}


CAI::~CAI()
{
	CUpdatable::~CUpdatable();
}


void CAI::setCurrentRoom( CRoom* pRoom )
{
	m_pCurrentRoom = pRoom;
}


void CAI::update()
{
	// move up
	if (isMovingUp && !isMovingDown)
	{
		moveUp();
	}

	// move down
	if (!isMovingUp && isMovingDown)
	{
		moveDown();
	}

	// move left
	if (isMovingLeft && !isMovingRight)
	{
		moveLeft();
	}

	// move right
	if (!isMovingLeft && isMovingRight)
	{
		moveRight();
	}
}



void CAI::setMove(bool up, bool down, bool left, bool right)
{
	isMovingUp		= up;
	isMovingDown	= down;
	isMovingLeft	= left;
	isMovingRight	= right;
}


void CAI::moveUp()
{
	// TODO : have AI physics dependent

	int increment = m_sAtributes.defaultVelosity_pos;

	// must collision detect on both the top and bottom corners so no phasing through
	SCoords2<int> stepUp_left, stepUp_right;
	stepUp_left.setCoords(m_topLeft.x, m_topLeft.y - increment);
	stepUp_right.setCoords(m_topRight.x, m_topRight.y - increment);

	// if next step of the bottom left corner is going out of the room
	if (m_pCurrentRoom->collision(&stepUp_left) == false)
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
			stepUp_left.setCoords(stepUp_left.x, room_topLeft.y);
		}

		setTopLeft(stepUp_left);
		return;
	}

	// if next step of the bottom right corner is going out of the room
	if (m_pCurrentRoom->collision(&stepUp_right) == false)
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
			stepUp_right.setCoords(stepUp_right.x, room_topLeft.y);
		}

		setTopRight(stepUp_right);
		return;
	}


	// nothing is obstructing the AI and the next step on both of the corners will be within the room
	// just step normally on either of the corners, it does not matter
	setTopLeft(stepUp_left);
}


void CAI::moveDown()
{
	// TODO : have AI physics dependent

	int increment = m_sAtributes.defaultVelosity_pos;

	// must collision detect on both the top and bottom corners so no phasing through
	SCoords2<int> stepDown_left, stepDown_right;
	stepDown_left.setCoords(m_bottomLeft.x, m_bottomLeft.y + increment);
	stepDown_right.setCoords(m_bottomRight.x, m_bottomRight.y + increment);

	// if next step of the bottom left corner is going out of the room
	if (m_pCurrentRoom->collision(&stepDown_left) == false)
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
			stepDown_left.setCoords(stepDown_left.x, room_bottomLeft.y);
		}

		setBottomLeft(stepDown_left);
		return;
	}

	// if next step of the bottom right corner is going out of the room
	if (m_pCurrentRoom->collision(&stepDown_right) == false)
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
			stepDown_right.setCoords(stepDown_right.x, room_bottomRight.y);
		}

		setBottomRight(stepDown_right);
		return;
	}


	// nothing is obstructing the AI and the next step on both of the corners will be within the room
	// just step normally on either of the corners, it does not matter
	setBottomLeft(stepDown_left);
}


void CAI::moveLeft()
{
	// TODO : have AI physics dependent

	int increment = m_sAtributes.defaultVelosity_pos;

	// must collision detect on both the top and bottom corners so no phasing through
	SCoords2<int> stepLeft_top, stepLeft_bottom;
	stepLeft_top.setCoords(m_topLeft.x - increment, m_topLeft.y);
	stepLeft_bottom.setCoords(m_bottomLeft.x - increment, m_bottomLeft.y);

	// if next step of the top left corner is going to go out of the room
	if (m_pCurrentRoom->collision(&stepLeft_top) == false)
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
			stepLeft_top.setCoords(room_topLeft.x, stepLeft_top.y);
		}

		setTopLeft(stepLeft_top);
		return;
	}

	// if the next step of the bottom left corner is going out of the room
	if (m_pCurrentRoom->collision(&stepLeft_bottom) == false)
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
			stepLeft_bottom.setCoords(room_topLeft.x, stepLeft_bottom.y);
		}

		setBottomLeft(stepLeft_bottom);
		return;
	}

	// nothing is obstructing the AI and the next step on both of the corners will be within the room
	// just step normally on either of the corners, it does not matter
	setBottomLeft(stepLeft_bottom);
}


void CAI::moveRight()
{
	// TODO : have AI physics dependent

	int increment = m_sAtributes.defaultVelosity_pos;
	
	// must collision detect on both the top and bottom corners so no phasing through
	SCoords2<int> stepRight_top, stepRight_bottom;
	stepRight_top.setCoords(m_topRight.x + increment, m_topRight.y);
	stepRight_bottom.setCoords(m_bottomRight.x + increment, m_bottomRight.y);

	// if next step of the top right corner is going to go out of the room
	if (m_pCurrentRoom->collision(&stepRight_top) == false)
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
			stepRight_top.setCoords(room_bottomRight.x, stepRight_top.y);
		}

		setTopRight(stepRight_top);
		return;
	}

	// if the next step of the bottom right corner is going out of the room
	if (m_pCurrentRoom->collision(&stepRight_bottom) == false)
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
			stepRight_bottom.setCoords(room_bottomRight.x, stepRight_bottom.y);
		}

		setBottomRight(stepRight_bottom);
		return;
	}

	// nothing is obstructing the AI and the next step on both of the corners will be within the room
	// just step normally on either of the corners, it does not matter
	setTopRight(stepRight_top);
}