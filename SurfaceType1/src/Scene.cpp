#include "Scene.hpp"
#include "Color.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

/* CONSTRUCT / DESTRUCT */

Scene::Scene() : _minx(0), _miny(0), _minz(0), _maxx(0), _maxy(0), _maxz(0)
{}

Scene::~Scene()
{}

/* METHODES */

void
Scene::setScalePts(void)
{
	int	size = this->_pts.size();
	int	iter = this->_b2D.getIter();

	std::cout << "min X: "  << this->_minx << std::endl;
	std::cout << "min Y: "  << this->_miny << std::endl;
	std::cout << "min Z: "  << this->_minz << std::endl;
	std::cout << "max X: "  << this->_maxx << std::endl;
	std::cout << "max Y: "  << this->_maxy << std::endl;
	std::cout << "max Z: "  << this->_maxz << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << "Entry: " << this->_pts[i] << std::endl;
		double x = iter * this->_pts[i].getX() / this->_maxx;
		double y = iter * this->_pts[i].getY() / this->_maxy;
		double z = iter * this->_pts[i].getZ() / this->_maxz;
		//double z = this->_pts[i].getZ();
		this->_ptsScale.push_back(Point<double>(x, z, y));
		std::cout << "new x: " << x << std::endl;
		std::cout << "new y: " << y << std::endl;
		std::cout << "new z: " << z << std::endl;
	}
}

void
Scene::setMinXYZ(void)
{
	if (this->_pts.size() == 0)
		return;
	this->_minx = this->_pts[0].getX();
	this->_miny = this->_pts[0].getY();
	this->_minz = this->_pts[0].getZ();
	for (unsigned int i = 1, size = this->_pts.size(); i < size; i++)
	{
		if (this->_pts[i].getX() < this->_minx)
			this->_minx = this->_pts[i].getX();
		if (this->_pts[i].getY() < this->_miny)
			this->_miny = this->_pts[i].getY();
		if (this->_pts[i].getZ() < this->_minz)
			this->_minz = this->_pts[i].getZ();
	}
}

void
Scene::setMaxXYZ(void)
{
	if (this->_pts.size() == 0)
		return;
	this->_maxx = this->_pts[0].getX();
	this->_maxy = this->_pts[0].getY();
	this->_maxz = this->_pts[0].getZ();
	for (unsigned int i = 1, size = this->_pts.size(); i < size; i++)
	{
		if (this->_pts[i].getX() > this->_maxx)
			this->_maxx = this->_pts[i].getX();
		if (this->_pts[i].getY() > this->_maxy)
			this->_maxy = this->_pts[i].getY();
		if (this->_pts[i].getZ() > this->_maxz)
			this->_maxz = this->_pts[i].getZ();
	}
}

void
Scene::setExtremeControlPoint(void)
{
	this->_pts.push_back(Point<double>(this->_minx - MARGE, this->_miny - MARGE, 0));

	this->_pts.push_back(Point<double>(this->_minx - MARGE, this->_maxy + MARGE,0));

	this->_pts.push_back(Point<double>(this->_maxx + MARGE, this->_miny - MARGE, 0));

	this->_pts.push_back(Point<double>(this->_maxx + MARGE, this->_maxy + MARGE, 0));
}

bool
Scene::setPts(const char *p)
{
	std::ifstream	ifs;
	std::string		content;
	int				begin = -1;
	int				end = -1;
	double			x,y,z;

	ifs.open(p);
	if (ifs.is_open() == false) {
		std::cerr << "Bad file" << std::endl;
		return false;
	}
	content.assign((std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()));
	ifs.close();
	for (unsigned int i = 0, size = content.length(); i < size; i = i + 1)
	{
		if (content[i] == '(')
			begin = i;
		if (content[i] == ')')
			end = i;
		if (content[i] == ',')
			content[i] = ' ';
		if (begin != -1 && end != -1)
		{
			std::stringstream ss;
			ss << content.substr(begin + 1, end - begin - 1);
			ss >> x >> y >> z;
			Point<double> p(x,y,z);
			this->_pts.push_back(p);
			begin = -1;
			end = -1;
			if (this->_pts.size() > 50) {
				break ;
			}
		}
	}
	std::sort(this->_pts.begin(), this->_pts.end(), xIncrease());
	return (true);
}

/* GETTERS */

float	Scene::getMinX(void) const { return this->_minx; }
float	Scene::getMinY(void) const { return this->_miny; }
float	Scene::getMinZ(void) const { return this->_minz; }
float	Scene::getMaxX(void) const { return this->_maxx; }
float	Scene::getMaxY(void) const { return this->_maxy; }
float	Scene::getMaxZ(void) const { return this->_maxz; }
int		Scene::getBezierIter(void) const { return this->_b2D.getIter(); }

/* BEZIER */

std::vector<Point<double>> &
Scene::getBezierAprox(void) { return this->_b2D.getAprox(); }

void
Scene::clearBezierAprox(void)
{
	this->_b2D.clearAprox();
}

void
Scene::computeBezier2D(void)
{
	this->_b2D.compute(this->_pts);
}

void
Scene::computeBezier2D(std::vector<Point<double>> & pts)
{
	this->_b2D.compute(pts);
}
