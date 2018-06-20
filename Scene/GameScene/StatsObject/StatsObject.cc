#include "StatsObject.hpp"

StatsObject::StatsObject(int32_t val, DynamicSprite &&tex, sf::Vector2f pos)
:value(val),texture(tex),position(pos)
{
	this->text.setFont(TextureManager::defaultFont);
	this->text.setPosition(this->position.x+20,this->position.y-20);
	this->text.setColor(sf::Color::White);
	this->text.setCharacterSize(32);
}

void StatsObject::draw(sf::RenderWindow &wnd)
{
	sf::Sprite *sprite;

	// Texture drawing
	this->texture.update();
	sprite = &this->texture.getFrame();
	sprite->setPosition(this->position);
	wnd.draw(*sprite);

	// Text drawing
	this->text.setString(std::to_string(value));
	wnd.draw(this->text);
}

