#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "stdint.h"
#include <SFML/Graphics.hpp>

class TextureManager
{
private:
	// Prevents from creating more than one TextureManager
	static int32_t lifecount;

	inline void loadTextures();
	inline void loadFonts();
public:
	static sf::Font defaultFont;
	static sf::Texture nulltexture;
	static sf::Texture gamesceneBackground;
	static sf::Texture mainsceneBackground;
	static sf::Texture wizard;
	static sf::Texture light;
	static sf::Texture torch;
	static sf::Texture darkness;
	static sf::Texture wall;
	static sf::Texture box;
	static sf::Texture ground;
	static sf::Texture broom;
	static sf::Texture web;
	
	static constexpr const char *defaultFontPath
		= "./assets/font/orange_juice.ttf";

	static constexpr const char *nulltexPath
		= "./assets/nulltex.png";

	static constexpr const char *gamesceneBackgroundPath
		= "./assets/gamesceneBackground.png";

	static constexpr const char *mainsceneBackgroundPath
		= "./assets/mainsceneBackground.png";

	static constexpr const char *wizardPath
		= "./assets/player/wizard.png";

	static constexpr const char *lightPath
		= "./assets/light.png";

	static constexpr const char *torchPath
		= "./assets/torch.png";

	static constexpr const char *darknessPath
		= "./assets/darkness.png";

	static constexpr const char *wallPath
		= "./assets/map/wall.png";

	static constexpr const char *boxPath
		= "./assets/map/box.png";

	static constexpr const char *floorPath
		= "./assets/floor.png";

	static constexpr const char *broomPath
		= "./assets/broom.png";

	static constexpr const char *webPath
		= "./assets/web.png";

	TextureManager();
	~TextureManager();
};

#endif // TEXTUREMANAGER_H
