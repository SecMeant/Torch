#include "TextureManager.hpp"

sf::Font TextureManager::defaultFont;
sf::Texture TextureManager::nulltexture;
sf::Texture TextureManager::gamesceneBackground;
sf::Texture TextureManager::mainsceneBackground;
sf::Texture TextureManager::wizard;
sf::Texture TextureManager::light;
sf::Texture TextureManager::torch;
sf::Texture TextureManager::darkness;
sf::Texture TextureManager::wall;
sf::Texture TextureManager::box;
sf::Texture TextureManager::ground;
sf::Texture TextureManager::broom;

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
	TextureManager::nulltexture.loadFromFile(this->nulltexPath);
	TextureManager::gamesceneBackground.loadFromFile(this->gamesceneBackgroundPath);
	TextureManager::mainsceneBackground.loadFromFile(this->mainsceneBackgroundPath);
	TextureManager::wizard.loadFromFile(this->wizardPath);
	TextureManager::light.loadFromFile(this->lightPath);
	TextureManager::torch.loadFromFile(this->torchPath);
	TextureManager::darkness.loadFromFile(this->darknessPath);
	TextureManager::wall.loadFromFile(this->wallPath);
	TextureManager::box.loadFromFile(this->boxPath);
	TextureManager::ground.loadFromFile(this->floorPath);
	TextureManager::broom.loadFromFile(this->broomPath);
}

void TextureManager::loadFonts()
{
	TextureManager::defaultFont.loadFromFile(this->defaultFontPath);
}

TextureManager::~TextureManager()
{
	--this->lifecount;
}
