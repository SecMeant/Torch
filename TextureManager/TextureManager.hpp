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
	static sf::Texture gamesceneBackground;
	static sf::Texture mainsceneBackground;
	static sf::Texture wizard_idle;

	static constexpr const char *defaultFontPath
		= "./assets/font/orange_juice.ttf";

	static constexpr const char *gamesceneBackgroundPath
		= "./assets/gamesceneBackground.png";

	static constexpr const char *mainsceneBackgroundPath
		= "./assets/mainsceneBackground.png";

	static constexpr const char *wizard_idlePath
		= "./assets/player/wizard-idle.png";

	TextureManager();
	~TextureManager();
};

#endif // TEXTUREMANAGER_H
