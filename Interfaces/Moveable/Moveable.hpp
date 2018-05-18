#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "../../utility/stdshared.hpp"

#include <stdint.h>

#include <utility>

class Moveable
{
public:
	typedef std::pair<float, float> CoordType;

	CoordType position;
	Direction direction;

	void set(CoordType p, Direction d);
	void move(float x, float y);
	void move(Direction d, float len);
};

#endif // MOVEABLE_H
