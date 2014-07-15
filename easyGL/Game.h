#pragma once
#include "OpenGL_Window.h"

class Game : public OpenGL_Window
{
public:
	Game(void);
	~Game(void);

	void Update() override;
	void Draw() override;
};

