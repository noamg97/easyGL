#include "Shader.h"

GLuint Shader::shaderProgram = -1;


Shader::Shader(const char* file_name, int shader_type)
{
	std::string shader_text;


	std::ifstream _file(file_name);
	if(!_file.is_open())
	{
		this->shader = 0; // glCreateShader returns 0 if error occurred, so no problem here.
		return;
	}

	std::getline(_file, shader_text, '\0');


	const char* shader_text_ptr = shader_text.c_str();

	this->shader = glCreateShader (shader_type);
	glShaderSource (this->shader, 1, &shader_text_ptr, NULL);
	glCompileShader (this->shader);
}

bool Shader::Errors()
{	
	if(this->shader == 0)
		return 1;

	// check for compile errors
	int params = -1;
	glGetShaderiv (this->shader, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		return 1;
	}

	return 0;
}

Shader::~Shader(void)
{
}

bool Shader::BindShaders(int number, Shader* shaders, ...)
{
	va_list arguments;
	va_start(arguments, shaders);


	Shader::shaderProgram = glCreateProgram();
	for (int i = 0; i < number; i++)
	{
		glAttachShader (Shader::shaderProgram, shaders->shader);
		shaders = va_arg(arguments, Shader*);
	}
	va_end(arguments);


	glLinkProgram(Shader::shaderProgram);


	// check if link was successful
	int params = -1;
	glGetProgramiv (shaderProgram, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (
			stderr,
			"ERROR: could not link shader programme GL index %u\n",
			shaderProgram
			);

		int max_length = 2048;
		int actual_length = 0;
		char log[2048];
		glGetProgramInfoLog (Shader::shaderProgram, max_length, &actual_length, log);
		printf ("program info log for GL index %u:\n%s", Shader::shaderProgram, log);

		return 1;
	}

	glUseProgram (shaderProgram);
	return 0;
}