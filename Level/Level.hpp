#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <memory>

#include "../utility/stdshared.hpp"
#include "../LightManager/LightManager.hpp"
#include "../Object/Object.hpp"

#include "../Tests/TestUnit.hpp"

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
	
	// Vector that holds static map objects
	// Objects occupies offsets in vector according
	// to its coordinates on map to make collision checks faster
	std::vector<Object*> mapObjects;
	std::vector<Object*> objects;

	Level& operator=(const Level&) = delete;
	Level(const Level&) = delete;

public:
	Level();

	~Level();

	void loadMap(const char *mapfilepath, LightManager *lm);
	
	inline const std::vector<Object*>& getMapObjects()
	{return this->mapObjects;}

	void insertObject(uint32_t x, uint32_t y, Object* nobj);
	Object* getObject(uint32_t x, uint32_t y) const;

	inline void freeObjects()
	{for (const auto& obj:mapObjects) delete obj;}

	void spawnLight(int32_t x, int32_t y, LightManager *lm);

	void printObjects();

	friend class UnitTest;
};

#endif // LEVEL_H
