#include "stdafx.h"
#include "CUpdatable.h"


CUpdatable::CUpdatable(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
                       SCoords2<int> spawnCoords_screen,
                       std::string filePath, int imageWidth, int imageHeight,
                       int numImages_rows, int numImages_columns)
{
	m_pWindow = window;
	m_pMap_collision = collisionMap;
	m_pRoom_collision = collisionRoom;

	m_width = imageWidth;
	m_height = imageHeight;

	setTopLeft(spawnCoords_screen);

	m_pSprite = new CSprite(window, filePath,
	                        imageWidth, imageHeight,
	                        numImages_rows, numImages_columns);

	isFirstUpdate = true;
	isToBeDeleted = false;

	m_sAtributes.defaultVelosity_neg = -2;
	m_sAtributes.defaultVelosity_pos = 2;
	m_sAtributes.nullVelosity();
}


CUpdatable::CUpdatable() {}


CUpdatable::~CUpdatable()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


void CUpdatable::getEverything(SCoords2<int>* pTopLeft, SCoords2<int>* pTopRight,
                               SCoords2<int>* pBottomLeft, SCoords2<int>* pBottomRight)
{
	pTopLeft->setCoords(m_topLeft.x, m_topLeft.y);
	pTopRight->setCoords(m_topRight.x, m_topRight.y);
	pBottomLeft->setCoords(m_bottomLeft.x, m_bottomLeft.y);
	pBottomRight->setCoords(m_bottomRight.x, m_bottomRight.y);
}


void CUpdatable::getMinMax(SCoords2<int>* pTopLeft, SCoords2<int>* pBottomRight)
{
	*pTopLeft = m_topLeft;
	*pBottomRight = m_bottomRight;
}


int CUpdatable::getWidth()
{
	return m_width;
}


int CUpdatable::getHeight()
{
	return m_height;
}

void CUpdatable::setEverything(SCoords2<int> topLeft, SCoords2<int> topRight,
                               SCoords2<int> bottomLeft, SCoords2<int> bottomRight)
{
	// not implemented yet
	assert(false);
}


void CUpdatable::setTopLeft(SCoords2<int> topLeft)
{
	m_topLeft.setCoords(topLeft.x, topLeft.y);

	m_topRight.setCoords(topLeft.x + m_width, topLeft.y);

	m_bottomLeft.setCoords(topLeft.x, topLeft.y + m_height);

	m_bottomRight.setCoords(topLeft.x + m_width, topLeft.y + m_height);
}


void CUpdatable::setTopLeft(int x, int y)
{
	m_topLeft.setCoords(x, y);

	m_topRight.setCoords(x + m_width, y);

	m_bottomLeft.setCoords(x, y + m_height);

	m_bottomRight.setCoords(x + m_width, y + m_height);
}


void CUpdatable::setTopRight(SCoords2<int> topRight)
{
	m_topLeft.setCoords(topRight.x - m_width, topRight.y);

	m_topRight.setCoords(topRight.x, topRight.y);

	m_bottomLeft.setCoords(topRight.x - m_width, topRight.y + m_height);

	m_bottomRight.setCoords(topRight.x, topRight.y + m_height);
}


void CUpdatable::setTopRight(int x, int y)
{
	m_topLeft.setCoords(x - m_width, y);

	m_topRight.setCoords(x, y);

	m_bottomLeft.setCoords(x - m_width, y + m_height);

	m_bottomRight.setCoords(x, y + m_height);
}


void CUpdatable::setBottomLeft(SCoords2<int> bottomLeft)
{
	m_topLeft.setCoords(bottomLeft.x, bottomLeft.y - m_height);

	m_topRight.setCoords(bottomLeft.x + m_width, bottomLeft.y - m_height);

	m_bottomLeft.setCoords(bottomLeft.x, bottomLeft.y);

	m_bottomRight.setCoords(bottomLeft.x + m_width, bottomLeft.y);
}


void CUpdatable::setBottomLeft(int x, int y)
{
	m_topLeft.setCoords(x, y - m_height);

	m_topRight.setCoords(x + m_width, y - m_height);

	m_bottomLeft.setCoords(x, y);

	m_bottomRight.setCoords(x + m_width, y);
}


void CUpdatable::setBottomRight(SCoords2<int> bottomRight)
{
	m_topLeft.setCoords(bottomRight.x - m_width, bottomRight.y - m_height);

	m_topRight.setCoords(bottomRight.x, bottomRight.y - m_height);

	m_bottomLeft.setCoords(bottomRight.x - m_width, bottomRight.y);

	m_bottomRight.setCoords(bottomRight.x, bottomRight.y);
}


void CUpdatable::setBottomRight(int x, int y)
{
	m_topLeft.setCoords(x - m_width, y - m_height);

	m_topRight.setCoords(x, y - m_height);

	m_bottomLeft.setCoords(x - m_width, y);

	m_bottomRight.setCoords(x, y);
}


bool CUpdatable::collision(SCoords2<int>* pPoint)
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


void CUpdatable::update() {} // virtual


void CUpdatable::render()
{
	m_pSprite->render(m_topLeft.x, m_topLeft.y, m_width, m_height);
}


void CUpdatable::offCollisionMap()
{
	// +2 just to make absolutely sure that the room is off of the collision map
	int maxRowScreenCoord_y = (m_pMap_collision->getRows() + 4) * m_pMap_collision->getHeight_tile();

	if (m_bottomLeft.y + m_sAtributes.velosity_y > maxRowScreenCoord_y ||
	        m_bottomRight.y + m_sAtributes.velosity_y > maxRowScreenCoord_y)
	{
		isToBeDeleted = true;
	}
}

bool CUpdatable::correctMapCollision_down()
{
	// get the x coord in map space for a fast search
	int column = m_topLeft.x + m_sAtributes.velosity_x;
	int row = m_topLeft.y + m_sAtributes.velosity_y;
	m_pMap_collision->convertScreenToMap(&column, &row);

	const std::vector<STileData<int>*>* pMapTiles = m_pMap_collision->getMapTiles();
	for (int i = 0; i < pMapTiles->size(); ++i)
	{
		STileData<int>* pTile = pMapTiles->at(i);

		// we are only looking for a specific column (falling down), no need to search needlessly
		if (pTile->mapCoords.x != column)
		{
			continue;
		}

		SCoords2<int> midBottom;
		midBottom.setCoords(m_bottomLeft.x + m_width / 2, (int)(m_bottomLeft.y + m_sAtributes.velosity_y));
		if (pTile->collision(&midBottom))
		{
			setBottomRight(pTile->screenCoords_topLeft.x + pTile->width, pTile->screenCoords_topLeft.y);

			isFalling = false;
			m_sAtributes.gravityTimer.start();
			return true;
		}
	}

	return false;
}
