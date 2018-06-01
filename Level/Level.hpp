#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <memory>

#include "../utility/stdshared.hpp"
#include "../LightManager/LightManager.hpp"
#include "../Object/Object.hpp"

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
	void loadMap(FILE *mapfile, LightManager *lm);
	bool fetchObjectFromFile(FILE *mapfile, LightManager *lm);
	std::vector<std::unique_ptr<Object> > objects;

public:
	Level();

	void loadMap(const char *mapfilepath, LightManager *lm);
	void drawAll(sf::RenderWindow &wnd);
	
	inline const std::vector<std::unique_ptr<Object> >& getObjects()
	{return this->objects;}

	void printObjects();
};

#endif // LEVEL_H
