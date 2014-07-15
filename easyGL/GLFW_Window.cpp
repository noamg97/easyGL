#include "GLFW_Window.h"

GLFW_Window* GLFW_Window::instance;


bool GLFW_Window::Initialize( const char* name, bool full_screen, int width, int height, int opengl_version_major, int opengl_version_minor, int anti_aliasing )
{
	GLFW_Window::instance = this;

	GLFWmonitor* mon = NULL;
	if(full_screen)
	{
		mon = glfwGetPrimaryMonitor ();
		const GLFWvidmode* vmode = glfwGetVideoMode (mon);

		this->width = vmode->width;
		this->height = vmode->height;
	}
	else
	{
		if(!(width && height))
		{
			LogMessage ("ERROR: window width or height are 0 when full_screen is false");
			return 1;
		}
		this->width = width;
		this->height = height;
	}


	assert(GLFW_Window::RestartLog());
	LogMessage ("starting GLFW\n%s\n", glfwGetVersionString ());

	glfwSetErrorCallback (GLFW_Window::GLFWErrorCallback);

	if (!glfwInit ()) {
		LogMessage ("ERROR: could not start GLFW3");
		return 1;
	}


	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, opengl_version_major);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, opengl_version_minor);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwWindowHint (GLFW_SAMPLES, anti_aliasing);


	this->handle = glfwCreateWindow (this->width, this->height, name, mon, NULL);


	glfwMakeContextCurrent (this->handle);
	glfwSetWindowSizeCallback (this->handle, GLFW_Window::GLFWWindowSizeCallback);


	return 0;
}


void GLFW_Window::DoPollEvents()
{
	glfwPollEvents();
}
void GLFW_Window::SwapBuffers()
{
	glfwSwapBuffers (this->handle);
}
bool GLFW_Window::ShouldExit(bool esc_to_exit)
{
	return 
		glfwWindowShouldClose(this->handle) || 
		(esc_to_exit && this->KeyPressed(GLFW_KEY_ESCAPE));
}
bool GLFW_Window::KeyPressed( int key )
{
	return GLFW_PRESS == glfwGetKey (this->handle, key);
}
void GLFW_Window::CloseWindow()
{
	glfwTerminate();
}


void GLFW_Window::GLFWWindowSizeCallback( int width, int height )
{
	this->width = width;
	this->height = height;
}










void GLFW_Window::GLFWErrorCallback ( int error, const char* description ) {
	GLFW_Window::LogMessage ("GLFW ERROR: code %i msg: %s\n", error, description);
}
void GLFW_Window::GLFWWindowSizeCallback( GLFWwindow* window, int width, int height )
{
	GLFW_Window::instance->GLFWWindowSizeCallback(width, height);
}

// -- Log Functions -- //
bool GLFW_Window::RestartLog()
{
	FILE* file = fopen (GL_LOG_FILE, "w");
	if (!file) {
		fprintf (
			stderr,
			"ERROR: could not open GL_LOG_FILE log file %s for writing\n",
			GL_LOG_FILE
			);
		return false;
	}
	time_t now = time (NULL);
	char* date = ctime (&now);
	fprintf (file, "GL_LOG_FILE log. local time %s\n", date);
	fclose (file);
	return true;
}
bool GLFW_Window::LogMessage( const char* message, ... )
{
	va_list argptr;
	va_start (argptr, message);
	bool end_code = GLFW_Window::LogMessage(message, argptr);
	va_end (argptr);

	return end_code;
}

bool GLFW_Window::LogMessage( const char* message, va_list argptr )
{
	FILE* file = fopen (GL_LOG_FILE, "a");
	if (!file) {
		fprintf (
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending\n",
			GL_LOG_FILE
			);
		return 1;
	}
	vfprintf (file, message, argptr);
	fclose (file);
	return 0;
}
