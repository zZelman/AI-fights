#include "stdafx.h"
#include "CRoom.h"


CRoom::CRoom(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
             SCoords2<int> spawnCoords_screen,
             std::string filePath, int imageWidth, int imageHeight,
             int numImages_rows, int numImages_columns)

	: CUpdatable(window, collisionMap, collisionRoom,
	             spawnCoords_screen,
	             filePath, imageWidth, imageHeight, numImages_rows, numImages_columns)
{
	m_coords.x = spawnCoords_screen.x;
	m_coords.y = spawnCoords_screen.y;
	m_pMap_collision->convertScreenToMap(&m_coords.x, &m_coords.y);
}


CRoom::CRoom() {}


CRoom::~CRoom()
{
	CUpdatable::~CUpdatable();
}


int CRoom::getColumn()
{
	return m_coords.x;
}


const SCoords2<int>* CRoom::getLayout()
{
	return &m_layout;
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


void CRoom::update() {}


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


//bool CRoom::collision(SCoords2<int>* pTopLeft_this, SCoords2<int>* pTopRight_this,
//                      SCoords2<int>* pBottomLeft_this, SCoords2<int>* pBottomRight_this,
//
//                      SCoords2<int>* pTopLeft_other, SCoords2<int>* pTopRight_other,
//                      SCoords2<int>* pBottomLeft_other, SCoords2<int>* pBottomRight_other)
//{
//	// bottom checking first because this room class will MOSTLY be falling down .. small optimization
//
//	// check bottomLeft of 'this'
//	if (pBottomLeft_this->x > pBottomLeft_other->x && pBottomLeft_this->x < pBottomRight_other->x &&
//	        pBottomLeft_this->y > pTopLeft_other->y && pBottomLeft_this->y < pBottomRight_other->y)
//	{
//		return true;
//	}
//
//	// check bottomRight of 'this'
//	if (pBottomRight_this->x > pBottomLeft_other->x && pBottomRight_this->x < pBottomRight_other->x &&
//	        pBottomRight_this->y > pTopRight_other->y && pBottomRight_this->y < pBottomRight_other->y)
//	{
//		return true;
//	}
//
//	// check topLeft of 'this'
//	if (pTopLeft_this->x > pTopLeft_other->x && pTopLeft_this->x < pTopRight_other->x &&
//	        pTopLeft_this->y > pTopLeft_other->y && pTopLeft_this->y < pBottomLeft_other->y)
//	{
//		return true;
//	}
//
//	// check topRight of 'this'
//	if (pTopRight_this->x > pTopLeft_other->x && pTopRight_this->x < pTopRight_other->x &&
//	        pTopRight_this->y > pTopRight_other->y && pTopRight_this->y < pBottomRight_other->y)
//	{
//		return true;
//	}
//
//	return false;
//}


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