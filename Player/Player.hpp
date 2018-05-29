#ifndef PLAYER_H
#define PLAYER_H

#include "../Interfaces/Moveable/Moveable.hpp"
#include "../TextureManager/DynamicSprite/MotionSprite/MotionSprite.hpp"
#include "../Interfaces/LightSource/LightSource.hpp"

#include <stdint.h>

class Player:public Moveable, public LightSource
{
public:
	mutable DynamicSprite torch;
	mutable DynamicSprite light;
	mutable MotionSprite playerSprite;

	Player();

	void scaleLightRadius(float scaleFactor);

	// Handles texture changing according to movement
	void updateOrientation();
};

#endif // PLAYER_H
