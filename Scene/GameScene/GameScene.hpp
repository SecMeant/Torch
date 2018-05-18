#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../Scene.hpp"
#include "../../Player/Player.hpp"

#include "../../utility/complexTypes.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class GameScene:public Scene
{
private:
	Player player;
	virtual sceneID eventLoop() override;

public:
	explicit GameScene(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // GAMESCENE_H
