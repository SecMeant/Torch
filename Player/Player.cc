#include "Player.hpp"

Player::Player()
:playerSprite(this->direction)
{
	this->Moveable::set({300,300}, Direction::N);
	this->playerSprite.setIdleAnimation
		(TextureManager::wizard, 16, 24, 16, 22, 2, 0.75f);
	this->playerSprite.setMoveVerticalAnimation
		(TextureManager::wizard, 0, 47, 16, 22, 4, 0.1f);
	this->playerSprite.setMoveHorizontalAnimation
		(TextureManager::wizard, 0, 47, 16, 22, 4, 0.1f);
}

void Player::draw
(sf::RenderWindow &wnd) const
{
	this->playerSprite.update();
	auto frame = this->playerSprite.getFrame();
	frame.setPosition(this->Moveable::position.first, this->Moveable::position.second);
	wnd.draw(frame);
	return;
}
