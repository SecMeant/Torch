#include "Object.hpp"

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


