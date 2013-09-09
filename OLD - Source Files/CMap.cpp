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
	free();
}


int CMap::getRows()
{
	return m_MapRows;
}


int CMap::getColumns()
{
	return m_MapColumns;
}


int CMap::getWidth_tile()
{
	return m_tileWidth;
}


int CMap::getHeight_tile()
{
	return m_tileHeight;
}


const std::vector<STileData<int>*>* CMap::getMapTiles()
{
	return &m_pMapTiles;
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

			std::vector<std::vector<int>> mapData;
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

				mapData.push_back(lineVector);
			}

			for (int i = 0; i < mapData.size(); ++i)
			{
				vector<int> lineVector = mapData[i];
				for (int n = 0; n < lineVector.size(); ++n)
				{
					if (lineVector[n] == 0)
					{
						continue;
					}

					STileData<int>* pTile = new STileData<int>();
					pTile->width = m_tileWidth;
					pTile->height = m_tileHeight;
					pTile->spriteCoords.setCoords(lineVector[n], 1);
					pTile->mapCoords.setCoords(n, i);
					pTile->screenCoords_topLeft.setCoords(n * m_tileHeight, i * m_tileWidth);
					pTile->screenCoords_bottomRight.setCoords(
					    n * m_tileHeight + m_tileHeight,
					    i * m_tileWidth + m_tileWidth);
					m_pMapTiles.push_back(pTile);
				}
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
		m_pTileCoordsArray[i].setCoords(i + 1, 1);
	}
}


void CMap::render()
{
	// using int = 0 instead of iterators because I need indecies of locations ([i][n])
	for (int i = 0; i < m_pMapTiles.size(); ++i) // row
	{
		STileData<int>* pTile = m_pMapTiles[i];

		// 0 represents no tile (thats why all sprite rendering is done in lengths)
		if (shouldCull(pTile->mapCoords.x, pTile->mapCoords.y))
		{
			continue;
		}
		else
		{
			// what number represents the tile that should be drawn
			int numberInPosition = pTile->spriteCoords.x;
			// -1 b/c length -> index in data structure
			int spriteR = m_pTileCoordsArray[numberInPosition - 1].y;
			int spriteC = m_pTileCoordsArray[numberInPosition - 1].x;

			m_pSpriteSheet->render(pTile->screenCoords_topLeft.x, pTile->screenCoords_topLeft.y,
			                       pTile->width, pTile->height,
			                       spriteR, spriteC);
		}
	}
}


bool CMap::collision_screenToMap(CAABB_f* aabb, CAABB_f* tileCollidedWith)
{
	for (int i = 0; i < m_pMapTiles.size(); ++i) // row
	{
		// i don't believe culling will help here, because then off screen objects will just fall forever

		STileData<int>* pTile = m_pMapTiles[i];

		CVector2<float> tileMin(pTile->screenCoords_topLeft.x, pTile->screenCoords_topLeft.y);
		CVector2<float> tileMax(pTile->screenCoords_bottomRight.x, pTile->screenCoords_bottomRight.y);
		CAABB_f tileAABB(&tileMin, &tileMax);

		if (aabb->collision(&tileAABB) == true)
		{
			if (tileCollidedWith != NULL)
			{
				// give the calling place the tile that the given aabb collided with
				tileCollidedWith->setEverything(
				    pTile->screenCoords_topLeft.x, pTile->screenCoords_topLeft.y,
				    pTile->screenCoords_bottomRight.x, pTile->screenCoords_bottomRight.y);
			}
			return true;
		}
	}
	return false;
}


bool CMap::collision_screenToMap(SCoords2<int>* pPoint)
{
	for (int i = 0; i < m_pMapTiles.size(); ++i)
	{
		STileData<int>* pTile = m_pMapTiles[i];

		int x = pPoint->x;
		int y = pPoint->y;

		if (x >= pTile->screenCoords_topLeft.x && x <= pTile->screenCoords_bottomRight.x &&
		        y >= pTile->screenCoords_topLeft.y && y <= pTile->screenCoords_bottomRight.y)
		{
			return true;
		}
	}

	return false;
}


bool CMap::collision_mapToMap(int row, int column)
{
	for (int i = 0; i < m_pMapTiles.size(); ++i)
	{
		STileData<int>* pTile = m_pMapTiles[i];
		if (pTile->mapCoords.x == column && pTile->mapCoords.y == row)
		{
			return true;
		}
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

	float mapSize = (float)m_pSpriteSheet->getNumColumns() * (float)m_pSpriteSheet->getImageWidth();
	float subDevision_num = m_pSpriteSheet->getNumColumns();
	float subDevision_size = mapSize / subDevision_num;

	int mapX = (float)screenX / (float)subDevision_size;
	return mapX;
}


int CMap::convertScreenToMap_Y(int screenY)
{
//#ifdef DEBUG
//	assert(screenY >= 0 && screenY <= m_pWindow->getHeight());
//#endif // DEBUG

	float mapSize = (float)m_pSpriteSheet->getNumRows() * (float)m_pSpriteSheet->getImageHeight();
	float subDevision_num = m_pSpriteSheet->getNumRows();
	float subDevision_size = mapSize / subDevision_num;

	int mapY = (float)screenY / (float)subDevision_size;
	return mapY;
}


int CMap::stringToInt(std::string str)
{
	int result;
	std::stringstream convert(str);
	convert >> result;
	return result;
}


bool CMap::shouldCull(int column, int row)
{
	if (isMapStretched == true) // don't cull anything because everything is rendered to screen
	{
		return false;
	}

	if ((row * m_pSpriteSheet->getImageHeight()) > m_pWindow->getHeight())
	{
		return true;
	}
	if ((column * m_pSpriteSheet->getImageWidth()) > m_pWindow->getWidth())
	{
		return true;
	}

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