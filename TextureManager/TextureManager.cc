#include "TextureManager.hpp"

sf::Font TextureManager::defaultFont;
sf::Texture TextureManager::gamesceneBackground;
sf::Texture TextureManager::mainsceneBackground;
sf::Texture TextureManager::wizard_idle;

int32_t TextureManager::lifecount = 0;

TextureManager::TextureManager()
{
	if(this->lifecount > 0)
		return;

	++lifecount;

	this->loadTextures();
	this->loadFonts();
}

void TextureManager::loadTextures()
{
	TextureManager::gamesceneBackground.loadFromFile(this->gamesceneBackgroundPath);
	TextureManager::mainsceneBackground.loadFromFile(this->mainsceneBackgroundPath);
	TextureManager::wizard_idle.loadFromFile(this->wizard_idlePath);
}

void TextureManager::loadFonts()
{
	TextureManager::defaultFont.loadFromFile(this->defaultFontPath);
}

TextureManager::~TextureManager()
{
	--this->lifecount;
}
