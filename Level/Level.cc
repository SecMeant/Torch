#include "Level.hpp"

void Level::loadMap(FILE *mapfile)
{
	auto ret = fread(&this->mapHeader, sizeof(this->mapHeader), 1, mapfile);

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
	struct mapObject obj;
	MapObject mobj; 
	auto ret = fread(&obj, sizeof(mapObject), 1, mapfile);
	
	if(not ret)
	{
		puts("Error while fetching object from map file.");
		return false;
	}
	
	if(obj.id == 0)
		mobj.texture = &TextureManager::wall;
	else if(obj.id == 1)
		mobj.texture = &TextureManager::box;
	else
		mobj.texture = &TextureManager::nulltexture;

	mobj.position.x = obj.x;
	mobj.position.y = obj.y;
	mobj.size.x = 32;
	mobj.size.y = 32;

	this->objects.push_back(mobj);
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
		printf("x: %f\t y: %f width: %f height: %f\n",
				    obj.position.x, obj.position.y,
						obj.size.x, obj.size.y);
	}
}

