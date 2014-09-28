#include "Game.h"


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
	this->vertexShader = new Shader("test_vs.glsl", GL_VERTEX_SHADER);
	this->fragmentShader = new Shader("test_fs.glsl", GL_FRAGMENT_SHADER);
	Shader::BindShaders(2, vertexShader, fragmentShader);

}

void Game::Update()
{

}

void Game::Draw()
{

}

Game::~Game(void)
{
	//--unload resources--
}
