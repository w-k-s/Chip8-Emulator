#pragma once

#include <string>

class Window{
public:
	virtual void setTitle(const std::string& title) = 0;
	virtual void clear() = 0;
	virtual ~Window(){};
};