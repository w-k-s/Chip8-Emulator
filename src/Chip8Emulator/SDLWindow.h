#pragma once

#include <SDL2/SDL.h>
#include "Window.h"

class SDLWindow : public Window{
private:
	SDL_Window* _window;
	SDL_Surface* _screenSurface;

	Canvas _canvas;

	bool _requiresRedraw;

	void eventLoop();
public:
	SDLWindow(const std::string& title);
	SDLWindow(const SDLWindow&)			= delete;
	void operator=(const SDLWindow&)	= delete;

	void setTitle(const std::string& title);
	void clear();

	void redraw();
	void setNeedsRedraw();

	Canvas& canvas();
	void publishCanvasToSurface();

	~SDLWindow();
};