#pragma once

#include "stdafx.h"

#include "CSprite.h"
#include "CWindow.h"
#include "CBot.h"

// * bot is an AI which fights other AI
// * Holds the logic for the AI movements
// * has-a relationship with 'CSprite'
class CUserControlled_Bot : public CBot
{
public:
	CUserControlled_Bot(CWindow* window, CMap* collisionMap, std::string fileName,
	                    int imageWidth, int imageHeight,
	                    int numImages_rows = 1, int numImages_columns = 1);
	~CUserControlled_Bot();

	// * allows user to manipulate things
	// * returns true if key is consumed
	bool userInput(SDL_Event* key);
	void update(); // executes from on instance variables
	void render();

private:
	bool isUpPressed, isDownPressed;
	bool isLeftPressed, isRightPressed;

};