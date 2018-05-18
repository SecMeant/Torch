#include "Moveable.hpp"

void Moveable::set
(CoordType p, Direction d)
{
	this->position = p;
	this->direction = d;
}

void Moveable::move
(float x, float y)
{
	this->position.first += x;
	this->position.second += y;
}

void Moveable::move
(Direction d, float len)
{
	switch(d)
	{
		case Direction::N:
			this->position.second += len;
			break;
		case Direction::NE:
			this->position.first += 1.414 * len;
			this->position.second += 1.414 * len;
			break;
		case Direction::E:
			this->position.first += len;
			break;
		case Direction::SE:
			this->position.first += 1.414 * len;
			this->position.second -= 1.414 * len;
			break;
		case Direction::S:
			this->position.second -= len;
			break;
		case Direction::SW:
			this->position.first -= 1.414 * len;
			this->position.second -= 1.414 * len;
			break;
		case Direction::W:
			this->position.first -= len;
			break;
		case Direction::NW:
			this->position.first -= 1.414 * len;
			this->position.second += 1.414 * len;
			break;
	}
}
