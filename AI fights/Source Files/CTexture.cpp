#include "stdafx.h"
#include "CTexture.h"
#include "CWindow.h"

CTexture::CTexture(std::string fileName, CWindow* window) : CResourceDirectories()
{
	m_TexturePath	= m_resource_texture += (fileName);
	m_TextureName	= fileName;
	isTextureLoaded = false;

	// default color manipulation is white
	m_red	= 255;
	m_green = 255;
	m_blue	= 255;

	// default alpha is solid
	m_alpha	= 255;

	// default blending is no blending
	m_blendMode = SDL_BLENDMODE_NONE;

	m_pWindow = window;
}


CTexture::~CTexture()
{
	free();
}


SDL_Texture* CTexture::getTexture()
{
#ifdef DEBUG
	assert(isTextureLoaded);
#endif // DEBUG

	return m_pTexture;
}


int CTexture::getWidth()
{
	return m_width;
}


int CTexture::getHeight()
{
	return m_height;
}


std::string CTexture::getFileName()
{
	return m_TextureName;
}


void CTexture::setFileName(std::string fileName)
{
	free();
	m_TexturePath = m_resource_texture += (fileName);
	m_TextureName = fileName;
}


void CTexture::free()
{
	if (isTextureLoaded == true)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = NULL;
		m_width = 0;
		m_height = 0;

		isTextureLoaded = false;
	}
}


void CTexture::load()
{
	m_pTexture = NULL;

	// load image at specified path
	SDL_Surface* pLoadedSurface = IMG_Load(m_TexturePath.c_str());
#ifdef DEBUG
	assert(pLoadedSurface != NULL);
#endif // DEBUG

	// Color Key image
	// * this samples the surface for transparent pixels and then removes them if they exist
	//		sampling is done with the call to SDL_MapRGB
	// * as it is now, does not read blue - 0xFF (g) by 0xFF (b) is a turquoise is color
	// * whatever color SDL_MapRGB is set too, the texture will not display
	SDL_SetColorKey(pLoadedSurface, SDL_TRUE, SDL_MapRGB(pLoadedSurface->format, 0, 0xFF, 0xFF));

	// create texture from surface pixels
	m_pTexture = SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), pLoadedSurface);
#ifdef DEBUG
	assert(m_pTexture != NULL);
#endif // DEBUG

	m_width = pLoadedSurface->w;
	m_height = pLoadedSurface->h;

	// free unneeded surface
	SDL_FreeSurface(pLoadedSurface);

	isTextureLoaded = true;
}


void CTexture::loadNew(std::string fileName)
{
	setFileName(fileName);
	load();
}


void CTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	m_red	= red;
	m_green = green;
	m_blue	= blue;
}


void CTexture::manipulate_Color()
{
	SDL_SetTextureColorMod(m_pTexture, m_red, m_green, m_blue);
}


void CTexture::setAlpha(Uint8 alpha)
{
	m_alpha = alpha;
}


void CTexture::manipulate_Alpha()
{
	SDL_SetTextureAlphaMod(m_pTexture, m_alpha);
}


void CTexture::setBlendMode(SDL_BlendMode blendMode)
{
	m_blendMode = blendMode;
}


void CTexture::manipulate_Blending()
{
	SDL_SetTextureBlendMode(m_pTexture, m_blendMode);
}


void CTexture::render(int x, int y, SDL_Rect* clip)
{
	manipulate_Color();
	manipulate_Alpha();
	//manipulate_Blending();

	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, m_width, m_height};

	// set clip rendering dimensions (part of the texture to be rendered -- a sprite from a sprite sheet)
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// * render to the screen
	// * 'clip' is the selection from the sprite sheet
	SDL_RenderCopy(m_pWindow->getRenderer(), m_pTexture, clip, &renderQuad);
}


bool CTexture::equals(CTexture* other)
{
	return m_TextureName.compare(other->getFileName());
}