#ifndef MOTIONSPRITE_H
#define MOTIONSPRITE_H

#include "../../../utility/stdshared.hpp"

#include "../DynamicSprite.hpp"

#include <array>

class MotionSprite
{
public:
	enum spriteID: int32_t
	{
		idle = 0,
		moveHorizontal = 1,
		moveVertical = 2
	};

	spriteID currentAnimation;
private:
	std::array<DynamicSprite,3> animations;
	
	// Initialized with objects diretion
	const Direction& direction;

public:
	explicit MotionSprite(const Direction &d);

	/* Setters for initializing animations for differenet motion states */
	void setIdleAnimation
	(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
	 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown);

	void setMoveHorizontalAnimation
	(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
	 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown);

	void setMoveVerticalAnimation
	(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
	 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown);

	// applies rotation according ro movement direction
	void applyRotation();

	// Updates state of animation to sprite
	void update();
	sf::Sprite& getFrame();
};

#endif // MOTIONSPRITE_H
