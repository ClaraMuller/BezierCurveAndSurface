#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>

template <class T>
class Point
{
private:
	T	_x;
	T	_y;
	T	_z;

public:
	Point<T>(T x, T y, T z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	Point<T>(const Point & p)
	{
		*this = p;
	}

	Point<T> & operator=(const Point<T> & p)
	{
		_x = p._x;
		_y = p._y;
		_z = p._z;
		return *this;
	}

	virtual ~Point<T>() = default;

	bool compare(const Point & p) const
	{
		return (this->_x == p._x &&
				this->_y == p._y &&
				this->_z == p._z);
	}

	/* GET / SET */

	T	getX(void) const { return _x; }
	T	getY(void) const { return _y; }
	T	getZ(void) const { return _z; }
	void	setX(T param) { _x = param; }
	void	setY(T param) { _y = param; }
	void	setZ(T param) { _z = param; }

	/* MATHS */

	static void		linearInterpolation(Point<T> & dest, const Point<T> & a, const Point<T> b, const float t)
	{
		dest.setX(a.getX() + (b.getX() - a.getX()) * t);
		dest.setY(a.getY() + (b.getY() - a.getY()) * t);
	}

	static Point<T> &	linearInterpolation(const Point<T> & a, const Point<T> b, const float t)
	{
		T x = a.getX() + (b.getX() - a.getX()) * t;
		T y = a.getY() + (b.getY() - a.getY()) * t;
		return Point<T>(x, y, 0);
	}
};

template <class T>
std::ostream & operator<<(std::ostream & os, const Point<T> & o)
{
	os << "(" << o.getX() << "," << o.getY() << "," << o.getZ() << ")";
	return os;
}

struct xIncrease
{
	template <class T>
	inline bool operator() (const Point<T> & p1, const Point<T> & p2)
	{
		return (p1.getX() < p2.getX());
	}
};

#endif
