#pragma once

#include "stdafx.h"
#include "CResourceDirectories.h"
#include "CWindow.h"

class CSprite : public CResourceDirectories
{
public:
	// only takes the file name, default texture directory is used
	CSprite(CWindow* window, std::string fileName,
	        int imageWidth, int imageHeight,
	        int numImages_rows = 1, int numImages_columns = 1);
	~CSprite();

	SDL_Texture* getTexture();
	int getImageWidth();
	int getImageHeight();
	int getEntireWidth();
	int getEntireHeight();
	int getNumRows();
	int getNumColumns();
	std::string getFileName();

	// * change the file name of the texture
	// * NOTE: does not load
	// * NOTE: destroys old texture (b/c y change name if not new texture?)
	void setFileName(std::string fileName);

	void free(); // releases resources used by the texture
	void load(); // loads from m_filePath into m_spriteSheet
	// loads a new file into a texture NOTE: destroys old one
	void loadNew(std::string fileName,
	             int imageWidth, int imageHeight,
	             int numImages_rows = 1, int numImages_columns = 1);

	// * sets the color modulation for the texture
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void manipulate_Color(); // manipulates the rendering of this texture by the defined member variables

	// alpha is transparency 255 is solid (opaque)
	void setAlpha(Uint8 alpha);
	void manipulate_Alpha();

	// blend mode is how the src rectangle is drawn onto the destination rectangle in SDL_RenderCopy()
	void setBlendMode(SDL_BlendMode blendMode);
	void manipulate_Blending();

	// returns the rectangle of the sprite at [row][column] inside of the image array
	SDL_Rect getRect(int row = 1, int column = 1);

	// * x, y: where the top left corner of the texture will start to be rendered in screen space
	// * screenW, screenH: width and height the sprite will be rendered TO (null will be the whole size of the sprite sheet)
	// * sheetRow, sheetColumn: LENGTH which segment of the sprite sheet will be rendered (defaults to top left)
	void render(int screenX, int screenY,
	            int screenW = NULL, int screenH = NULL,
	            int sheetRow = 1, int sheetColumn = 1);

	bool equals(CSprite* other);

private:
	CWindow* m_pWindow; // access to the game window

	bool isSpriteSheetLoaded; // simple check to see if load() has been called
	SDL_Texture* m_pSpriteSheet; // 2D sprite sheet with the images having the same width & height

	int m_entireWidth, m_entireHeight; // LENGTH width and height of the sprite sheet
	int m_imageWidth, m_imageHeight; // individual image PIXEL width & height
	int m_numRows, m_numColums; // LENGTH how many images there are per row/column

	std::string m_filePath; // full path to sprite sheet
	std::string m_fileName; // just file name of sprite sheet (used in == testing)

	// the sprite sheet is comprised of 2D images with the same size and width
	//		So, this is an array of pointers of size n pointing to another array of size m
	// NOT REFFERENCED BY INDEX image 1,1 is the top left
	SDL_Rect** m_imageArray;

	Uint8 m_red, m_green, m_blue; // color manipulations of the texture (255 = white)
	Uint8 m_alpha; // alpha manipulation (255 = solid [opaque])
	SDL_BlendMode m_blendMode; // how src rect is blended with dest rect in SDL_RenderCopy()
};
