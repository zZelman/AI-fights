#include "stdafx.h"
#include "CSprite.h"

CSprite::CSprite(CWindow* window, std::string fileName,
                 int imageWidth, int imageHeight,
                 int numImages_rows, int numImages_columns)
	: CResourceDirectories()
{
	m_pWindow = window;

	isSpriteSheetLoaded = false;
	setFileName(fileName);

	m_imageWidth	= imageWidth;
	m_imageHeight	= imageHeight;
	m_numRows		= numImages_rows;
	m_numColums		= numImages_columns;

	m_imageArray = new SDL_Rect*[m_numRows];
	for (int i = 0; i < m_numRows; ++i)
	{
		m_imageArray[i] = new SDL_Rect[m_numColums];
	}

	// default color manipulation is white
	m_red	= 255;
	m_green = 255;
	m_blue	= 255;

	// default alpha is solid
	m_alpha	= 255;

	// default blending is no blending
	m_blendMode = SDL_BLENDMODE_NONE;

	load();
}


CSprite::~CSprite()
{
	free();
}


SDL_Texture* CSprite::getTexture()
{
#ifdef DEBUG
	assert(isSpriteSheetLoaded);
#endif // DEBUG

	return m_pSpriteSheet;
}


int CSprite::getImageWidth()
{
	return m_imageWidth;
}


int CSprite::getImageHeight()
{
	return m_imageHeight;
}


int CSprite::getEntireWidth()
{
	return m_entireWidth;
}


int CSprite::getEntireHeight()
{
	return m_entireHeight;
}


int CSprite::getNumRows()
{
	return m_numRows;
}


int CSprite::getNumColumns()
{
	return m_numColums;
}


std::string CSprite::getFileName()
{
	return m_fileName;
}


void CSprite::setFileName(std::string fileName)
{
	//m_filePath = m_resource_sprite += (fileName);
	m_filePath = fileName;
	m_fileName = fileName;
}


void CSprite::free()
{
	if (isSpriteSheetLoaded == true)
	{
		for (int i = 0; i < m_numRows; ++i)
		{
			delete [] m_imageArray[i];
		}
		delete [] m_imageArray;
		m_imageArray = NULL;

		SDL_DestroyTexture(m_pSpriteSheet);
		m_pSpriteSheet = NULL;
		m_imageWidth = 0;
		m_imageHeight = 0;
		m_entireWidth = 0;
		m_entireHeight = 0;

		isSpriteSheetLoaded = false;
	}
}


void CSprite::load()
{
	m_pSpriteSheet = NULL;

	// load image at specified path
	SDL_Surface* pLoadedSurface = IMG_Load(m_filePath.c_str());
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
	m_pSpriteSheet = SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), pLoadedSurface);
#ifdef DEBUG
	assert(m_pSpriteSheet != NULL);
#endif // DEBUG

	m_entireWidth = pLoadedSurface->w;
	m_entireHeight = pLoadedSurface->h;

	// free unneeded surface
	SDL_FreeSurface(pLoadedSurface);

	isSpriteSheetLoaded = true;

	for (int i = 0; i < m_numRows; ++i)
	{
		for (int n = 0; n < m_numColums; ++n)
		{
			int topLeftX = n * m_imageWidth;
			int topLeftY = i * m_imageHeight;
			SDL_Rect rect = {topLeftX, topLeftY, m_imageWidth, m_imageHeight};
			m_imageArray[i][n] = rect;
		}
	}
}


void CSprite::loadNew(std::string fileName,
                      int imageWidth, int imageHeight,
                      int numImages_rows, int numImages_columns)
{
	isSpriteSheetLoaded = true; // going to be loading new, so delete the old (it must be there)
	free();

	setFileName(fileName);

	m_imageWidth	= imageWidth;
	m_imageHeight	= imageHeight;
	m_numRows		= numImages_rows;
	m_numColums		= numImages_columns;

	m_imageArray = new SDL_Rect*[m_numRows];
	for (int i = 0; i < m_numRows; ++i)
	{
		m_imageArray[i] = new SDL_Rect[m_numColums];
	}

	// default color manipulation is white
	m_red	= 255;
	m_green = 255;
	m_blue	= 255;

	// default alpha is solid
	m_alpha	= 255;

	// default blending is no blending
	m_blendMode = SDL_BLENDMODE_NONE;

	load();
}


void CSprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	m_red	= red;
	m_green = green;
	m_blue	= blue;
}


void CSprite::manipulate_Color()
{
	SDL_SetTextureColorMod(m_pSpriteSheet, m_red, m_green, m_blue);
}


void CSprite::setAlpha(Uint8 alpha)
{
	m_alpha = alpha;
}


void CSprite::manipulate_Alpha()
{
	SDL_SetTextureAlphaMod(m_pSpriteSheet, m_alpha);
}


void CSprite::setBlendMode(SDL_BlendMode blendMode)
{
	m_blendMode = blendMode;
}


void CSprite::manipulate_Blending()
{
	SDL_SetTextureBlendMode(m_pSpriteSheet, m_blendMode);
}


SDL_Rect CSprite::getRect(int row, int column)
{
	SDL_Rect rect = m_imageArray[row - 1][column - 1];
	return rect;
}


void CSprite::render(int screenX, int screenY,
                     int screenW, int screenH,
                     int sheetRow, int sheetColumn)
{
	manipulate_Color();
	manipulate_Alpha();
	//manipulate_Blending();

	// Set rendering space and render to screen
	SDL_Rect renderQuad = {screenX, screenY, m_entireWidth, m_entireHeight};
	if (screenW != NULL &&
	        screenH != NULL)
	{
		renderQuad.w = screenW;
		renderQuad.h = screenH;
	}

	// individual sprite to be rendered to renderQuad
	SDL_Rect spriteQuad = getRect(sheetRow, sheetColumn);

	// * render to the screen
	// * 'clip' is the selection from the sprite sheet
	SDL_RenderCopy(m_pWindow->getRenderer(), m_pSpriteSheet, &spriteQuad, &renderQuad);
}


bool CSprite::equals(CSprite* other)
{
	return m_fileName.compare(other->getFileName());
}