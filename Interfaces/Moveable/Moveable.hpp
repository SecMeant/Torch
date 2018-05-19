#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../utility/stdshared.hpp"

#include <stdint.h>

#include <utility>

class Moveable
{
public:
	typedef std::pair<float, float> CoordType;
	static constexpr float defRunSpeed = 175.0f;

	// Used to calculate movement according to time passed
	sf::Clock clock;

	CoordType position;
	Direction direction;

	Moveable();

	// Vertical speed
	float Vspeed;

	// Horizontal speed
	float Hspeed;

	void set(CoordType p, Direction d);

	// Updates position according to forces and
	// speeds aplied to this object
	void updatePosition();

	// Sets velocity to 0
	void stop();

	void move(float x, float y);
	void move(Direction d, float len);
};

#endif // MOVEABLE_H
