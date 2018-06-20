#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "../Scene.hpp"
#include "../../TextureManager/DynamicSprite/DynamicSprite.hpp"

#include "../../utility/complexTypes.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class MainScene:public Scene
{
private:
	TextButton gamesceneTextBtn;
	TextButton creditsTextBtn;

	DynamicSprite torch;

	void initializeButtons();
	void handleMouseHovers(const sf::Event &ev);
	void drawTorch();
	sceneID handleMouseReleased(const sf::Event &ev);
	virtual sceneID eventLoop() override;

public:
	explicit MainScene(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // MAINSCENE_H
