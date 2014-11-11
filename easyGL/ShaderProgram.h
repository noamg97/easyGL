#include "GL\glew.h"
#include "Shader.h"

class ShaderProgram{
public:
	static void useProgram(ShaderProgram& program);

	ShaderProgram();
	int initialize(Shader** shaders, int count);

	GLuint getHandler();
private:
	static GLuint sCurrentProgram;
	GLuint mHandler;
};