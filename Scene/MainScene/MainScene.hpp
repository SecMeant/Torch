#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "../Scene.hpp"

#include "../../utility/complexTypes.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class MainScene:public Scene
{
private:
	TextButton gamesceneTextBtn;

	void initializeButtons();
	void handleMouseHovers(const sf::Event &ev);
	sceneID handleMouseReleased(const sf::Event &ev);
	virtual sceneID eventLoop() override;

public:
	explicit MainScene(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // MAINSCENE_H
