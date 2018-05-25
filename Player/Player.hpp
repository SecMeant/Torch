#ifndef PLAYER_H
#define PLAYER_H

#include "../Interfaces/Moveable/Moveable.hpp"
#include "../TextureManager/DynamicSprite/MotionSprite/MotionSprite.hpp"

#include <stdint.h>

class Player:public Moveable
{
public:
	mutable DynamicSprite torch;
	mutable DynamicSprite light;
	mutable MotionSprite playerSprite;

	Player();

	void updateDirection();

	// Handles texture changing according to movement
	void updateOrientation();
};

#endif // PLAYER_H
