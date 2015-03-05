#include <Engine.hpp>
#include <Scene.hpp>

#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cstdlib>


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

Engine::Engine(void):
	_win(0),
	_camX(15), _camY(-25), _camZ(0),
	_lastX(0), _lastY(0), _dist(-SIZE_MAP - 150)
{
	std::cout << "Construct Engine" << std::endl;
	this->_fov = 45.0f;
}

Engine::Engine(const Engine& o)
{
	*this = o;
}

Engine&
Engine::operator=(const Engine& o)
{
	(void)o;
	return (*this);
}

Engine::~Engine(void)
{
	if (this->_win != 0)
	{
		std::cout << "Destroy Window and Context" << std::endl;;
		glfwDestroyWindow(this->_win);
		glfwTerminate();
	}
	std::cout << "Destruct Engine" << std::endl;
}

bool
Engine::init(int mode, int w, int h)
{
	this->_w = w;
	this->_h = h;
	this->_drawingMode = mode;
	glfwSetErrorCallback(Engine::error_callback);
	if (glfwInit() != GL_TRUE)
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->_win = glfwCreateWindow(w, h, "My OpenGL Window", NULL, NULL);
	if (!this->_win)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(this->_win);

	glewExperimental=true;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwDestroyWindow(this->_win);
		glfwTerminate();
		return false;
	}

	glfwSetKeyCallback(this->_win, Engine::key_callback);
	glfwSetCursorPosCallback(this->_win, cursor_pos_callback);
	return true;
}

void
Engine::launch(Scene & sc)
{
	runThroughSquare(sc._pts);
	setBorderMap();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,
			this->_vertice.size() * sizeof(glm::vec3),
			&this->_vertice[0],
			GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER,
			this->_colors.size() * sizeof(glm::vec3),
			&this->_colors[0],
			GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "mapVertex", "mapFragment" );
	while (glfwWindowShouldClose(_win) == false)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE OR G_FILL
		manageDrawing(programID, vertexbuffer, colorbuffer, this->_vertice.size());
		updateCam();
		manageCam(programID);

		glfwSwapBuffers(this->_win);
		glfwPollEvents();
	}
}

void
Engine::manageDrawing(GLuint programID,
					  GLuint vertexbuffer,
					  GLuint colorbuffer,
					  GLsizei nbVertices)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	// No particular reason for 1, but must match the layout in the shader.
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// DRAWING TRIANLES
	glDrawArrays(GL_TRIANGLES, 0,  nbVertices);
	glDisableVertexAttribArray(0);
}

void
Engine::manageCam(GLuint programID)
{
	int	spawn = SIZE_MAP / 2;

	glm::mat4 Projection = glm::perspective(this->_fov,
						16.0f / 9.0f,
//						this->_w / this->_h * 1.0f,
						0.1f, 10000.0f);

	glm::mat4 Model;
	Model = glm::rotate(Model, this->_camX / 16, glm::vec3(1, 0, 0));
	Model = glm::rotate(Model, this->_camY / 16, glm::vec3(0, 1, 0));
	Model = glm::rotate(Model, this->_camZ / 16, glm::vec3(0, 0, 1));

	glm::mat4 View;
	View = glm::translate(View, glm::vec3(spawn, spawn, this->_dist));

	glm::mat4 MVP   = Projection * View * Model;

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

void
Engine::updateCam(void)
{
	double	xpos, ypos;
	float	dx, dy;
	int		state;

	if (glfwGetKey( this->_win, GLFW_KEY_UP ) == GLFW_PRESS)
		this->_dist += PAS;

	if (glfwGetKey( this->_win, GLFW_KEY_DOWN ) == GLFW_PRESS)
		this->_dist -= PAS;

	state = glfwGetMouseButton(this->_win, GLFW_MOUSE_BUTTON_RIGHT);
	glfwGetCursorPos(this->_win, &xpos, &ypos);
	if (state == GLFW_PRESS)
	{
		dx = xpos - this->_lastX;
		dy = ypos - this->_lastY;
		this->rotateBy(dy,  0, 0);
		this->rotateBy( 0, dx, 0);
//		std::cout << "xcam" << this->_camX << std::endl;
//		std::cout << "ycam" << this->_camY << std::endl;
//		std::cout << "zcam" << this->_camZ << std::endl;
	}
	this->_lastX = xpos;
	this->_lastY = ypos;
}


