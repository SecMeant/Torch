#include "DynamicSprite.hpp"

DynamicSprite::DynamicSprite
(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cd)
{
	this->texFileOffset = {offsetX, offsetY};
	this->texSize = {tWidth, tHeight};
	this->animPhaseNumber = numberOfFrames;
	this->animPhase = 0;
	this->cooldown = cd;
	this->currentFrame.setTexture(tex);
	this->currentFrame.setTextureRect
		(sf::IntRect(offsetX, offsetY, tWidth,tHeight));
	this->currentFrame.setPosition(300,300);

	this->clock.restart();
}

void DynamicSprite::update()
{
	if (this->clock.getElapsedTime().asSeconds() > this->cooldown)
	{
		this->clock.restart();
		this->animPhase++;

		if (this->animPhase == this->animPhaseNumber)
			this->animPhase = 0;

		this->currentFrame.setTextureRect(sf::IntRect
		(this->texFileOffset.first + this->texSize.first * this->animPhase,
		 this->texFileOffset.second, this->texSize.first, this->texSize.second));
		this->currentFrame.setScale(2,2);
	}
}

sf::Sprite& DynamicSprite::getFrame()
{
	return this->currentFrame;
}
