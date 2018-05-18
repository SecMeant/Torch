#ifndef PLAYER_H
#define PLAYER_H

#include "../Interfaces/Moveable/Moveable.hpp"
#include "../TextureManager/DynamicSprite/MotionSprite/MotionSprite.hpp"

#include <stdint.h>

class Player:public Moveable
{
public:
	mutable MotionSprite playerSprite;

	Player();

	void draw(sf::RenderWindow &wnd) const;
};

#endif // PLAYER_H
