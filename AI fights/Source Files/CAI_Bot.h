#pragma once

#include "stdafx.h"
#include "CWindow.h"
#include "CSprite.h"
#include "CBot.h"

class CAI_Bot : public CBot
{
public:
	CAI_Bot(std::string spriteName, CWindow* pWindow);
	~CAI_Bot();

	void update(); // executes from on instance variables

private:
	bool isMovingRight; // true for yes, false for left

};