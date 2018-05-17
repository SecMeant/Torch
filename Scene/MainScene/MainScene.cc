#include "MainScene.hpp"

MainScene::MainScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd)
{
	puts("MAINSCENE CREATION MESSAGE");
	this->setBackground(TextureManager::mainsceneBackground);
}

sceneID MainScene::eventLoop()
{
	while (this->parentWindow->isOpen())
	{
		sf::Event event;
		while (this->parentWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->parentWindow->close();
			
			if (event.type == sf::Event::MouseButtonPressed)
				return {sceneID::gamescene};

			// TODO event handling
		}

		this->parentWindow->clear();
		this->parentWindow->draw(this->background);
		this->parentWindow->display();
	}
	return {sceneID::none};
}

sceneID MainScene::switchScene()
{
	puts("Switching to MAINSCENE");

	// TODO
	// Some returning animation ?

	return this->eventLoop();
}
