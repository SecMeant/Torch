#include "Player.hpp"

Player::Player()
:playerSprite(TextureManager::wizard_idle, 0, 47,16,22, 4, 0.1f)
{
	this->Moveable::set({300,300}, Direction::N);
}

void Player::draw
(sf::RenderWindow &wnd) const
{
	this->playerSprite.update();
	wnd.draw(this->playerSprite.getFrame());
	return;
}
