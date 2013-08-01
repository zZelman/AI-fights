#include "stdafx.h"
#include "Math2D.h"


///////////////////////////////////////////////////////////////////////////////////////////////////


CVector2f::CVector2f() {}


CVector2f::CVector2f(float _x, float _y)
{
	x = _x;
	y = _y;
}


void CVector2f::setVars(float _x, float _y)
{
	x = _x;
	y = _y;
}


float CVector2f::length()
{
	return sqrtf(x * x + y * y);
}


void CVector2f::normalize()
{
	float length = this->length();

	x /= length;
	y /= length;
}


float CVector2f::dotProduct(CVector2f other)
{
	return (x * other.x) + (y * other.y);
}


float CVector2f::dotProduct(CVector2f other, float pheta)
{
	float length_a = length();
	float length_b = other.length();

	return length_a * length_b * cosf(pheta);
}


// returns in degrees
float CVector2f::findAngle(CVector2f other)
{
	float dot = dotProduct(other);
	float mag = length() * other.length();

	float pheta = acosf(dot / mag);

	return pheta;
}


///////////////////////////////////////////////////////////////////////////////////////////////////


CAABB_f::CAABB_f() {}


CAABB_f::CAABB_f(CVector2f* _min, CVector2f* _max)
{
	min = _min;
	max = _max;

	width = max->x - min->x;
	height = max->y - min->y;
}


CAABB_f::~CAABB_f()
{
	// no need to delete max/min because they are just pointers (no new was used in this class)
}


CVector2f* CAABB_f::getMin()
{
	return min;
}


CVector2f* CAABB_f::getMax()
{
	return max;
}


float CAABB_f::getWidth()
{
	return width;
}


float CAABB_f::getHeight()
{
	return height;
}


void CAABB_f::setEverything(float upperX, float upperY, float lowerX, float lowerY)
{
	// delete the previous CVector2f coords because you are reseting everything
	delete min;
	delete max;

	min = new CVector2f(upperX, upperY);
	max = new CVector2f(lowerX, lowerY);

	width = lowerX - upperX;
	height = lowerY - upperX;
}


void CAABB_f::setMin(CVector2f* _min)
{
	// delete because if you move the pointer you will cause a memory leak
	delete min;
	min = _min;

	// don't need to delete max because just changing values inside of max,
	//		not moving a pointer
	max->x = min->x + width;
	max->y = min->y + height;
}


void CAABB_f::setMin(float x, float y)
{
	setMinX(x);
	setMinY(y);
}


void CAABB_f::setMinX(float x)
{
	min->x = x;
	max->x = min->x + width;
}


void CAABB_f::setMinY(float y)
{
	min->y = y;
	max->y = min->y + height;
}


void CAABB_f::setMax(CVector2f* _max)
{
	// delete because if you move the pointer you will cause a memory leak
	delete max;
	max = _max;

	// don't need to delete min because just changing values inside of min,
	//		not moving a pointer
	min->x = max->x - width;
	min->y = max->y - height;
}


void CAABB_f::setMax(float x, float y)
{
	setMaxX(x);
	setMaxY(y);
}


void CAABB_f::setMaxX(float x)
{
	max->x = x;
	min->x = max->x - width;
}


void CAABB_f::setMaxY(float y)
{
	max->y = y;
	min->y = max->y - height;
}


bool CAABB_f::collision(CAABB_f* other)
{
	// exit with no intersection if found separated along an axis
	if (max->x < other->getMin()->x || min->x > other->getMax()->x)
	{
		return false;
	}
	if (max->y < other->getMin()->y || min->y > other->getMax()->y)
	{
		return false;
	}

	// no separating axis found, therefore there is at least one overlapping axis
	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////