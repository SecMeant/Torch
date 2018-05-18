#ifndef PLAYER_H
#define PLAYER_H

#include "../Interfaces/Moveable/Moveable.hpp"
#include "../TextureManager/DynamicSprite/DynamicSprite.hpp"

#include <stdint.h>

class Player: protected Moveable
{
private:
	mutable DynamicSprite playerSprite;

public:
	void draw(sf::RenderWindow &wnd) const;
	Player();
};

#endif // PLAYER_H
