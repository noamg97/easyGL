#pragma once
#include "OpenGL_Window.h"

class Game : public OpenGL_Window
{
public:
	Game(void);
	~Game(void);

	void LoadContent() override;
	void Update() override;
	void Draw() override;

private:
	Shader* vertexShader, *fragmentShader;
};

