#include "Player.hpp"

Player::Player()
:LightSource(&this->position.x, &this->position.y, 120.0f),
 torch(TextureManager::torch, 0, 0, 9, 15, 3, 0.25f),
 light(TextureManager::light, 0, 0, 40, 40, 5, 0.25f, 3, 3),
 broom(TextureManager::broom, 0, 0, 60, 60, 6, 0.05f, 0.8f, 0.8f),
 playerSprite(this->direction),
 torchCount(5)
{
	this->Moveable::set({0,0}, {16,22}, Direction::N);
	this->playerSprite.setIdleAnimation
		(TextureManager::wizard, 16, 24, 16, 22, 2, 0.75f);
	this->playerSprite.setMoveVerticalAnimation
		(TextureManager::wizard, 0, 47, 16, 22, 4, 0.07f);
	this->playerSprite.setMoveHorizontalAnimation
		(TextureManager::wizard, 0, 47, 16, 22, 4, 0.07f);
}

void Player::scaleLightRadius(float scaleFactor)
{
	this->radius *= scaleFactor;
	this->light.scaleSprite(1.5f);
}

void Player::updateOrientation()
{
	if (this->Moveable::Hspeed == 0 && this->Moveable::Vspeed == 0)
	{
		this->playerSprite.currentAnimation = MotionSprite::spriteID::idle;
		return;
	}

	if (this->Moveable::Vspeed != 0)
	{
		if (this->Moveable::Vspeed > 0)
			this->direction = Direction::S;
		else
			this->direction = Direction::N;

		this->playerSprite.currentAnimation
			= MotionSprite::spriteID::moveVertical;
	}

	if (this->Moveable::Hspeed > 0)
		this->direction = Direction::E;
	else
		this->direction = Direction::W;

	// At this point Hspeed must be != 0, no need to check it
	this->playerSprite.currentAnimation
		= MotionSprite::spriteID::moveHorizontal;
}
