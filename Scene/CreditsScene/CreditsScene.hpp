#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#include "../Scene.hpp"

#include "../../utility/stdshared.hpp"

class CreditsScene:public Scene
{
private:
	TextButton mainsceneTextBtn;

	void initializeButtons();
	void handleMouseHovers(const sf::Event &ev);
	sceneID handleMouseReleased(const sf::Event &ev);
	virtual sceneID eventLoop() override;

public:
	explicit CreditsScene(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // CREDITSSCENE_H
