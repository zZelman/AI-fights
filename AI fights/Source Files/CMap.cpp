#include "stdafx.h"
#include "CMap.h"

CMap::CMap() : CResourceDirectories()
{
}


CMap::~CMap()
{
}


void CMap::load(std::string fileName)
{
	using namespace std;

	string filePath = m_resource_tileSets + fileName;
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
			m_width = stringToInt(numStr);

			widthFound = true;
		}

		if (line.find(height) != string::npos && !heightFound)
		{
			string numStr = line.substr(height.length(), line.length());
			m_height = stringToInt(numStr);

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
			m_tileSetName = name;
		}

		if (line.find(data) != string::npos && !dataFound)
		{

			for (int i = 0; i < m_height-1; ++i)
			{
				getline(fileStream, line);

				vector<int> lineVector;
				int lineLength = line.length();
				for (int n = 0; n < lineLength-1; ++n)
				{
					string delimiter = ",";
					string numStr = line.substr(0, line.find(delimiter));
					int numInt = stringToInt(numStr);
					lineVector.push_back(numInt);

					// this line of code slowly reduces the size of the string
					//		each time a number is found (from the start to the next ',')
					//		it makes a substring from the rest of the line after the ','
					line = line.substr(line.find(delimiter)+1, line.length());
				}
				// get rid of any spot that was grown by the vector that we don't want
				//		(it is uninitialized data which could be a problem)
				lineVector.resize(m_width);
				
				m_mapData.push_back(lineVector);
			}

		}

	}

 	fileStream.close();
}


int CMap::stringToInt(std::string str)
{
	int result;
	std::stringstream convert(str);
	convert >> result;
	return result;
}