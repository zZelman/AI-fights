#ifndef SCOORDS2_H
#define SCOORDS2_H


template <typename T>
struct SCoords2
{
	T x, y;

	SCoords2() {}
	SCoords2(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	template <typename T>
	void operator=(SCoords2<T> other)
	{
		x = other.x;
		y = other.y;
	}

	template <typename T>
	void setCoords(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	template <typename T>
	void setX(T _x)
	{
		x = _x;
	}

	template <typename T>
	void setY(T _y)
	{
		y = _y;
	}

	template <typename T>
	bool equals(SCoords2<T> other)
	{
		if (x == other.x && y == other.y)
		{
			return true;
		}
		return false;
	}
};


#endif // !SCOORDS2_H