#include "TestUnit.hpp"

void TestUnit::crashTestLevelClass()
{
	typedef unsigned int uint;

	puts("Starting Level Class test . . .");

	Level level;
	LightManager lm({800,600});
	level.loadMap("./Level/mapfiles/test.map", &lm);

	for (uint x = 0; x < level.mapHeader.mapWidth; x++)
	{
		for (uint y = 0; y < level.mapHeader.mapHeight; y++)
		{
			auto obj = level.getObject(x,y);
			assert(obj->position.x/32.0f == x);
			assert(obj->position.y/32.0f == y);
		}
	}

	puts("Level class test ended successfull");
}

