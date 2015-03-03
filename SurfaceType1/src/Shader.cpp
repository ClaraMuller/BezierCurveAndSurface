#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

GLuint
LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
	// Create the shaders
	GLuint	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string		vertexShaderCode;
	std::ifstream	vertexShaderStream(vertex_file_path, std::ios::in);
	
	if (vertexShaderStream.is_open()) {
		std::string line;
		
		while (getline(vertexShaderStream, line))
			vertexShaderCode += "\n" + line;
		vertexShaderStream.close();
	} else {
		std::cerr << "Couldn't open " << vertex_file_path << std::endl;
		return (0);
	}
	
	// Read the Fragment Shader code from the file
	std::string		fragmentShaderCode;
	std::ifstream	fragmentShaderStream(fragment_file_path, std::ios::in);
	
	if (fragmentShaderStream.is_open()) {
		std::string line;
		
		while (getline(fragmentShaderStream, line))
			fragmentShaderCode += "\n" + line;
		fragmentShaderStream.close();
	}

	GLint		result = GL_FALSE;
	int			lenght;
	
	const char	*VertexSourcePointer = vertexShaderCode.c_str();

	// Compile Vertex Shader
	std::cout << "Compiling shader " << vertex_file_path << std::endl;
	glShaderSource(vertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &lenght);
	if (lenght > 0) {
		std::vector<char>	VertexShaderErrorMessage(lenght + 1);
		
		glGetShaderInfoLog(vertexShaderID, lenght, NULL, &VertexShaderErrorMessage[0]);
		std::cout << &VertexShaderErrorMessage[0] << std::endl;
	}

	// Compile Fragment Shader
	std::cout << "Compiling shader : " << fragment_file_path << std::endl;
	char const * FragmentSourcePointer = fragmentShaderCode.c_str();
	
	glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &lenght);
	if (lenght > 0) {
		std::vector<char> FragmentShaderErrorMessage(lenght + 1);
		
		glGetShaderInfoLog(fragmentShaderID, lenght, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the program
	std::cout << "Linking program" << std::endl;
	GLuint ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	// Check the program
	glGetProgramiv(ID, GL_LINK_STATUS, &result);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &lenght);
	if (lenght > 0) {
		std::vector<char> ProgramErrorMessage(lenght + 1);
		
		glGetProgramInfoLog(ID, lenght, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return (ID);
}
