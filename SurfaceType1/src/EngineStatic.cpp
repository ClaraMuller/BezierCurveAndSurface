#include <Engine.hpp>

void
Engine::error_callback(int error, const char* description)
{
	std::cerr << "error " << error << ": "
		  << description << std::endl;
}

void
Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
//	std::cerr << __func__ << " keys [" << key << "]";
//	std::cerr << " scancode [" << scancode << "]";
//	std::cerr << " action [" << action << "]";
//	std::cerr << " mods [" << mods << "]" << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void
Engine::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	(void)xpos;
	(void)ypos;
//	std::cerr << __func__ << " ";
//	std::cerr << "xpos [" << xpos << "] ";
//	std::cerr << "ypos [" << ypos << "] ";
//	std::cerr << std::endl;
}

glm::vec3
Engine::pointToVec3(const Point<double> & p)
{
	float x = p.getX();
	float y = p.getY();
	float z = p.getZ();
	return glm::vec3(x, y, z);
}

Point<double>
Engine::vec3ToPoint(const glm::vec3 & v)
{
	return (Point<double>(v.x, v.y, v.z));
}
