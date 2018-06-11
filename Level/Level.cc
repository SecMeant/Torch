#include "Level.hpp"
#include "../Object/Torch/OTorch.hpp"

Level::Level()
{};

Level::~Level()
{this->freeObjects();}


void Level::loadMap(FILE *mapfile, LightManager *lm)
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
	
	this->objects.clear();
	this->objects.resize(this->mapHeader.mapWidth * this->mapHeader.mapHeight);

	for(auto& obj:this->objects)
	{
		obj = new Object();
	}

	while(this->fetchObjectFromFile(mapfile, lm)){}
}

bool Level::fetchObjectFromFile(FILE *mapfile, LightManager *lm)
{
	struct mapObject obj;
	Object mobj; 
	OTorch *tobj;
	auto ret = fread(&obj, sizeof(mapObject), 1, mapfile);
	
	if(not ret)
	{
		puts("Error while fetching object from map file.");
		return false;
	}
	
	switch(obj.id)
	{
		case 0:
			mobj.texture = &TextureManager::wall;
			break;
		case 1:
			mobj.texture = &TextureManager::box;
			break;
		case 2:

			tobj = new OTorch(obj.x * defaultTileWidth, obj.y * defaultTileHeight);

			this->insertObject(obj.x, obj.y, tobj);

			//lm->registerLightSource(static_cast<LightSource*>(tobj));
			break;
		default:
			mobj.texture = &TextureManager::nulltexture;
	}

	mobj.position.x = obj.x * defaultTileWidth;
	mobj.position.y = obj.y * defaultTileHeight;
	mobj.size.x = defaultTileWidth;
	mobj.size.y = defaultTileHeight;

	this->insertObject(obj.x, obj.y, new Object(mobj));
	return true;
}

void Level::loadMap(const char *mapfilepath, LightManager *lm)
{
	FILE *f = fopen(mapfilepath, "rb");
	
	if(f == NULL)
	{
		printf("Could not open file %s.", mapfilepath);
		return;
	}

	this->loadMap(f, lm);
}

void Level::insertObject(uint32_t x, uint32_t y, Object* nobj)
{
	if(x >= this->mapHeader.mapWidth)
		return;

	if(y >= this->mapHeader.mapHeight)
		return;

	auto offset = x + y*this->mapHeader.mapWidth;

	delete this->objects.at(offset);
	this->objects.at(offset) = nobj;
}

Object* Level::getObject(uint32_t x, uint32_t y) const
{
	if(x >= this->mapHeader.mapWidth)
		return nullptr;

	if(y >= this->mapHeader.mapHeight)
		return nullptr;
	
	auto offset = x + y*this->mapHeader.mapWidth;

	return this->objects.at(offset);
}

void Level::printObjects()
{
	puts("Object list:");
	for(const auto& obj:this->objects)
	{
		printf("x: %f\t y: %f width: %f height: %f",
				    obj->position.x, obj->position.y,
						obj->size.x, obj->size.y);
		if(obj->texture == &TextureManager::nulltexture)
		{
			printf(" NULL");
		}
		puts("");
	}
}

