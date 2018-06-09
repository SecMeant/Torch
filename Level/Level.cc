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

	this->objects.reserve(this->mapHeader.mapWidth*this->mapHeader.mapHeight);

	while(this->fetchObjectFromFile(mapfile, lm)){}
}

bool Level::fetchObjectFromFile(FILE *mapfile, LightManager *lm)
{
	struct mapObject obj;
	Object mobj; 
	auto ret = fread(&obj, sizeof(mapObject), 1, mapfile);
	
	if(not ret)
	{
		puts("Error while fetching object from map file.");
		return false;
	}
	
	// coords from file are in tile units
	// Need to translate them
	obj.x *= defaultTileWidth;
	obj.y *= defaultTileHeight;

	switch(obj.id)
	{
		case 0:
			mobj.texture = &TextureManager::wall;
			break;
		case 1:
			mobj.texture = &TextureManager::box;
			break;
		case 2:

		this->objects.push_back(new OTorch(obj.x, obj.y));

		// First casting with dynamic cast to cast to 
		// parent class when info about hierarchy is lost
		// Second cast makes proper shift on ptr to get to
		// derived class.
		lm->registerLightSource(
				static_cast<LightSource*>(
					dynamic_cast<OTorch*>(this->objects.back())));
		break;
		default:
			mobj.texture = &TextureManager::nulltexture;
	}

	mobj.position.x = obj.x;
	mobj.position.y = obj.y;
	mobj.size.x = defaultTileWidth;
	mobj.size.y = defaultTileHeight;

	this->objects.push_back(new Object(mobj));
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

void Level::printObjects()
{
	puts("Object list:");
	for(const auto& obj:this->objects)
	{
		printf("x: %f\t y: %f width: %f height: %f\n",
				    obj->position.x, obj->position.y,
						obj->size.x, obj->size.y);
	}
}

