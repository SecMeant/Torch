#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../utility/stdshared.hpp"

class Level
{
public:
	static constexpr int32_t defaultWidth      = 25;
	static constexpr int32_t defaultHeight     = 25;
	static constexpr int32_t defaultTileWidth  = 32;
	static constexpr int32_t defaultTileHeight = 32;

	typedef unsigned char byte;

	enum class Tile
	{
		wall,
		box
	};

	#pragma pack(push,1)
	struct _mapHeader
	{
		char signature[2];
		uint32_t mapWidth;
		uint32_t mapHeight;
	}mapHeader;

	struct mapObject
	{
		uint32_t id;
		float x;
		float y;
	};
	#pragma pack(pop)

private:
	void loadMap(FILE *mapfile);
	bool fetchObjectFromFile(FILE *mapfile);
	std::vector<mapObject> objects;

public:
	Level() = default;

	void loadMap(const char *mapfilepath);
	void drawAll(sf::RenderWindow &wnd);
	
	inline const std::vector<mapObject>& getObjects()
	{return this->objects;}

	void printObjects();
};

#endif // LEVEL_H
