#pragma once

#include "stdafx.h"
#include "CBot.h"


///////////////////////////////////////////////////////////////////////////////////////////////////


#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))


///////////////////////////////////////////////////////////////////////////////////////////////////


//struct SCoords2i
//{
//	int x, y;
//
//	SCoords2i() {}
//	SCoords2i(int _x, int _y)
//	{
//		x = _x;
//		y = _y;
//	}
//};


///////////////////////////////////////////////////////////////////////////////////////////////////


// representation of a vector with associated useful functions
class CVector2f
{
public:
	float x, y; // public for ease of use

	CVector2f();
	CVector2f(float _x, float _y);

	void setVars(float _x, float _y);

	float length(); // or 'magnitude' in linear algebra terms
	void normalize(); // makes the total sum of the vector = 1
	float dotProduct(CVector2f other);
	float dotProduct(CVector2f other, float pheta);
	float findAngle(CVector2f other); // returns in degrees

};


///////////////////////////////////////////////////////////////////////////////////////////////////


// * Axis Aligned Bounding Box
// * used in collision detection
// * 'f' stands for float
class CAABB_f
{
public:
	CAABB_f();
	CAABB_f(CVector2f* _min, CVector2f* _max);
	~CAABB_f();

	CVector2f* getMin();
	CVector2f* getMax();
	CVector2f getMinS();
	CVector2f getMaxS();

	float getWidth();
	float getHeight();

	// * sets the min/max CVector2f
	// * calculates the width and height accordingly
	void setEverything(float upperX, float upperY, float lowerX, float lowerY);

	void setMin(CVector2f* _min);
	void setMin(float x, float y);
	void setMinX(float x);
	void setMinY(float y);

	void setMax(CVector2f* _max);
	void setMax(float x, float y);
	void setMaxX(float x);
	void setMaxY(float y);

	bool collision(CAABB_f* other); // heap collision detection

private:
	CVector2f* min; // represents the top left corner
	CVector2f* max; // represents the bottom right corner

	float width, height; // size of the AABB from the top left to each corresponding edge
};


///////////////////////////////////////////////////////////////////////////////////////////////////


// a manifold is a small object that contains information about a collision between two objects
struct SManifold
{
	CBot* bot1;
	CBot* bot2;
	float penetration;
	CVector2f normal;
};


///////////////////////////////////////////////////////////////////////////////////////////////////


// commented out because CBot isnt able to see this for whatever reason (in CBot.h atm)

//// Holds physics information about the object
//struct SAtributes
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