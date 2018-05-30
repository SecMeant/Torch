#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include "../utility/stdshared.hpp"

class Object
{
public:
	sf::Texture* texture;
	sf::Vector2f position;
	sf::Vector2f size;

	Object():texture(&TextureManager::nulltexture){}
	Object(sf::Texture* tex, sf::Vector2f pos={0,0},
			   sf::Vector2f s={32,32})
	:texture(tex), position(pos), size(s){}

	virtual void use();
	virtual void drop();
	virtual void pickup();

	sf::FloatRect getObjectRange() const;
	sf::Vector2f getObjectCoords() const;
};

#endif // OBJECT_H
