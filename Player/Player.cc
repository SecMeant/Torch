#include "Player.hpp"

Player::Player()
:torch(TextureManager::torch, 0, 0, 9, 15, 3, 0.25f),
 light(TextureManager::light, 0, 0, 40, 40, 5, 0.25f, 2, 2),
 playerSprite(this->direction)
{
	this->Moveable::set({300,300}, Direction::N);
	this->playerSprite.setIdleAnimation
		(TextureManager::wizard, 16, 24, 16, 22, 2, 0.75f);
	this->playerSprite.setMoveVerticalAnimation
		(TextureManager::wizard, 0, 47, 16, 22, 4, 0.1f);
	this->playerSprite.setMoveHorizontalAnimation
		(TextureManager::wizard, 0, 47, 16, 22, 4, 0.1f);
}

void Player::updateDirection()
{
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

void Player::draw
(sf::RenderWindow &wnd) const
{
	this->torch.update();
	this->light.update();
	this->playerSprite.update();

	// Drawing light texture
	auto frame = this->light.getFrame();
	frame.setPosition(this->Moveable::position.first - 6,
			              this->Moveable::position.second + 15 /* Bottom texture offset */);
	wnd.draw(frame);

	if (this->Moveable::direction == Direction::W)
	{
		// Drawing torch texture
		frame = this->torch.getFrame();
		frame.setPosition(this->Moveable::position.first - 6,
											this->Moveable::position.second - 8);
		wnd.draw(frame);

		// Drawing player texture
		frame = this->playerSprite.getFrame();
		frame.setPosition(this->Moveable::position.first, this->Moveable::position.second);
		wnd.draw(frame);
	}
	else
	{
		// Drawing player texture
		frame = this->playerSprite.getFrame();
		frame.setPosition(this->Moveable::position.first, this->Moveable::position.second);
		wnd.draw(frame);

		// Drawing torch texture
		frame = this->torch.getFrame();
		frame.setPosition(this->Moveable::position.first - 6,
											this->Moveable::position.second - 6);
		wnd.draw(frame);
	}

	return;
}
