#ifndef STATSOBJECT_H
#define STATSOBJECT_H

#include <string>
#include "../../../utility/stdshared.hpp"

// Used to store texture + value combination
// to represent stats on screen, like current torch amount etc
class StatsObject
{
public:
	int32_t value;

private:
	DynamicSprite texture;
	sf::Vector2f position; // On screen position
	sf::Text text; // holds this->value as string

public:
	StatsObject(int32_t val, DynamicSprite &&tex, sf::Vector2f pos);

	void draw(sf::RenderWindow &wnd);
};

#endif // STATSOBJECT_H
