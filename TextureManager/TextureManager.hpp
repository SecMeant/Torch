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

	static constexpr const char *defaultFontPath
		= "./assets/font/orange_juice.ttf";

	TextureManager();
	~TextureManager();
};

#endif // TEXTUREMANAGER_H
