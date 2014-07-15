#include "OpenGL_Window.h"


OpenGL_Window::OpenGL_Window(void)
	: GLFW_Window()
{
	//init variables to default
	this->isFullscreen = false;
	this->windowName = "OpenGL App";
	this->minOpenGlVersion_Major = 4;
	this->minOpenGlVersion_Minor = 0;
	this->width = 800;
	this->height = 640;
	this->antiAliasing = 4;
}

OpenGL_Window::~OpenGL_Window(void)
{

}




bool OpenGL_Window::Initialize()
{
	if(GLFW_Window::Initialize(
		this->windowName.c_str(),
		this->isFullscreen,
		this->width, this->height,
		this->minOpenGlVersion_Major, 
		this->minOpenGlVersion_Minor, 
		this->antiAliasing))
	{
		LogMessage("Error: error initializing GLFW window");
		return 1;
	}


	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
		LogMessage("Error: %s\n", glewGetErrorString(err));

	LogGlParameters();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); //enable depth-testing
	glDepthFunc (GL_LESS); //depth-testing interprets a smaller value as "closer"
	
	//CornFlowerBlue FTW!
	glClearColor(100/225.0f, 149/225.0f, 237/225.0f, 1);





	return 0;
}

bool OpenGL_Window::Run()
{
	while(!GLFW_Window::ShouldExit(true))
	{
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		this->Update();
		this->Draw();


		GLFW_Window::DoPollEvents();
		GLFW_Window::SwapBuffers();
	}


	GLFW_Window::CloseWindow();
	return 0;
}





void OpenGL_Window::LogGlParameters () {
	LogMessage ("Renderer: %s\n", glGetString (GL_RENDERER));
	LogMessage ("OpenGL version supported %s\n", glGetString (GL_VERSION));


	GLenum params[] = {
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO,
	};
	const char* names[] = {
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};
	LogMessage ("\nGL Context Params:\n");
	char msg[256];
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		LogMessage ("%s %i\n", names[i], v);
	}
	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv (params[10], v);
	LogMessage ("%s %i %i\n", names[10], v[0], v[1]);
	unsigned char s = 0;
	glGetBooleanv (params[11], &s);
	LogMessage ("%s %u\n", names[11], (unsigned int)s);
	LogMessage ("-----------------------------\n");
}

void OpenGL_Window::LogMessage( const char* message, ... )
{
	va_list argptr;
	va_start (argptr, message);
	GLFW_Window::LogMessage(message, argptr);
	va_end (argptr);
}