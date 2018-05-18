#include "MotionSprite.hpp"

MotionSprite::MotionSprite
(const Direction &d)
:currentAnimation(spriteID::idle), animations(), direction(d)
{}

void MotionSprite::setIdleAnimation
(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown)
{
	DynamicSprite ds(tex, offsetX, offsetY, tWidth, tHeight, numberOfFrames, cooldown);
	ds.currentFrame.setOrigin(tWidth/2.0f, tHeight/2.0f);
	this->animations[spriteID::idle] = ds;
}

void MotionSprite::setMoveHorizontalAnimation
(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown)
{
	DynamicSprite ds(tex, offsetX, offsetY, tWidth, tHeight, numberOfFrames, cooldown);
	ds.currentFrame.setOrigin(tWidth/2.0f, tHeight/2.0f);
	this->animations[spriteID::moveHorizontal] = ds;
}

void MotionSprite::setMoveVerticalAnimation
(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cooldown)
{
	DynamicSprite ds(tex, offsetX, offsetY, tWidth, tHeight, numberOfFrames, cooldown);
	ds.currentFrame.setOrigin(tWidth/2.0f, tHeight/2.0f);
	this->animations[spriteID::moveVertical] = ds;
}

void MotionSprite::applyRotation()
{
	if(this->direction == Direction::W)
		this->animations[this->currentAnimation].currentFrame.setScale(-2.0f,2.0f);
	else
		this->animations[this->currentAnimation].currentFrame.setScale(2.0f,2.0f);
}

void MotionSprite::update()
{
	this->animations[this->currentAnimation].update();
}

sf::Sprite& MotionSprite::getFrame()
{
	this->applyRotation();
	return this->animations[this->currentAnimation].getFrame();
}



