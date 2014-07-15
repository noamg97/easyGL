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

Game::~Game(void)
{
	//--unload resources--
}


void Game::Update()
{

}

void Game::Draw()
{

}
