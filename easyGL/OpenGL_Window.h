#pragma once
#include "GLFW_Window.h"
#include "Shader.h"
#include "string"
using namespace std;


class OpenGL_Window : public GLFW_Window
{
public:
	OpenGL_Window(void);
	virtual ~OpenGL_Window(void);

	bool Initialize();
	bool Run() override;

protected:
	//-- variables that may be set by user in the ctor of the "Game" class --

	//glew variables
	//...

	//glfw window variables
	bool isFullscreen;
	string windowName;
	int width, height; //set <=0 for automatic resolution when isFullscreen=true
	int antiAliasing, minOpenGlVersion_Major, minOpenGlVersion_Minor;


	virtual void LoadContent() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
private:
	void LogGlParameters();


	//instead of writing GLFW_Window::LogMessage() every time... maybe use define? or just write the class name...
	void LogMessage(const char* message, ...);
};