#include "TextureManager.hpp"

sf::Font TextureManager::defaultFont;
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

}

void TextureManager::loadFonts()
{
	TextureManager::defaultFont.loadFromFile(this->defaultFontPath);
}

TextureManager::~TextureManager()
{
	--this->lifecount;
}
