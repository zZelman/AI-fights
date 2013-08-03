#pragma once

#include "stdafx.h"
#include "CBot.h"

#include "CVector2.h"
#include "SCoords2.h"
#include "SAtributes.h"


///////////////////////////////////////////////////////////////////////////////////////////////////


#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

#define SecToMS(x) (float)( ((float)x) * ((float)1000) )
#define MStoSec(x) (float)( ((float)x) / ((float)1000) )

///////////////////////////////////////////////////////////////////////////////////////////////////


//struct SCoords2<int>
//{
//	int x, y;
//
//	SCoords2<int>() {}
//	SCoords2<int>(int _x, int _y)
//	{
//		x = _x;
//		y = _y;
//	}
//};


///////////////////////////////////////////////////////////////////////////////////////////////////


// * Axis Aligned Bounding Box
// * used in collision detection
// * 'f' stands for float
class CAABB_f
{
public:
	CAABB_f();
	CAABB_f(CVector2<float>* _min, CVector2<float>* _max);
	~CAABB_f();

	CVector2<float>* getMin();
	CVector2<float>* getMax();

	float getWidth();
	float getHeight();

	// * sets the min/max CVector2<float>
	// * calculates the width and height accordingly
	void setEverything(float upperX, float upperY, float lowerX, float lowerY);

	void setMin(CVector2<float>* _min);
	void setMin(float x, float y);
	void setMinX(float x);
	void setMinY(float y);

	void setMax(CVector2<float>* _max);
	void setMax(float x, float y);
	void setMaxX(float x);
	void setMaxY(float y);

	bool collision(CAABB_f* other); // heap collision detection

private:
	CVector2<float>* min; // represents the top left corner
	CVector2<float>* max; // represents the bottom right corner

	float width, height; // size of the AABB from the top left to each corresponding edge
};


///////////////////////////////////////////////////////////////////////////////////////////////////


// a manifold is a small object that contains information about a collision between two objects
struct SManifold
{
	CBot* bot1;
	CBot* bot2;
	float penetration;
	CVector2<float> normal;
};


///////////////////////////////////////////////////////////////////////////////////////////////////


// commented out because CBot isnt able to see this for whatever reason (in CBot.h atm)

//// Holds physics information about the object
//struct SAtributes<float>
//{
//	float defaultVelosity_pos; // DEFAULT movement size each update
//	float defaultVelosity_neg; // DEFAULT movement size each update
//	float velosity_x; // change in the x axis each update
//	float velosity_y; // change in the y axis each update
//	float mass;
//
//	void nullVelosity()
//	{
//		velosity_x = 0;
//		velosity_y = 0;
//	}
//
//	void nullVelosity_x()
//	{
//		velosity_x = 0;
//	}
//
//	void nullVelosity_y()
//	{
//		velosity_y = 0;
//	}
//};


///////////////////////////////////////////////////////////////////////////////////////////////////