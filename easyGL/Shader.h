#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h> //GLEW must always be included before glfw
#include <string>
#include <stdarg.h>
#include <fstream>

class Shader
{
public:
	Shader();
	int initialize(const char* fileName, int shaderType);
	~Shader(void);

	GLuint getHandler();
private:
	GLuint mHandler;
};