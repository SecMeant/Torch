#include "Moveable.hpp"

Moveable::Moveable()
:Vspeed(0.0f), Hspeed(0.0f)
{}

void Moveable::set
(sf::Vector2f p, Direction d)
{
	this->position = p;
	this->direction = d;
}

void Moveable::updatePosition()
{
	auto dt = this->clock.getElapsedTime().asSeconds();

	this->position.x += this->Hspeed*dt;
	this->position.y += this->Vspeed*dt;

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
	this->position.x += x;
	this->position.y += y;
}

void Moveable::move
(Direction d, float len)
{
	switch(d)
	{
		case Direction::N:
			this->position.y += len;
			break;
		case Direction::NE:
			this->position.x += 1.414 * len;
			this->position.y += 1.414 * len;
			break;
		case Direction::E:
			this->position.x += len;
			break;
		case Direction::SE:
			this->position.x += 1.414 * len;
			this->position.y -= 1.414 * len;
			break;
		case Direction::S:
			this->position.y -= len;
			break;
		case Direction::SW:
			this->position.x -= 1.414 * len;
			this->position.y -= 1.414 * len;
			break;
		case Direction::W:
			this->position.x -= len;
			break;
		case Direction::NW:
			this->position.x -= 1.414 * len;
			this->position.y += 1.414 * len;
			break;
	}
}
