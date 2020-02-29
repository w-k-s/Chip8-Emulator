#pragma once

#include <string>
#include <cstdint>
#include <array>

#define SCALE 10
#define DP(px) px * 10

const int SCREEN_WIDTH = DP(64);
const int SCREEN_HEIGHT = DP(32);
const int WINDOW_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

using Canvas = std::array<uint8_t,WINDOW_SIZE>;

class Window{
public:
	virtual void setTitle(const std::string& title) = 0;
	virtual void clear() = 0;
	virtual void redraw() = 0;
	virtual void setNeedsRedraw() = 0;
	virtual Canvas& canvas() = 0;
	virtual void publishCanvasToSurface() = 0;
	virtual ~Window(){};
};