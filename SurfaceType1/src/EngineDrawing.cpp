#include <Engine.hpp>

#include <OpenGL/gl.h>
#include <glm/glm.hpp>

#define SIZE_POINT 0.5

void
Engine::drawControlPoints(void)
{
	std::cout << "Drawing Control Point" << std::endl;
	int		size;

	size = this->_testPoints.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << "- " << this->_testPoints[i];
		std::cout << std::endl;
		drawPoint(this->_testPoints[i], 1, 0, 1);
	}

	if (this->_drawingMode == SIMPLE)
	{
		size = this->_testPoints2.size();
		for (int i = 0; i < size; i++)
		{
			std::cout << "- " << this->_testPoints2[i];
			std::cout << std::endl;
			drawPoint(this->_testPoints2[i], 1, 1, 0);
		}
	}

	if (this->_drawingMode == MULTI)
	{
		size = this->_map.size();
		for (int i = 0; i < size; ++i)
		{
			int s = this->_map[i].size();
			for (int j = 0; j < s; ++j)
			{
			std::cout << "- " << this->_map[i][j];
			std::cout << std::endl;
			drawPoint(this->_map[i][j], 1, 1, 0);
			}
		}
	}

	size = this->_testPoints3.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << "- " << this->_testPoints3[i];
		std::cout << std::endl;
		drawPoint(this->_testPoints3[i], 0.564706, 0.933333, 0.564706);
	}
}

void
Engine::setCorrectColor(float zMax, float z, int iter)
{
	glm::vec3 c;

	if (z >= zMax - iter / 20.0 && zMax > 0)
		c = glm::vec3(0.839216, 0.839216, 0.839216);

	else if (z < 2 && z > -2)
		c = glm::vec3(0, 0.392157, 0);

	else if (z <= -2)
		c = glm::vec3(0.333333, 0.333333, 0.333333);

	else
		c = glm::vec3(0.545098, 0.270588, 0.0745098);

	this->_colors.push_back(c);
}

void
Engine::drawPoint(const Point<double> & p, float r, float g, float b)
{
	float x = p.getX();
	float y = p.getY();
	float z = p.getZ();
	drawPoint(x, y, z, r, g, b);
}

void
Engine::drawPoint(const glm::vec3 & v, float r, float g, float b)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	drawPoint(x, y, z, r, g, b);
}

void
Engine::drawPoint(float x, float y, float z, float r, float g, float b)
{
	glm::vec3 O = glm::vec3(x, y, z);

	glm::vec3 A = glm::vec3(x - SIZE_POINT, y - SIZE_POINT,              z);
	glm::vec3 B = glm::vec3(x + SIZE_POINT, y - SIZE_POINT,              z);
	glm::vec3 C = glm::vec3(             x, y - SIZE_POINT, z - SIZE_POINT);

	this->_vertice.push_back(O);
	this->_vertice.push_back(A);
	this->_vertice.push_back(B);

	this->_vertice.push_back(O);
	this->_vertice.push_back(A);
	this->_vertice.push_back(C);

	this->_vertice.push_back(O);
	this->_vertice.push_back(B);
	this->_vertice.push_back(C);

	this->_vertice.push_back(A);
	this->_vertice.push_back(B);
	this->_vertice.push_back(C);

	for (int i = 0; i < 12; i++)
		this->_colors.push_back(glm::vec3(r, g, b));
}

void
Engine::animatedTriangle(void)
{
	float ratio;
	int width, height;

	glfwGetFramebufferSize(_win, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}
