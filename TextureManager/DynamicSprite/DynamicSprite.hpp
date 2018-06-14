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
	float scaleFactorX;
	float scaleFactorY;

public:
	sf::Sprite currentFrame;

	// Holds value which tells if texture is
	// flipped horizontally
	bool isFlipped;

	DynamicSprite();

	DynamicSprite
	(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
	 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown,
	 float scaleFactorX = 2.0f, float scaleFactorY = 2.0f);

	void scaleSprite(float scaleFactor);
	
	void update();
	
	// If any dynamicsprite have some custom rendering this
	// method should be overriden and return proper, custom rendred
	// sprite
	virtual sf::Sprite& getFrame();
};

#endif // DYNAMICSPRITE_H
