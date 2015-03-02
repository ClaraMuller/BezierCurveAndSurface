#include "Scene.hpp"
#include "EnvSDL.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <M_Error.hpp>

/* CONSTRUCT / DESTRUCT */

Scene::Scene()
{}

Scene::~Scene()
{}

/* METHODES */

bool
Scene::setPts(const char *p)
{
	std::ifstream	ifs;
	std::string	content;
	int		begin = -1;
	int		end = -1;
	double		x,y,z;

	ifs.open(p);
	if (ifs.is_open() == false) {
		return (M_ERROR(false, "bad file %s", p));
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

void
Scene::drawPts(EnvSDL & env) const
{
	Color	red(255, 0, 0);
	Color	blue(106, 101, 255);
	int	size = this->_pts.size();

	for (auto i = 0; i < size; i++)
		env.drawSquare(this->_pts[i].getX(), this->_pts[i].getY(), 3, red);

	for (auto i = 0; i < size - 1; i++)
		env.drawLine(this->_pts[i].getX(), this->_pts[i].getY(),
			     this->_pts[i + 1].getX(), this->_pts[i + 1].getY(),
			     blue);
}

void
Scene::drawBezier2D(EnvSDL & env)
{
	float						t;
	std::list<Point<double> >			lst;
	std::list<Point<double> >::const_iterator	iterator;
	Color						yellow(255, 255, 0);

	for (unsigned int i = 0; i < this->_b2D.getIter(); i++)
	{
		t = (i + 1.0) / this->_b2D.getIter();
		this->_b2D.casteljau(this->_pts, t);
	}
	lst = this->_b2D.getAprox();
	for (iterator = lst.begin(); iterator != lst.end(); ++iterator)
	{
		Point<double> p = *iterator;
		env.drawSquare(p.getX() - 1, p.getY() - 1, 2, yellow);
	}
}

