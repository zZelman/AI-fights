#include "stdafx.h"
#include "CRoom.h"


CRoom::CRoom() {}


CRoom::CRoom(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
             SCoords2<int> spawnCoords_screen,
             std::string filePath, int imageWidth, int imageHeight,
             int numImages_rows, int numImages_columns)
{
	m_pWindow = window;
	m_pMap_collision = collisionMap;
	m_filePath = filePath;

	m_width = imageWidth;
	m_height = imageHeight;

	setTopLeft(spawnCoords_screen);

	m_coords.x = spawnCoords_screen.x;
	m_coords.y = spawnCoords_screen.y;
	m_pMap_collision->convertScreenToMap(&m_coords.x, &m_coords.y);

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
	return m_coords.x;
}


int CRoom::getWidth()
{
	return m_width;
}


int CRoom::getHeight()
{
	return m_height;
}


const SCoords2<int>* CRoom::getLayout()
{
	return &m_layout;
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


void CRoom::setBottomLeft(SCoords2<int> bottomLeft)
{
	m_topLeft.setCoords(bottomLeft.x, bottomLeft.y - m_height);

	m_topRight.setCoords(bottomLeft.x + m_width, bottomLeft.y - m_height);

	m_bottomLeft.setCoords(bottomLeft.x, bottomLeft.y);

	m_bottomRight.setCoords(bottomLeft.x + m_width, bottomLeft.y);
}


void CRoom::setBottomLeft(int x, int y)
{
	m_topLeft.setCoords(x, y - m_height);

	m_topRight.setCoords(x + m_width, y - m_height);

	m_bottomLeft.setCoords(x, y);

	m_bottomRight.setCoords(x + m_width, y);
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
	if (mapColumn == m_coords.x)
	{
		return true;
	}

	return false;
}


bool CRoom::collision(SCoords2<int>* pPoint)
{
	int x = pPoint->x;
	int y = pPoint->y;

	if (x >= m_topLeft.x && x <= m_bottomRight.x &&
	        y >= m_topLeft.y && y <= m_bottomRight.y)
	{
		return true;
	}

	return false;
}


void CRoom::update() {}


void CRoom::render()
{
	m_pSprite->render(m_topLeft.x, m_topLeft.y, m_width, m_height);
}


void CRoom::nullPtrs()
{
	m_pRoom_11_up		= NULL;
	m_pRoom_11_left		= NULL;

	m_pRoom_21_up		= NULL;
	m_pRoom_21_right	= NULL;

	m_pRoom_12_left		= NULL;
	m_pRoom_12_down		= NULL;

	m_pRoom_22_right	= NULL;
	m_pRoom_22_down		= NULL;
}


void CRoom::checkPtrs(int pixelCheck) {}


void CRoom::check_up(CRoom* roomToCheck, int pixelCheck) {}


void CRoom::check_down(CRoom* roomToCheck, int pixelCheck) {}


void CRoom::check_left(CRoom* roomToCheck, int pixelCheck) {}


void CRoom::check_right(CRoom* roomToCheck, int pixelCheck) {}


bool CRoom::collision(SCoords2<int>* pTopLeft_this, SCoords2<int>* pTopRight_this,
                      SCoords2<int>* pBottomLeft_this, SCoords2<int>* pBottomRight_this,

                      SCoords2<int>* pTopLeft_other, SCoords2<int>* pTopRight_other,
                      SCoords2<int>* pBottomLeft_other, SCoords2<int>* pBottomRight_other)
{
	// bottom checking first because this room class will MOSTLY be falling down .. small optimization

	// check bottomLeft of 'this'
	if (pBottomLeft_this->x > pBottomLeft_other->x && pBottomLeft_this->x < pBottomRight_other->x &&
	        pBottomLeft_this->y > pTopLeft_other->y && pBottomLeft_this->y < pBottomRight_other->y)
	{
		return true;
	}

	// check bottomRight of 'this'
	if (pBottomRight_this->x > pBottomLeft_other->x && pBottomRight_this->x < pBottomRight_other->x &&
	        pBottomRight_this->y > pTopRight_other->y && pBottomRight_this->y < pBottomRight_other->y)
	{
		return true;
	}

	// check topLeft of 'this'
	if (pTopLeft_this->x > pTopLeft_other->x && pTopLeft_this->x < pTopRight_other->x &&
	        pTopLeft_this->y > pTopLeft_other->y && pTopLeft_this->y < pBottomLeft_other->y)
	{
		return true;
	}

	// check topRight of 'this'
	if (pTopRight_this->x > pTopLeft_other->x && pTopRight_this->x < pTopRight_other->x &&
	        pTopRight_this->y > pTopRight_other->y && pTopRight_this->y < pBottomRight_other->y)
	{
		return true;
	}

	return false;
}


SCoords2<int> CRoom::whichSubRoom(SCoords2<int>* pPoint)
{
	// because this is the BASE CLASS just return the point as intersecting the top left sub room
	SCoords2<int> c;
	c.setCoords(1, 1);
	return c;
}


bool CRoom::correctRoomCollision_down()
{
#ifdef DEBUG
	assert(false);
#endif // DEBUG
	return false;
}


bool CRoom::correctMapCollision_down()
{
#ifdef DEBUG
	assert(false);
#endif // DEBUG
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