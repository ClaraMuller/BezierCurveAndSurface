#include <Bezier2D.hpp>
#include <Color.hpp>

Bezier2D::Bezier2D(const int iter) : _iter(iter)
{}

Bezier2D::Bezier2D(const Bezier2D& o) : _iter(o._iter)
{
	*this = o;
}

Bezier2D&
Bezier2D::operator=(const Bezier2D& o)
{
	(void)o;
	return (*this);
}

unsigned int
Bezier2D::getIter(void) const { return this->_iter; }

std::list<Point<double> >&
Bezier2D::getAprox(void)
{
	return this->_aprox;
}

void
Bezier2D::clearAprox(void)
{
	this->_aprox.clear();
}

void
Bezier2D::casteljau(const std::vector<Point<double>> & v, float t)
{
	std::vector<Point<double>>	pts;
	int				size = v.size();
	Color				yellow(255, 222, 0);

	if (size <= 1)
	{
		// Dernier donc a ajouter dans _aprox
		this->_aprox.push_back(v[0]);
		return;
	}

	for (auto i = 0; i < size - 1; i++)
	{
		double x = v[i].getX() + (v[i + 1].getX() - v[i].getX()) * t;
		double y = v[i].getY() + (v[i + 1].getY() - v[i].getY()) * t;
		pts.push_back(Point<double>(x, y, 0));
	}
	this->casteljau(pts, t);
}

