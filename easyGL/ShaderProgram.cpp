#include "ShaderProgram.h"

GLuint ShaderProgram::sCurrentProgram = 0;

void ShaderProgram::useProgram(ShaderProgram& program){
	sCurrentProgram = program.mHandler;

	glUseProgram(sCurrentProgram);
}

ShaderProgram::ShaderProgram(){

}

GLuint ShaderProgram::getHandler(){
	return mHandler;
}

int ShaderProgram::initialize(Shader** shaders, int count){
	mHandler = glCreateProgram();

	for (int i = 0; i < count; i++)
	{
		glAttachShader(mHandler, shaders[i]->getHandler());
	}

	glLinkProgram(mHandler);

	// check if link was successful
	int params = -1;
	glGetProgramiv(mHandler, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(
			stderr,
			"ERROR: could not link shader programme GL index %u\n",
			mHandler
			);

		int max_length = 2048;
		int actual_length = 0;
		char log[2048];
		glGetProgramInfoLog(mHandler, max_length, &actual_length, log);
		printf("program info log for GL index %u:\n%s", mHandler, log);

		return 1;
	}

	return 0;
}
