#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../utility/stdshared.hpp"
#include "../../Level/Level.hpp"

#include <stdint.h>

#include <utility>

class Moveable
{
public:
	static constexpr float defRunSpeed = 225.0f;

	// Used to calculate movement according to time passed
	sf::Clock clock;

	sf::Vector2f position;
	sf::Vector2f size;
	Direction direction;

	Moveable();

	// Vertical speed
	float Vspeed;

	// Horizontal speed
	float Hspeed;

	void set(sf::Vector2f p, sf::Vector2f s, Direction d);

	// Calculates new position
	sf::Vector2f calcNewPosition();

	// Updates position according to forces and
	// speeds aplied to this object
	void updateDirections();

	// Sets velocity to 0
	void stop();

	void move(float x, float y);
	void move(Direction d, float len);
};

#endif // MOVEABLE_H
