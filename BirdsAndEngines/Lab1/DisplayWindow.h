#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class DisplayWindow
{
public:
	DisplayWindow();
	~DisplayWindow();
	void InitialiseDisplay();
	void SwapBuff();
	void ClearDisplay(float r, float g, float b, float a);

	float GetWidth() { return widthOfScreen; };
	float GetHeight() { return heightOfScreen; };

private:

	void ErrorHandling(std::string errorMessage);
	
	SDL_GLContext context; 
	SDL_Window* window; 
	float widthOfScreen;
	float heightOfScreen;
};

