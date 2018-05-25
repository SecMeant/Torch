#include "Level.hpp"

void Level::loadMap(FILE *mapfile)
{
	auto ret = fread(&this->mapHeader, sizeof(this->mapHeader), 1
			             ,mapfile);

	if(not ret)
	{
		puts("Error while loading map file.\n");
	}

	if(memcmp(this->mapHeader.signature, "TM", 2))
	{
		puts("Error while loading map file.\n\
				  Signature check failed.");
		return;
	}

	printf("Loading map header ended successfull.\nSize:%u %u %u\n",
			    (uint32_t)sizeof(_mapHeader),
					this->mapHeader.mapWidth,
					this->mapHeader.mapHeight);

	while(this->fetchObjectFromFile(mapfile)){}
}

bool Level::fetchObjectFromFile(FILE *mapfile)
{
	mapObject obj;
	auto ret = fread(&obj, sizeof(mapObject), 1, mapfile);
	
	if(not ret)
	{
		puts("Error while fetching object from map file.");
		return false;
	}

	this->objects.push_back(obj);
	return true;
}

void Level::loadMap(const char *mapfilepath)
{
	FILE *f = fopen(mapfilepath, "rb");
	
	if(f == NULL)
	{
		printf("Could not open file %s.", mapfilepath);
		return;
	}

	this->loadMap(f);
}

void Level::printObjects()
{
	puts("Object list:");
	for(const auto& obj:this->objects)
	{
		printf("id: %u\t x: %f\t y: %f\n",
				   obj.id, obj.x, obj.y);
	}
}

