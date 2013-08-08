#ifndef SANIMATION_H
#define SANIMATION_H


struct SAnimation {
	// * holds the sprite sheet coords for animation/successive images to be played by the bot
	// * SPRITE SHEET COORDS (lengths -> top left is 1,1)
	SCoords2<int> AnimationSequence;

	// * Timer for keeping track of how long each animation frame takes
	CTimer* pAnimationTimer;

	// how many ms will be between animation image changes
	int animationChangeMS; 
};


#endif // !SANIMATION_H
