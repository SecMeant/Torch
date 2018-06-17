#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "../../utility/stdshared.hpp"
#include "../Object.hpp"
#include "../../TextureManager/DynamicSprite/DynamicSprite.hpp"

class DynamicObject: public Object
{
public:
	using Object::Object;

	DynamicSprite sprite;

	void setSprite(const DynamicSprite &ds);
	void setSprite(const DynamicSprite &&ds);

	virtual void use();
	virtual void drop();
	virtual void pickup();
};

#endif // DYNAMIC_OBJECT_H

