#include "stdafx.h"
#include "CWindow.h"

CWindow::CWindow()
{
	m_windowPosX = 100;
	m_windowPosY = 100;

	m_windowWidth = 500;
	m_windowHeight = 500;

	init();
}


CWindow::~CWindow()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	m_pRenderer = NULL;
	m_pWindow = NULL;

	// this is done here because it was init'ed here
	IMG_Quit();
	SDL_Quit();
}


SDL_Window* CWindow::getWindow()
{
	return m_pWindow;
}


SDL_Renderer* CWindow::getRenderer()
{
	return m_pRenderer;
}


int CWindow::getWidth()
{
	return m_windowWidth;
}


int CWindow::getHeight()
{
	return m_windowHeight;
}


void CWindow::updateSize()
{
	SDL_GetWindowSize(m_pWindow, &m_windowWidth, &m_windowHeight);
}


void CWindow::init()
{
	// init sdl
	int sdlInitCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
#ifdef DEBUG
	assert(sdlInitCode >= 0);
#endif // DEBUG

	// Enable VSync
	bool isVSyncOn = SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
#ifdef DEBUG
	assert(isVSyncOn);
#endif // DEBUG


	// set texture filtering to linear
	bool isHintSuccess = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
#ifdef DEBUG
	assert(isHintSuccess);
#endif // DEBUG

	// create window
	m_pWindow = NULL;
	m_pWindow = SDL_CreateWindow("AI fights",
	                             m_windowPosX, m_windowPosY,
	                             m_windowWidth, m_windowHeight,
	                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
#ifdef DEBUG
	assert(m_pWindow != NULL);
#endif // DEBUG

	// create renderer
	m_pRenderer = NULL;
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
#ifdef DEBUG
	assert(m_pRenderer != NULL);
#endif // DEBUG

	//initalize PNG loading
	int imgFlags = IMG_INIT_PNG;
	int imageInitCode = IMG_Init(imgFlags);
#ifdef DEBUG
	assert(imageInitCode & imgFlags);
#endif // DEBUG
}