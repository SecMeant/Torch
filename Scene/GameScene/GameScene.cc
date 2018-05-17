#include "GameScene.hpp"

GameScene::GameScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd)
{
	puts("GAMESCENE CREATION MESSAGE");
	this->setBackground(TextureManager::gamesceneBackground);
}

sceneID GameScene::eventLoop()
{
	while (this->parentWindow->isOpen())
	{
		sf::Event event;
		while (this->parentWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->parentWindow->close();
			
			if (event.type == sf::Event::MouseButtonPressed)
				return {sceneID::mainmenu};

			// TODO event handling
		}

		this->parentWindow->clear();
		this->parentWindow->draw(this->background);
		this->parentWindow->display();
	}
	return {sceneID::none};
}

sceneID GameScene::switchScene()
{
	puts("Switching to GAMESCENE");

	// TODO
	// Some returning animation ?

	return this->eventLoop();
}
