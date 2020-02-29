#include "SDLWindow.h"

#include <iostream>

SDLWindow::SDLWindow(const std::string& title)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        // TODO: Handle error
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << "\n";
        exit(1);
    }

    this->_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (this->_window == NULL) {
        // TODO: Handle error
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    this->_screenSurface = SDL_GetWindowSurface(this->_window);

    this->clear();
    this->eventLoop();
}

SDLWindow::~SDLWindow()
{
    SDL_DestroyWindow(this->_window);
    SDL_Quit();
}

void SDLWindow::setNeedsRedraw()
{
    this->_requiresRedraw = true;
}

void SDLWindow::setTitle(const std::string& title)
{
    SDL_SetWindowTitle(this->_window, title.c_str());
    this->setNeedsRedraw();
}

void SDLWindow::eventLoop()
{
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}

Canvas& SDLWindow::canvas()
{
    return this->_canvas;
}

void SDLWindow::clear()
{
    this->_canvas.fill(0);
    SDL_FillRect(this->_screenSurface, NULL, 0x00);
    this->setNeedsRedraw();
}

void SDLWindow::publishCanvasToSurface()
{
    for (uint16_t i = 0; i < WINDOW_SIZE; ++i)
    {
        SDL_Rect rect;
        rect.x = DP(this->_canvas[i]) % SCREEN_WIDTH;
        rect.y = DP(this->_canvas[i]) / SCREEN_HEIGHT;
        rect.w = DP(1);
        rect.h = DP(1);
        SDL_FillRect(this->_screenSurface, &rect, 0x00ff00);

    }
    this->setNeedsRedraw();
}

void SDLWindow::redraw()
{
    if (this->_requiresRedraw) {
        SDL_UpdateWindowSurface(this->_window);
    }
}