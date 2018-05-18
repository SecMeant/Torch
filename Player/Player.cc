#include "Player.hpp"

Player::Player()
:playerSprite(this->direction)
{
	this->Moveable::set({300,300}, Direction::N);
	this->playerSprite.setIdleAnimation
		(TextureManager::wizard_idle, 0, 24,16,22, 4, 0.15f);
	this->playerSprite.setMoveVerticalAnimation
		(TextureManager::wizard_idle, 0, 47,16,22, 4, 0.1f);
	this->playerSprite.setMoveHorizontalAnimation
		(TextureManager::wizard_idle, 0, 47,16,22, 4, 0.1f);
}

void Player::draw
(sf::RenderWindow &wnd) const
{
	this->playerSprite.update();
	wnd.draw(this->playerSprite.getFrame());
	return;
}
