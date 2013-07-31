#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CSprite.h"
#include "CBot.h"

class CAI_Bot : public CBot
{
public:
	CAI_Bot(CWindow* window, std::string fileName, 
		int imageWidth, int imageHeight,
		int numImages_rows = 1, int numImages_columns = 1);
	~CAI_Bot();

	void update(); // executes from on instance variables

private:
	bool isMovingRight; // true for yes, false for left

};