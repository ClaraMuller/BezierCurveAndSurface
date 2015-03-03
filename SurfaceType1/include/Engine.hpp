#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <OpenGL/gl.h>
# include <glm/glm.hpp>
# include <vector>

# include <Point.hpp>
# include <Bezier2D.hpp>

class Scene;

class	Engine
{
private:
	GLFWwindow	*_win;
	size_t		_w;
	size_t		_h;

	float	_camX;
	float	_camY;
	float	_camZ;
	float	_lastX;
	float	_lastY;
	float	_dist;

	float		_fov;
	Bezier2D	_b2D;
	int		_drawingMode;

	std::vector<glm::vec3>		_vertice;
	std::vector<glm::vec3>		_colors;
	std::vector<glm::vec3>		_water;

	std::vector<Point<double>>	_testPoints;
	std::vector<Point<double>>	_testPoints2;
	std::vector<Point<double>>	_testPoints3;

	std::vector< std::vector< Point<double> > >	_map;

	Engine(const Engine& o);
	Engine&	operator=(const Engine& o);

	/* EngineDrawing.cpp  */

	void	animatedTriangle(void); // OK

	/* Engine.cpp  */

	void	manageDrawing(GLuint pID, GLuint vertex, GLuint color, GLsizei nbV);
	void	manageCam(GLuint pID);
	void	updateCam(void);

public:

	enum
	{
		MULTI = 0,
		SIMPLE = 1,
		BORD = 20,
		LIM = 10,
	};

	/* Engine.cpp  */

	Engine(void);
	virtual ~Engine(void);

	bool	init(int w = 1900, int h = 1200, int mode = SIMPLE);
	void	launch(Scene & sc);

	/* EngineMap.cpp */

	void	drawBezier2D(void);
	void	setControlPoints(std::vector<Point<double> > & p);
	void	setBorderMap(void);
	void	drawLand(std::vector<glm::vec3> & pts, int square);
	void	drawLand(std::vector<glm::vec3> & pts, int square, float r, float g, float b);
	void	drawLand(std::vector<glm::vec3> & pts, int sqZ, int sqX, float r, float g, float b);

	/* EngineGetterSetter.cpp  */

	int	getCamX(void) const;
	int	getCamY(void) const;
	int	getCamZ(void) const;
	void	setCamX(int param);
	void	setCamY(int param);
	void	setCamZ(int param);
	void	rotateBy(float x, float y, float z);

	/* EngineDrawing.cpp  */

	void	drawControlPoints(void);
	void	setCorrectColor(float mazZ, float z, int iter);
	void	drawPoint(float x, float y, float z, float r, float g, float b);
	void	drawPoint(const glm::vec3 & v, float r, float g, float b);
	void	drawPoint(const Point<double> & p, float r, float g, float b);

	/* EngineStatic.cpp  */

	static void		error_callback(int error, const char* description);
	static void		key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void		cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static glm::vec3	pointToVec3(const Point<double> & p);
	static Point<double>	vec3ToPoint(const glm::vec3 & v);

};

#endif
