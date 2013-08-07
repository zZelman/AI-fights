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

	// set top
	setTopLeft(m_topLeft.x, m_topLeft.y + m_sAtributes.defaultVelosity_neg);
}


void CAI::moveDown()
{
	// TODO : have AI physics dependent

	// set bottom
	setBottomLeft(m_bottomLeft.x, m_bottomLeft.y + m_sAtributes.defaultVelosity_pos);
}


void CAI::moveLeft()
{
	// TODO : have AI physics dependent

	// set left
	setTopLeft(m_topLeft.x + m_sAtributes.defaultVelosity_neg, m_topLeft.y);
}


void CAI::moveRight()
{
	// TODO : have AI physics dependent

	// set right
	setTopRight(m_topRight.x + m_sAtributes.defaultVelosity_pos, m_topRight.y);
}