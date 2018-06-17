#include "DynamicObject.hpp"

void DynamicObject::setSprite(const DynamicSprite &ds)
{
 	this->sprite = ds;
}

void DynamicObject::setSprite(const DynamicSprite &&ds)
{
	this->sprite = ds;
}

void DynamicObject::use()
{
	puts("USING OBJECT");
}

void DynamicObject::drop()
{
	puts("DROPPING OBJECT");
}

void DynamicObject::pickup()
{
	puts("PICKING UP OBJECT");
}
