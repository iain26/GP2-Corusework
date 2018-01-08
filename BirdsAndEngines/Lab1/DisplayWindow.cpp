#include "DisplayWindow.h"

//constructor initialises window and its size on screen
DisplayWindow::DisplayWindow()
{
	window = nullptr; 
	widthOfScreen = 1024.0f;
	heightOfScreen = 768.0f; 
}

//deconstructor used for clean up  
DisplayWindow::~DisplayWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// displays to user where screen setup has went wrong and quits program
void DisplayWindow::ErrorHandling(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

// swap to other rendered screen
void DisplayWindow::SwapBuff()
{
	SDL_GL_SwapWindow(window);
}

// color of the background to window
void DisplayWindow::ClearDisplay(float red, float green, float blue, float Alpha)
{
	glClearColor(red, green, blue, Alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void DisplayWindow::InitialiseDisplay()
{
	// sets up color and z buffering witn minimun amount of bits 
	// also sets amouint of windows that can be rendered on
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); 
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// returning errors 
	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		(int)widthOfScreen, (int)heightOfScreen, SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		ErrorHandling("window failed to create");
	}

	context = SDL_GL_CreateContext(window);
	if (context == nullptr)
	{
		ErrorHandling("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		ErrorHandling("GLEW failed to initialise");
	}



	// enables z buffering and baackface culling, also sets the clear color of window
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}