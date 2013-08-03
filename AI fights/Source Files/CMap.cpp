#include "stdafx.h"
#include "CMap.h"

CMap::CMap(CWindow* window, std::string fileName)
	: CResourceDirectories()
{
	m_pWindow = window;

	m_tileSetName = fileName;

	m_tileLength = 0;

	isMapLoaded = false;
	isMapStretched = false;

	load();
}


CMap::~CMap()
{

}


int CMap::getRows()
{
	return m_MapRows;
}


int CMap::getColumns()
{
	return m_MapColumns;
}


void CMap::swapIsStretched()
{
	isMapStretched = !isMapStretched;
}


void CMap::load()
{
	using namespace std;

	string filePath = /*m_resource_tileSets +*/ m_tileSetName;

	ifstream fileStream;
	fileStream.open(filePath);
#ifdef DEBUG
	assert(fileStream.is_open());
#endif // DEBUG

	// flags to look for in the file
	string width		= "width=";
	string height		= "height=";
	string tileWidth	= "tilewidth=";
	string tileHeight	= "tileheight=";
	string tileSet		= "tileset=";
	string data			= "data=";

	// to stop double findings
	bool widthFound			= false;
	bool heightFound		= false;
	bool tileHeightFound	= false;
	bool tileWidthFound		= false;
	bool tileSetfound		= false;
	bool dataFound			= false;


	string line;
	while (getline(fileStream, line))
	{
		if (line.find(width) != string::npos && !widthFound)
		{
			string numStr = line.substr(width.length(), line.length());
			m_MapColumns = stringToInt(numStr);

			widthFound = true;
		}

		if (line.find(height) != string::npos && !heightFound)
		{
			string numStr = line.substr(height.length(), line.length());
			m_MapRows = stringToInt(numStr);

			heightFound = true;
		}

		if (line.find(tileWidth) != string::npos && !tileWidthFound)
		{
			string numStr = line.substr(tileWidth.length(), line.length());
			m_tileWidth = stringToInt(numStr);

			tileWidthFound = true;
		}

		if (line.find(tileHeight) != string::npos && !tileHeightFound)
		{
			string numStr = line.substr(tileHeight.length(), line.length());
			m_tileHeight = stringToInt(numStr);

			tileHeightFound = true;
		}

		if (line.find(tileSet) != string::npos && !tileSetfound)
		{
			string s = line.substr(tileSet.length(), line.length());
			string delimiter = ",";
			string name = s.substr(0, s.find(delimiter));
			m_tileSetName = "Resource Files/Sprites/" + name;
		}

		if (line.find(data) != string::npos && !dataFound)
		{

			for (int i = 0; i < m_MapRows; ++i)
			{
				getline(fileStream, line);

				vector<int> lineVector;
				int lineLength = line.length();
				for (int n = 0; n < lineLength; ++n)
				{
					string delimiter = ",";
					string numStr = line.substr(0, line.find(delimiter));
					int numInt = stringToInt(numStr);
					lineVector.push_back(numInt);

					// this line of code slowly reduces the size of the string
					//		each time a number is found (from the start to the next ',')
					//		it makes a substring from the rest of the line after the ','
					line = line.substr(line.find(delimiter) + 1, line.length());
				}
				// get rid of any spot that was grown by the vector that we don't want
				//		(it is uninitialized data which could be a problem)
				lineVector.resize(m_MapColumns);

				m_mapData.push_back(lineVector);
			}

		}

	}

	fileStream.close();

	isMapLoaded = true;

	m_pSpriteSheet = new CSprite(m_pWindow, m_tileSetName,
	                             m_tileWidth, m_tileHeight,
	                             1, 8);

	int spriteColumns = m_pSpriteSheet->getNumColumns();
	m_pTileCoordsArray = new SCoords2<int>[spriteColumns];

	// this for loop assumes that it is a 1D tile set of sequential indecies converted to lengths
	for (int i = 0; i < spriteColumns; ++i)
	{
		m_pTileCoordsArray[i] = SCoords2<int>(i + 1, 1);
	}
}


void CMap::render()
{
	// using int = 0 instead of iterators because I need indecies of locations ([i][n])
	for (int i = 0; i < m_mapData.size(); ++i) // row
	{
		std::vector<int> lineVector = m_mapData[i];
		for (int n = 0; n < lineVector.size(); ++n) // column
		{
			// 0 represents no tile (thats why all sprite rendering is done in lengths)
			if (lineVector[n] == 0 || shouldCull(i, n))
			{
				continue;
			}
			else
			{
				int screenX, screenY;
				int screenW, screenH;

				if (isMapStretched == true)
				{
					// these two floats are what make the map draw to the entire screen no mater what
					float proportionX = m_pWindow->getWidth() / lineVector.size();
					float proportionY = m_pWindow->getHeight() / m_mapData.size();

					screenX = n * proportionX;
					screenY = i * proportionY;

					screenW = proportionX;
					screenH = proportionY;
				}
				else if (isMapStretched == false)
				{
					screenX = n * m_pSpriteSheet->getImageWidth();
					screenY = i * m_pSpriteSheet->getImageHeight();

					screenW = m_pSpriteSheet->getImageWidth();
					screenH = m_pSpriteSheet->getImageHeight();
				}

				// what number represents the tile that should be drawn
				int numberInPosition = lineVector[n];
				// -1 b/c length -> index in data structure
				int spriteR = m_pTileCoordsArray[numberInPosition - 1].y;
				int spriteC = m_pTileCoordsArray[numberInPosition - 1].x;

				m_pSpriteSheet->render(screenX, screenY, screenW, screenH,
				                       spriteR, spriteC);
			}
		}
	}
}


bool CMap::collision_screenToMap(CAABB_f* aabb, CAABB_f* tileCollidedWith)
{
	for (int i = 0; i < m_mapData.size(); ++i) // row
	{
		std::vector<int> lineVector = m_mapData[i];
		for (int n = 0; n < lineVector.size(); ++n) // column
		{
			if (lineVector[n] == 0 || shouldCull(i, n))
			{
				continue;
			}

			int topLeftX, topLeftY;
			int botomRightX, botomRightY;

			if (isMapStretched == true)
			{
				// window size / how many tiles are in it = size of individual tile
				float proportionX = m_pWindow->getWidth() / lineVector.size();
				float proportionY = m_pWindow->getHeight() / m_mapData.size();

				topLeftX = n * proportionX;
				topLeftY = i * proportionY;

				botomRightX = topLeftX + proportionX;
				botomRightY = topLeftY + proportionY;
			}
			else if (isMapStretched == false)
			{
				topLeftX = n * m_pSpriteSheet->getImageWidth();
				topLeftY = i * m_pSpriteSheet->getImageHeight();

				botomRightX = topLeftX + m_pSpriteSheet->getImageWidth();
				botomRightY = topLeftY + m_pSpriteSheet->getImageHeight();
			}

			CVector2<float> tileMin(topLeftX, topLeftY);
			CVector2<float> tileMax(botomRightX, botomRightY);
			CAABB_f tileAABB(&tileMin, &tileMax);

			if (aabb->collision(&tileAABB) == true)
			{
				if (tileCollidedWith != NULL)
				{
					// give the calling place the tile that the given aabb collided with
					tileCollidedWith->setEverything(topLeftX, topLeftY, botomRightX, botomRightY);
				}
				//collision_screenToMap_fake(aabb, tileCollidedWith);
				return true;
			}
		}
	}
	return false;
}


bool CMap::collision_screenToMap_fake(CAABB_f* aabb, CAABB_f* tileCollidedWith)
{
	int topLeftX = aabb->getMin()->x;
	int topLeftY = aabb->getMin()->y;

	int botomRightX = aabb->getMax()->x;
	int botomRightY = aabb->getMax()->y;

	int topRightX = botomRightX;
	int topRightY = topLeftY;

	int botomLeftX = topLeftX;
	int botomLeftY = botomRightY;

	//convertScreenToMap(&topLeftX,		&topLeftY);
	//convertScreenToMap(&botomRightX,	&botomRightY);
	convertScreenToMap(&topRightX,		&topRightY);
	//convertScreenToMap(&botomLeftX,		&botomLeftY);

	// NOTE!!	* now the vars are in MAP coords
	//			* collision happens on map if coord is != 0 b/c Tiled does it that way

	// window size / how many tiles are in it = size of individual tile
	//float proportionX = m_pWindow->getWidth() / m_mapData[1].size();
	//float proportionY = m_pWindow->getHeight() / m_mapData.size();

	// length to index inside of data structure
	//int map_topLeft = m_mapData[topLeftY-1][topLeftX-1];
	//int map_botomRight = m_mapData[botomRightY-1][botomRightX-1];
	int map_topRight = m_mapData[topRightY][topRightX];
	//int map_botomLeft = m_mapData[botomLeftY-1][botomLeftX-1];

	int q = 0;

	//if (m_mapData[topLeftY][topLeftX] != 0)
	//{
	//	if (tileCollidedWith != NULL)
	//	{
	//		int topLeftX_tile = topLeftX * proportionX;
	//		int topLeftY_tile = topLeftY * proportionY;

	//		int botomRightX_tile = topLeftX_tile + proportionX;
	//		int botomRightY_tile = topLeftY_tile + proportionY;

	//		// give the calling place the tile that the given aabb collided with
	//		tileCollidedWith->setEverything(topLeftX_tile, topLeftY_tile, botomRightX_tile, botomRightY_tile);
	//	}

	//	return true;
	//}
	//if (m_mapData[botomRightY][botomRightX] != 0)
	//{
	//	if (tileCollidedWith != NULL)
	//	{
	//		int topLeftX_tile = botomRightX * proportionX;
	//		int topLeftY_tile = botomRightY * proportionY;

	//		int botomRightX_tile = topLeftX_tile + proportionX;
	//		int botomRightY_tile = topLeftY_tile + proportionY;

	//		// give the calling place the tile that the given aabb collided with
	//		tileCollidedWith->setEverything(topLeftX_tile, topLeftY_tile, botomRightX_tile, botomRightY_tile);
	//	}

	//	return true;
	//}
	//if (m_mapData[topRightY][topRightX] != 0)
	//{
	//	if (tileCollidedWith != NULL)
	//	{
	//		int topLeftX_tile = topRightX * proportionX;
	//		int topLeftY_tile = topRightY * proportionY;

	//		int botomRightX_tile = topLeftX_tile + proportionX;
	//		int botomRightY_tile = topLeftY_tile + proportionY;

	//		// give the calling place the tile that the given aabb collided with
	//		tileCollidedWith->setEverything(topLeftX_tile, topLeftY_tile, botomRightX_tile, botomRightY_tile);
	//	}

	//	return true;
	//}
	//if (m_mapData[botomLeftY][botomLeftX] != 0)
	//{
	//	if (tileCollidedWith != NULL)
	//	{
	//		int topLeftX_tile = botomLeftX * proportionX;
	//		int topLeftY_tile = botomLeftY * proportionY;

	//		int botomRightX_tile = topLeftX_tile + proportionX;
	//		int botomRightY_tile = topLeftY_tile + proportionY;

	//		// give the calling place the tile that the given aabb collided with
	//		tileCollidedWith->setEverything(topLeftX_tile, topLeftY_tile, botomRightX_tile, botomRightY_tile);
	//	}

	//	return true;
	//}

	return false;
}


bool CMap::collision_mapToMap(int row, int column)
{
	std::vector<int> lineVector = m_mapData[row];
	int num = lineVector[column];

	if (num != 0) // 0 represents no rendering on map -> != is collision
	{
		return true;
	}

	return false;
}


void CMap::convertScreenToMap(int* screenX, int* screenY)
{
	*screenX = convertScreenToMap_X(*screenX);
	*screenY = convertScreenToMap_Y(*screenY);
}


int CMap::convertScreenToMap_X(int screenX)
{
//#ifdef DEBUG
//	assert(screenX >= 0 && screenX <= m_pWindow->getWidth());
//#endif // DEBUG

	int mapX = ceil(((float)m_pSpriteSheet->getNumColumns() * (float)m_pSpriteSheet->getImageWidth())
	                / (float)screenX);
	return mapX;
}


int CMap::convertScreenToMap_Y(int screenY)
{
//#ifdef DEBUG
//	assert(screenY >= 0 && screenY <= m_pWindow->getHeight());
//#endif // DEBUG

	int mapY = ceil(((float)m_pSpriteSheet->getNumRows() * (float)m_pSpriteSheet->getImageHeight())
	                / (float)screenY);
	return mapY;
}


int CMap::stringToInt(std::string str)
{
	int result;
	std::stringstream convert(str);
	convert >> result;
	return result;
}


bool CMap::shouldCull(int row, int column)
{
	if (isMapStretched == true) // don't cull anything because everything is rendered to screen
		return false;

	if ( (row * m_pSpriteSheet->getImageHeight()) > m_pWindow->getHeight())
		return true;
	if ( (column * m_pSpriteSheet->getImageWidth()) > m_pWindow->getWidth())
		return true;

	return false;
}


void CMap::free()
{
	if (isMapLoaded)
	{
		delete m_pSpriteSheet;
		delete[] m_pTileCoordsArray;
	}
}