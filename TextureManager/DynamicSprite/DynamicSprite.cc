#include "DynamicSprite.hpp"

DynamicSprite::DynamicSprite()
{
	this->currentFrame.setOrigin(this->texSize.first/2.0f, this->texSize.second/2.0f);
}

DynamicSprite::DynamicSprite
(const sf::Texture &tex, int32_t offsetX, int32_t offsetY,
 int32_t tWidth, int32_t tHeight, int32_t numberOfFrames, float cd,
 float sfx, float sfy)
{
	this->texFileOffset = {offsetX, offsetY};
	this->texSize = {tWidth, tHeight};
	this->animPhaseNumber = numberOfFrames;
	this->animPhase = 0;
	this->cooldown = cd;
	this->scaleFactorX = sfx;
	this->scaleFactorY = sfy;
	this->currentFrame.setTexture(tex);
	this->currentFrame.setTextureRect
		(sf::IntRect(offsetX, offsetY, tWidth,tHeight));
	this->currentFrame.setPosition(300,300);
	this->currentFrame.scale(scaleFactorX, scaleFactorY);
	this->currentFrame.setOrigin(this->texSize.first/2.0f, this->texSize.second/2.0f);

	this->clock.restart();
}

void DynamicSprite::scaleSprite(float scaleFactor)
{
	this->scaleFactorX*=scaleFactor;
	this->scaleFactorY*=scaleFactor;
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
	}
}

sf::Sprite& DynamicSprite::getFrame()
{
	if(this->isFlipped)
		this->currentFrame.setScale(this->scaleFactorX*(-1),this->scaleFactorY);
	else
		this->currentFrame.setScale(this->scaleFactorX,this->scaleFactorY);

	return this->currentFrame;
}
