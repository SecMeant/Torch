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
	
	this->mapObjects.clear();
	this->mapObjects.resize(this->mapHeader.mapWidth * this->mapHeader.mapHeight);

	for(auto& obj:this->mapObjects)
	{
		obj = nullptr;
	}

	while(this->fetchObjectFromFile(mapfile, lm)){}

	for(auto& obj:this->mapObjects)
	{
		if(obj == nullptr)
			obj = new Object(Object::Type::Ground);
	}
}

bool Level::fetchObjectFromFile(FILE *mapfile, LightManager *lm)
{
	struct mapObject obj;
	Object mobj(Object::Type::Ground); 
	OTorch *tobj;
	auto ret = fread(&obj, sizeof(mapObject), 1, mapfile);
	
	if(not ret)
	{
		puts("Error while fetching object from map file.");
		return false;
	}
	
	switch(obj.id)
	{
		// Wall
		case 0:
			mobj.texture = &TextureManager::wall;
			mobj.type = Object::Type::Wall;
			mobj.isBlocking = true;
			break;

		// Box branch
		case 1:
			mobj.texture = &TextureManager::box;
			mobj.type = Object::Type::Box;
			mobj.isBlocking = true;
			break;

		// Adding light branch
		case 2:
			tobj = new OTorch(obj.x * defaultTileWidth, obj.y * defaultTileHeight);
			tobj->isBlocking = false;

			this->insertObject(static_cast<Object*>(tobj));
	
			lm->registerLightSource(static_cast<LightSource*>(tobj));

			// On map insert empty floor
			mobj.texture = &TextureManager::ground;
			mobj.type = Object::Type::Ground;
			mobj.isBlocking = false;
			break;

		// Floor / ground
		case 3:
			mobj.texture = &TextureManager::ground;
			mobj.type = Object::Type::Ground;
			mobj.isBlocking = false;
			break;
		
		// Dunno
		default:
			mobj.texture = &TextureManager::nulltexture;
			mobj.type = Object::Type::Ground;
			mobj.isBlocking = false;
	}

	mobj.position.x = obj.x * defaultTileWidth;
	mobj.position.y = obj.y * defaultTileHeight;
	mobj.size.x = defaultTileWidth;
	mobj.size.y = defaultTileHeight;

	this->insertMapObject(obj.x, obj.y, new Object(mobj));
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

void Level::insertMapObject(uint32_t x, uint32_t y, Object* nobj)
{
	if(x >= this->mapHeader.mapWidth)
		return;

	if(y >= this->mapHeader.mapHeight)
		return;

	auto offset = x + y*this->mapHeader.mapWidth;

	delete this->mapObjects.at(offset);
	this->mapObjects.at(offset) = nobj;
}

void Level::insertObject(Object* obj)
{
	this->objects.push_back(obj);
}

void Level::removeObject(Object *obj)
{
	for(auto it = this->objects.begin(), end = this->objects.end(); it != end; ++it)
	{
		if(*it == obj)
		{
			this->objects.erase(it);
		}
	}
}

Object* Level::getMapObject(uint32_t x, uint32_t y) const
{
	if(x >= this->mapHeader.mapWidth)
		return nullptr;

	if(y >= this->mapHeader.mapHeight)
		return nullptr;
	
	auto offset = x + y*this->mapHeader.mapWidth;

	return this->mapObjects.at(offset);
}

Object* Level::getObject(uint32_t x, uint32_t y) const
{
	// Poor implementation i know, maybe later ill do better
	for(auto obj:this->objects)
	{
		if((uint32_t)(obj->position.x/32.0f) == x &&
		   (uint32_t)(obj->position.y/32.0f) == y)
		{
			return obj;
		}
	}

	return nullptr;
}

void Level::printObjects()
{
	puts("Object list:");
	for(const auto& obj:this->mapObjects)
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

