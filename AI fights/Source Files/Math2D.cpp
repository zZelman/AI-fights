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
	delete min;
	min = NULL;

	delete max;
	max = NULL;
}


CVector2f* CAABB_f::getMin()
{
	return min;
}


CVector2f* CAABB_f::getMax()
{
	return max;
}


void CAABB_f::setMin(CVector2f* _min)
{
	// delete because if you move the pointer you will cause a memory leak
	delete min;
	min = _min;

	// don't need to delete max because just changing values inside of max,
	//		not moving pointer
	max->x = min->x + width;
	max->y = min->y + height;
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
	//		not moving pointer
	min->x = max->x - width;
	min->y = max->y - height;
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


///////////////////////////////////////////////////////////////////////////////////////////////////