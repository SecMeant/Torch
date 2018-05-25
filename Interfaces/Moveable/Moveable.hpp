#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../utility/stdshared.hpp"

#include <stdint.h>

#include <utility>

class Moveable
{
public:
	static constexpr float defPosx = 400;
	static constexpr float defPosy = 400;
	static constexpr float defRunSpeed = 175.0f;

	// Used to calculate movement according to time passed
	sf::Clock clock;

	sf::Vector2f position;
	Direction direction;

	Moveable();

	// Vertical speed
	float Vspeed;

	// Horizontal speed
	float Hspeed;

	void set(sf::Vector2f p, Direction d);

	// Updates position according to forces and
	// speeds aplied to this object
	void updatePosition();

	// Sets velocity to 0
	void stop();

	void move(float x, float y);
	void move(Direction d, float len);
};

#endif // MOVEABLE_H
