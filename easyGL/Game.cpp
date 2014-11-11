#include "Game.h"

const GLfloat vertexBuffer[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

GLuint vbo;
GLuint vao;

Game::Game(void) : OpenGL_Window()
{	
	this->isFullscreen = false;
	this->windowName = "Hello World!";
	this->minOpenGlVersion_Major = 4;
	this->minOpenGlVersion_Minor = 0;
	this->width = 800;
	this->height = 640;
	this->antiAliasing = 4;
}

void Game::LoadContent()
{
	mVertexShader = new Shader();
	if (mVertexShader->initialize("test_vs.glsl", GL_VERTEX_SHADER)){
		return;
	}
	mFragmentShader = new Shader();
	if (mFragmentShader->initialize("test_fs.glsl", GL_FRAGMENT_SHADER)){
		return;
	}
	mDefaultProgram = new ShaderProgram();
	Shader* shaders[2] = { mVertexShader, mFragmentShader };
	if (mDefaultProgram->initialize(shaders, sizeof(shaders)/sizeof(Shader*))){
		return;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
}

void Game::Update()
{

}

void Game::Draw()
{
	ShaderProgram::useProgram(*mDefaultProgram);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

Game::~Game(void)
{
	//--unload resources--
}
