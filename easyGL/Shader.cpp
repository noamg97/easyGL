#include "Shader.h"

Shader::Shader()
{
	
}

int Shader::initialize(const char* fileName, int shaderType){
	std::string shader_text;

	std::ifstream _file(fileName);
	if (!_file.is_open())
	{
		mHandler = 0; // glCreateShader returns 0 if error occurred, so no problem here.
		return 1;
	}

	std::getline(_file, shader_text, '\0');


	const char* shader_text_ptr = shader_text.c_str();

	mHandler = glCreateShader(shaderType);
	glShaderSource(mHandler, 1, &shader_text_ptr, NULL);
	glCompileShader(mHandler);


	if (mHandler == 0)
		return 2;

	// check for compile errors
	int params = -1;
	glGetShaderiv(mHandler, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		return 3;
	}

	return 0;
}

Shader::~Shader(void)
{
}

GLuint Shader::getHandler(){
	return mHandler;
}