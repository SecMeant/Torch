#include "Moveable.hpp"

Moveable::Moveable()
:Vspeed(0.0f), Hspeed(0.0f)
{}

void Moveable::set
(sf::Vector2f p, sf::Vector2f s, Direction d)
{
	this->position = p;
	this->size = s;
	this->direction = d;
}

sf::Vector2f Moveable::calcNewPosition()
{
	sf::Vector2f newPos = this->position;
	auto dt = this->clock.getElapsedTime().asSeconds();
	
	newPos.x += this->Hspeed*dt;
	newPos.y += this->Vspeed*dt;

	this->clock.restart();
	
	return newPos;
}

void Moveable::updateDirections()
{
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




