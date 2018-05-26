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
public:
	// used to shift point (0,0) on screen to the middle
	static constexpr float defShiftx = 400;
	static constexpr float defShifty = 400;

private:
	Player player;
	Level level;
	virtual sceneID eventLoop() override;

	sceneID handleKeyPressed(const sf::Event &kev);

	void playerMoveIfValid();

	bool isMoveLegal(sf::Vector2f pos);

	/* DRAWING HELPER METHODS */
	void drawPlayer();
	void drawObjects();
public:
	explicit GameScene(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // GAMESCENE_H
