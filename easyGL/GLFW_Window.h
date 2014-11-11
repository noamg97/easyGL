#pragma once
#define GLEW_STATIC
#include <GL/glew.h> //GLEW must always be included before glfw
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <assert.h>


#define GL_LOG_FILE "gl.txt"


class GLFW_Window
{
public:
	//so the static callback functions could call the member functions
	static GLFW_Window* instance;
	//window handle
	GLFWwindow* handle;

	bool Initialize(const char* name, bool full_screen=true, int width=0, int height=0, int opengl_version_major=4, int opengl_version_minor=0, int anti_aliasing=4);




	//let glfw handle os messages and stuff
	void DoPollEvents();
	//swaps display buffers
	void SwapBuffers();
	//returns whether or not there is a close window message
	bool ShouldExit(bool esc_to_exit=false);
	//returns whether or not a GLFW_KEY_[keyname] is pressed
	bool KeyPressed(int key);
	//terminates glfw and releases sources.
	void CloseWindow();



	virtual bool Run() = 0;
	virtual void GLFWWindowSizeCallback (int width, int height);


	// -- Log Functions -- //
	static bool RestartLog();
	static bool LogMessage (const char* message, ...);
	static bool LogMessage( const char* message, va_list argptr );
protected:
	//window size
	int width, height;

private:
	static void GLFWErrorCallback(int error, const char* description);
	static void GLFWWindowSizeCallback (GLFWwindow* window, int width, int height);
};