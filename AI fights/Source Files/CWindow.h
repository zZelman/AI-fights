#pragma once

#include "stdafx.h"

class CWindow
{
public:
	CWindow();
	~CWindow();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int windowPosX, windowPosY; // top left of window position from top left of screen
	int windowWidth, windowHeight;

	void init();
};
