#include "Scene.hpp"
#include "Color.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

/* CONSTRUCT / DESTRUCT */

Scene::Scene(int size) :
	_minx(0), _miny(0), _minz(0),
	_maxx(0), _maxy(0), _maxz(0),
	_sizeMap(size)
{
	(void)_sizeMap;
}

Scene::~Scene()
{}

/* METHODES */

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

