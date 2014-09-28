#pragma once
#include <GL/glew.h> //GLEW must always be included before glfw
#include <string>
#include <stdarg.h>
#include <fstream>

class Shader
{
public:
	GLuint shader;


	Shader(const char* file_name, int shader_type);
	bool Errors();
	~Shader(void);


	static bool BindShaders(int number, Shader* shaders, ...);

private:
	static GLuint shaderProgram;
};