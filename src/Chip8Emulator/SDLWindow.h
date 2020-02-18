#pragma once

#include <SDL2/SDL.h>
#include "Window.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

class SDLWindow : public Window{
private:
	SDL_Window* _window;
	SDL_Surface* _screenSurface;

	void eventLoop();
public:
	SDLWindow(const std::string& title);
	SDLWindow(const SDLWindow&)			= delete;
	void operator=(const SDLWindow&)	= delete;

	void setTitle(const std::string& title);
	void clear();
	~SDLWindow();
};