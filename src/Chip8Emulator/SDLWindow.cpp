#include "SDLWindow.h"

#include <iostream>

SDLWindow::SDLWindow(const std::string& title)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        // TODO: Handle error
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << "\n";
        exit(1);
    }

    this->_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void SDLWindow::setTitle(const std::string& title)
{
    SDL_SetWindowTitle(this->_window, title.c_str());
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

void SDLWindow::clear()
{
    SDL_FillRect(this->_screenSurface, NULL, 0x00);
    SDL_UpdateWindowSurface(this->_window);
}