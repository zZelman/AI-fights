#pragma once

#include "stdafx.h"
#include "CResourceDirectories.h"
#include "CWindow.h"

class CSprite : public CResourceDirectories
{
public:
	CSprite(std::string fileName, CWindow* window); // only takes the file name, default texture directory is used
	~CSprite();

	SDL_Texture* getTexture();
	int getWidth();
	int getHeight();
	std::string getFileName();

	// * change the file name of the texture
	// * NOTE: does not load
	// * NOTE: destroys old texture (b/c y change name if not new texture?)
	void setFileName(std::string fileName);

	void free(); // releases resources used by the texture
	void load(); // loads from m_TexturePath into m_pTexture
	void loadNew(std::string fileName); // loads a new file into a texture NOTE: destroys old one

	// * sets the color modulation for the texture
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void manipulate_Color(); // manipulates the rendering of this texture by the defined member variables

	// alpha is transparency 255 is solid (opaque)
	void setAlpha(Uint8 alpha);
	void manipulate_Alpha();

	// blend mode is how the src rectangle is drawn onto the destination rectangle in SDL_RenderCopy()
	void setBlendMode(SDL_BlendMode blendMode);
	void manipulate_Blending();

	// * x, y: where the top left corner of the texture will start to be rendered
	// * clip: the rectangle from the sprite sheet to be rendered. NULL just renders the whole thing
	void render(int x, int y, SDL_Rect* clip = NULL);

	bool equals(CSprite* other);

private:
	CWindow* m_pWindow; // access to the game window

	bool isTextureLoaded; // simple check to see if load() has been called
	// final loaded 'texture'
	//		called a texture because it is a sprite sheet -parts-
	//		applied to an arbitrary rectangle
	SDL_Texture* m_pTexture;
	int m_width, m_height; // width and height of the texture
	std::string m_TexturePath; // full path to texture
	std::string m_TextureName; // just file name of texture (used in == testing)

	Uint8 m_red, m_green, m_blue; // color manipulations of the texture (255 = white)
	Uint8 m_alpha; // alpha manipulation (255 = solid [opaque])
	SDL_BlendMode m_blendMode; // how src rect is blended with dest rect in SDL_RenderCopy()
};
