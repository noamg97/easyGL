#pragma once
#include "OpenGL_Window.h"
#include "ShaderProgram.h"

class Game : public OpenGL_Window
{
public:
	Game(void);
	~Game(void);

	void LoadContent() override;
	void Update() override;
	void Draw() override;

private:
	Shader* mVertexShader, *mFragmentShader;
	ShaderProgram* mDefaultProgram;
};

