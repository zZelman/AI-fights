#pragma once

#include "stdafx.h"
#include "CSprite.h"
#include "CWindow.h"

// * bot is an AI which fights other AI
// * Holds the logic for the AI movements
// * has-a relationship with 'CSprite'
class CBot
{
public:
	CBot(std::string spriteName, CWindow* pWindow);
	~CBot();

	// * allows user to manipulate things
	// * returns true if key is consumed
	bool userInput(SDL_Event* key);
	void update(); // holds passive update information
	void render();

private:
	CWindow* m_pWindow; // window everything happens in
	CSprite* m_pSprite; // holds the entire sprite sheet for this Bot
	std::string m_spriteName; // file name (not path) of the sprite used for this bot

	int m_posX, m_posY; // x & y PIXEL coords on the screen (top left of sprite)
	int m_stepSize; // size of each increment

	bool isUpPressed, isDownPressed;
	bool isLeftPressed, isRightPressed;

	// loads everything (separate from constructor b/c constructor sets data values)
	void init();
};