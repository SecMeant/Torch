#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../Scene.hpp"
#include "../../Player/Player.hpp"
#include "../../Level/Level.hpp"

#include "../../utility/complexTypes.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class GameScene:public Scene
{
private:
	Player player;
	Level level;
	virtual sceneID eventLoop() override;

	sceneID handleKeyPressed(const sf::Event &kev);

	void drawPlayer();
public:
	explicit GameScene(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // GAMESCENE_H
