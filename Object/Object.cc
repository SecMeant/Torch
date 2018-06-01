#include "Object.hpp"

void Object::use()
{
	puts("USING OBJECT");
}

void Object::drop()
{
	puts("DROPPING OBJECT");
}

void Object::pickup()
{
	puts("PICKING UP OBJECT");
}

sf::FloatRect Object::getObjectRange() const
{
	return sf::FloatRect(this->position.x,
											 this->position.y,
											 this->size.x,
											 this->size.y);
}

sf::Vector2f Object::getObjectCoords() const
{
	return sf::Vector2f(this->position.x,
											this->position.y);
}


