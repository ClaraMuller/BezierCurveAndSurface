#include <Engine.hpp>
#include <Scene.hpp>

#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cstdlib>

void
Engine::runThroughSquare(std::vector<Point<double> > & pts)
{
	int	iter = this->_b2D.getIter();
	int	nb = pts.size();

	std::cout << "Run Through Square" << std::endl;
	std::cout << "nb points : " << nb << std::endl;
	for (int x = 0; x < SIZE_MAP; x = x + iter)
	{
		for (int z = 0; z < SIZE_MAP; z = z + iter)
		{
			std::cout << "x: " << x << " - z:" << z << std::endl;
			std::vector<Point<double>>	lst;

			for (int i = 0; i < nb; ++i)
			{
				int	px = pts[i].getX();
				// Oui c'est pas les meme c'est normal
				int	pz = pts[i].getY();

				if (x <= px && px < x + iter && z <= pz && pz < z + iter)
				{
					std::cout << "Found: " << pts[i] << std::endl;
					lst.push_back(Point<double>(px, pts[i].getZ(), pz));
				}
			}
			if (lst.size() != 0)
			{
				setControlPoints(lst, x, z);
				drawBezier2D();
				this->_testPoints.clear();
				this->_testPoints2.clear();
				this->_testPoints3.clear();
				this->_map.clear();
				this->_b2D.clearAprox();
			}
			else
			{
				drawSquarePlan(x, z, iter);
			}
		}
	}
}

void
Engine::setControlPoints(std::vector<Point<double> > & ctrl, int mx, int mz)
{
	std::cout << "Setting Control Point" << std::endl;

	int	size;
	int	iter = this->_b2D.getIter();

	this->_testPoints.push_back(Point<double>( mx + iter, 0,            mz));
	this->_testPoints.push_back(Point<double>( mx + iter, 0, mz + iter / 2));
	this->_testPoints.push_back(Point<double>( mx + iter, 0,     mz + iter));

	/* ZE POINT(S) */

	size = ctrl.size();

	for (int i = 0; i < size; ++i)
	{
		double	x = ctrl[i].getX();
		double	y = ctrl[i].getY();
		double	z = ctrl[i].getZ();

		if (this->_drawingMode == SIMPLE)
		{
			this->_testPoints2.push_back(Point<double>( x, 0,        mz));
			this->_testPoints2.push_back(Point<double>( x, 0,   z - LIM));

			this->_testPoints2.push_back(Point<double>( x, y,         z));

			this->_testPoints2.push_back(Point<double>( x, 0,   z + LIM));
			this->_testPoints2.push_back(Point<double>( x, 0, mz + iter));
		}
		if (this->_drawingMode == MULTI)
		{
			std::vector< Point<double> >	lst;
			lst.push_back(Point<double>( x, 0,        mz));
			lst.push_back(Point<double>( x, 0,   z - LIM));

			lst.push_back(Point<double>( x, y,         z));

			lst.push_back(Point<double>( x, 0,   z + LIM));
			lst.push_back(Point<double>( x, 0, mz + iter));
			this->_map.push_back(lst);
		}

	}

	/***/

	this->_testPoints3.push_back(Point<double>( mx, 0,            mz));
	this->_testPoints3.push_back(Point<double>( mx, 0, mz + iter / 2));
	this->_testPoints3.push_back(Point<double>( mx, 0,     mz + iter));

	this->drawControlPoints();
}

void
Engine::drawBezier2D(void)
{
	int						size;
	std::vector<Point<double> >			tab;
	std::vector<Point<double> >			tab2;
	std::vector<Point<double> >			tab3;
	std::vector<std::vector<Point<double>> >	grid;

	std::cout << "Drawing Bezier" << std::endl;

	// COURBE 1

	this->_b2D.compute(_testPoints);
	tab = this->_b2D.getAprox();
	size = tab.size();
	for (int i = 0; i < size; i++)
		drawPoint(tab[i], 1, 0, 0);

	// COURBE 2

	if (this->_drawingMode == SIMPLE)
	{
		this->_b2D.clearAprox();
		this->_b2D.compute(_testPoints2);
		tab2 = this->_b2D.getAprox();
		size = tab2.size();
		for (int i = 0; i < size; i++)
			drawPoint(tab2[i], 1, 0, 0);
	}

	if (this->_drawingMode == MULTI)
	{
		size = this->_map.size();
		std::cout << "map size : " << size << std::endl;
		for (int i = 0; i < size; ++i)
		{
			std::vector<Point<double> >	t;
			int				s;

			this->_b2D.clearAprox();
			this->_b2D.compute(this->_map[i]);
			t = this->_b2D.getAprox();
			s = t.size();
			for (int i = 0; i < s; i++)
				drawPoint(t[i], 1, 0, 0);
			grid.push_back(t);
		}
	}

	// COURBE 3

	this->_b2D.clearAprox();
	this->_b2D.compute(_testPoints3);
	tab3 = this->_b2D.getAprox();
	size = tab3.size();
	for (int i = 0; i < size; i++)
		drawPoint(tab3[i], 1, 0, 0);

	// DRAWING

	int	iter     = this->_b2D.getIter();
	int	tab_size = tab.size();
	int	grid_size = grid.size();
	std::cout << "iter : " << iter     << std::endl;
	std::cout << "tab  : " << tab_size << std::endl;
	std::cout << "grid : " << grid_size << std::endl;

	std::vector<glm::vec3>		tmp;
	std::vector<Point<double> >	temp;

	for (int i = 0; i < tab_size; ++i)
	{
		temp.clear();
		this->_b2D.clearAprox();
		temp.push_back(tab[i]);

		if (this->_drawingMode == SIMPLE)
			temp.push_back(tab2[i]);

		if (this->_drawingMode == MULTI)
		{
			for (int k = 0; k < grid_size; ++k)
				temp.push_back(grid[k][i]);
		}

		temp.push_back(tab3[i]);
		this->_b2D.compute(temp);
		std::vector<Point<double> > res = this->_b2D.getAprox();
		for (int j = 0; j < tab_size; ++j) // iter = tab_size - 1
		{
			//drawPoint(res[j], 0, 1, 1);
			tmp.push_back(Engine::pointToVec3(res[j]));
		}
	}
	drawLand(tmp, tab_size);
}

void
Engine::setBorderMap(void)
{
	std::vector<glm::vec3>	tmp;

	std::cout << "Drawing Border" << std::endl;
	drawRectanglePlan(   -BORD,    -BORD,            BORD, SIZE_MAP + BORD);
	drawRectanglePlan(SIZE_MAP,        0,            BORD, SIZE_MAP + BORD);
	drawRectanglePlan(       0,    -BORD, SIZE_MAP + BORD, BORD);
	drawRectanglePlan(   -BORD, SIZE_MAP, SIZE_MAP + BORD, BORD);
}

void
Engine::drawRectanglePlan(int x, int z, int h, int w)
{
	this->_vertice.push_back(glm::vec3(    x, 0,     z));
	this->_vertice.push_back(glm::vec3(x + h, 0,     z));
	this->_vertice.push_back(glm::vec3(    x, 0, z + w));

	this->_vertice.push_back(glm::vec3(x + h, 0,     z));
	this->_vertice.push_back(glm::vec3(x + h, 0, z + w));
	this->_vertice.push_back(glm::vec3(    x, 0, z + w));

	for (int j = 0 ; j < 6; ++j)
		this->_colors.push_back(glm::vec3(0, 0.392157, 0));
}


void
Engine::drawSquarePlan(int x, int z, int size)
{
	this->_vertice.push_back(glm::vec3(       x, 0,        z));
	this->_vertice.push_back(glm::vec3(x + size, 0,        z));
	this->_vertice.push_back(glm::vec3(x       , 0, z + size));

	this->_vertice.push_back(glm::vec3(x + size, 0,        z));
	this->_vertice.push_back(glm::vec3(x + size, 0, z + size));
	this->_vertice.push_back(glm::vec3(x       , 0, z + size));

	for (int j = 0 ; j < 6; ++j)
		this->_colors.push_back(glm::vec3(0, 0.392157, 0));
}

void
Engine::drawLand(std::vector<glm::vec3> & tmp, int square, float r, float g, float b)
{
	drawLand(tmp, square, square, r, g, b);
}

void
Engine::drawLand(std::vector<glm::vec3> & tmp, int sqZ, int sqX, float r, float g, float b)
{
	int		size = tmp.size();

	if (size < 1)
		return;
	for (int z = 0 ; z < sqZ - 1; ++z)
	{
		for (int x = 0; x < sqX - 1; ++x)
		{
			int i = z * sqX + x;
			this->_vertice.push_back(tmp[i]);
			this->_vertice.push_back(tmp[i + sqX]);
			this->_vertice.push_back(tmp[i + 1]);
			this->_vertice.push_back(tmp[i + 1]);
			this->_vertice.push_back(tmp[i + sqX]);
			this->_vertice.push_back(tmp[i + 1 + sqX]);

			for (int j = 0 ; j < 6; ++j)
				this->_colors.push_back(glm::vec3(r, g ,b));
		}
	}
}

void
Engine::drawLand(std::vector<glm::vec3> & tmp, int square)
{
	int		size = tmp.size();
	int		iter = this->_b2D.getIter();
	float	yMax = 0;

	if (size < 1)
		return;
	for (int i = 0; i < size; ++i)
	{
		if (tmp[i].y > yMax)
			yMax = tmp[i].y;
	}
	std::cout << "yMax: " << yMax << std::endl;
	for (int z = 0 ; z < square - 1; ++z)
	{
		for (int x = 0; x < square - 1; ++x)
		{
			int i = z * square + x;
			this->_vertice.push_back(tmp[i]);
			this->_vertice.push_back(tmp[i + square]);
			this->_vertice.push_back(tmp[i + 1]);
			this->_vertice.push_back(tmp[i + 1]);
			this->_vertice.push_back(tmp[i + square]);
			this->_vertice.push_back(tmp[i + 1 + square]);

			this->setCorrectColor(yMax, tmp[i].y,              iter);
			this->setCorrectColor(yMax, tmp[i + square].y,     iter);
			this->setCorrectColor(yMax, tmp[i + 1].y,          iter);
			this->setCorrectColor(yMax, tmp[i + 1].y,          iter);
			this->setCorrectColor(yMax, tmp[i + square].y,     iter);
			this->setCorrectColor(yMax, tmp[i + 1 + square].y, iter);
		}
	}
}


