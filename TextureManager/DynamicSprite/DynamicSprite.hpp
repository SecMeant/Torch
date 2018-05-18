#ifndef DYNAMICSPRITE_H
#define DYNAMICSPRITE_H

#include "../../utility/stdshared.hpp"

class DynamicSprite
{
public:
	typedef std::pair<int32_t, int32_t> CoordType;
	typedef std::pair<int32_t, int32_t> SizeType;

private:
	sf::Clock clock;
	int32_t animPhase;
	
	CoordType texFileOffset;
	SizeType texSize;
	int32_t animPhaseNumber;
	float cooldown;
	sf::Sprite currentFrame;

public:
	DynamicSprite
	(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
	 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown);
	
	void update();
	sf::Sprite& getFrame();
};

#endif // DYNAMICSPRITE_H
