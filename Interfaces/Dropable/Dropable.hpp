#ifndef DROPABLE_H
#define DROPABLE_H

#include "../../utility/stdshared.hpp"

class Dropable
{
public:
	Dropable(const sf::Texture& tex);

	sf::Texture& texture; 
	void Drop();
};

#endif // DROPABLE_H
