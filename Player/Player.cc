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
	printf("%f %f\n", this->Moveable::position.first, this->Moveable::position.second);

	this->playerSprite.update();
	auto frame = this->playerSprite.getFrame();
	frame.setPosition(this->Moveable::position.first, this->Moveable::position.second);
	wnd.draw(frame);
	return;
}
