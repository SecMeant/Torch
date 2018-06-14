#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include "../utility/stdshared.hpp"

class Object
{
public:
	enum class Type
	{
		Wall, Box, Ground, Torch
	}type;

	static constexpr float defPosX = 13371377.0f;
	static constexpr float defPosY = defPosX;

	sf::Texture* texture;
	sf::Vector2f position;
	sf::Vector2f size;

	// True if object should blocks movement
	// False otherwise
	bool isBlocking;

	Object(Type t)
	:type(t), texture(&TextureManager::nulltexture),
	 position({defPosX,defPosY}), isBlocking(false){}

	Object(Type t, sf::Texture* tex, sf::Vector2f pos={0,0},
			   sf::Vector2f s={32,32}, bool isblocking = false)
	:type(t), texture(tex), position(pos), size(s), isBlocking(isblocking)
	{}

	virtual void use();
	virtual void drop();
	virtual void pickup();

	sf::FloatRect getObjectRange() const;
	sf::Vector2f getObjectCoords() const;

	virtual ~Object() = default;
};

#endif // OBJECT_H
