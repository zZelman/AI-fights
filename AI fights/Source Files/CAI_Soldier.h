#ifndef CAI_SOLDIER_H
#define CAI_SOLDIER_H

#include "stdafx.h"
#include "CAI.h"
#include "CUpdatable.h"


class CAI_Soldier : public CAI
{
public:
	CAI_Soldier(CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom,
		SCoords2<int> spawnCoords_screen,
		std::string filePath, int imageWidth, int imageHeight,
		int numImages_rows = 1, int numImages_columns = 1);
	CAI_Soldier();
	~CAI_Soldier();

	void update();

private:
	// specific movement control
	bool isCollision_up(SCoords2<int>* leftCorner, SCoords2<int>* rightCorner);
	bool isCollision_down(SCoords2<int>* leftCorner, SCoords2<int>* rightCorner);
	bool isCollision_left(SCoords2<int>* top, SCoords2<int>* bottom);
	bool isCollision_right(SCoords2<int>* top, SCoords2<int>* bottom);

	// moves up the base classes to CUpdatable's correctMapCollision_down() method
	bool correctMapCollision_down();
};

CAI_Soldier::CAI_Soldier( CWindow* window, CMap* collisionMap, std::vector<CRoom*>* collisionRoom, 
						 SCoords2<int> spawnCoords_screen, std::string filePath, 
						 int imageWidth, int imageHeight, int numImages_rows, int numImages_columns)

	: CAI(window, collisionMap, collisionRoom, 
	spawnCoords_screen, filePath, 
	imageWidth, imageHeight, numImages_rows, numImages_columns)
{
	m_layout.setCoords(1, 1);
}


CAI_Soldier::CAI_Soldier() : CAI() {}


CAI_Soldier::~CAI_Soldier()
{
	CAI::~CAI();
}

void CAI_Soldier::update()
{
	if (!correctMapCollision_down())
	{
		m_topLeft.x += (int) m_sAtributes.velosity_x;
		m_topLeft.y += (int) m_sAtributes.velosity_y;

		setTopLeft(m_topLeft);

		isFalling = true;
	}

	if (!isFalling)
	{
		if (m_pAnimationTimer->getTime() > m_animationChangeMS)
		{
			m_sAnimationSequence.y = 1;
			if (m_sAnimationSequence.x + 1 > m_pSprite->getNumColumns())
			{
				m_sAnimationSequence.x = 1;
			}
			else
			{
				++m_sAnimationSequence.x;
			}

			m_pAnimationTimer->start();
		}
	}
}

bool CAI_Soldier::isCollision_up( SCoords2<int>* leftCorner, SCoords2<int>* rightCorner )
{

}

bool CAI_Soldier::isCollision_down( SCoords2<int>* leftCorner, SCoords2<int>* rightCorner )
{

}

bool CAI_Soldier::isCollision_left( SCoords2<int>* top, SCoords2<int>* bottom )
{

}

bool CAI_Soldier::isCollision_right( SCoords2<int>* top, SCoords2<int>* bottom )
{

}

bool CAI_Soldier::correctMapCollision_down()
{
	return CAI::correctMapCollision_down();
}


#endif // !CAI_SOLDIER_H
