#ifndef CVECTOR2_H
#define CVECTOR2_H


#include "stdafx.h"

// representation of a vector with associated useful functions
template <class T>
class CVector2
{
public:
	T x, y; // public for ease of use

	CVector2();
	CVector2(T x, T y);

	void setVars(T x, T y);

	T length(); // or 'magnitude' in linear algebra terms
	void normalize(); // makes the total sum of the vector = 1
	T dotProduct(CVector2 other);
	//T dotProduct(CVector2 other, T pheta);
	T findAngle(CVector2 other); // returns in degrees

private:

};

template <class T>
CVector2<T>::CVector2() {}


template <class T>
CVector2<T>::CVector2(T x, T y)
{
	this->x = x;
	this->y = y;
}


template <class T>
void CVector2<T>::setVars(T x, T y)
{
	this->x = x;
	this->y = y;
}


template <class T>
T CVector2<T>::length()
{
	return sqrtf(x * x + y * y);
}


template <class T>
void CVector2<T>::normalize()
{
	T length = this->length();

	x /= length;
	y /= length;
}


template <class T>
T CVector2<T>::dotProduct(CVector2 other)
{
	return (x * other.x) + (y * other.y);
}


//template <class T>
//T CVector2<T>::dotProduct(CVector2 other, float pheta)
//{
//	T length_a = length();
//	T length_b = other.length();
//
//	return length_a * length_b * cosf(pheta);
//}


template <class T>
T CVector2<T>::findAngle(CVector2 other)
{
	T dot = dotProduct(other);
	T mag = length() * other.length();

	T pheta = acosf(dot / mag);

	return pheta;
}


#endif // !CVECTOR2_H