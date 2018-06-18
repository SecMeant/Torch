#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../Scene.hpp"
#include "../../Player/Player.hpp"
#include "../../Level/Level.hpp"
#include "../../LightManager/LightManager.hpp"
#include "../../Object/Torch/OTorch.hpp"

#include "../../utility/complexTypes.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class GameScene:public Scene, public LightManager
{
public:
	// used to shift point (0,0) on screen to the middle
	static constexpr float defShiftx = 600;
	static constexpr float defShifty = 400;

private:
	Player player;
	Level level;

	bool currentFrameParity;

	virtual sceneID eventLoop() override;

	sceneID handleKeyPressed(const sf::Event &kev);

	void playerMoveIfValid();

	bool isMoveLegal(sf::Vector2f pos);

	/* DRAWING HELPER METHODS */
	void drawPlayer();
	void drawObjects();

	void placeTorch();
	void pickUp();

	void spawnLight(int32_t x, int32_t y);

	void renderFrame();
public:
	explicit GameScene(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // GAMESCENE_H
