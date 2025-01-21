#pragma once
#include <string>

class Map {
public:
	Map(std::string tID, int ms, int ts);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int scrX, int scrY, int xpos, int ypos);

private:
	std::string texID;
	int mapScale, tileSize, scaledSize;
};