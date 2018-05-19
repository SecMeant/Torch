#include "Moveable.hpp"

Moveable::Moveable()
:Vspeed(0.0f), Hspeed(0.0f)
{}

void Moveable::set
(CoordType p, Direction d)
{
	this->position = p;
	this->direction = d;
}

void Moveable::updatePosition()
{
	auto dt = this->clock.getElapsedTime().asSeconds();

	this->position.first += this->Hspeed*dt;
	this->position.second += this->Vspeed*dt;

	this->clock.restart();

	// Resets velocities
	this->stop();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->Vspeed -= Moveable::defRunSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->Vspeed += Moveable::defRunSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->Hspeed -= Moveable::defRunSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->Hspeed += Moveable::defRunSpeed;
}

void Moveable::stop()
{
	this->Vspeed = 0;
	this->Hspeed = 0;
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
