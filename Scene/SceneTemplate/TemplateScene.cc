#include "TemplateScene.hpp"

TEMPLATESCENE::TEMPLATESCENE(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd)
{
	puts("TEMPLATE SCENE CREATION MESSAGE");
	this->background.assetPath = "./assets/default-background.png";
	this->initializeBackground();
}

sceneID TEMPLATESCENE::eventLoop()
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
		this->parentWindow->draw(this->background.shape);
		this->parentWindow->display();
	}
	return {sceneID::none};
}

sceneID TEMPLATESCENE::switchScene()
{
	puts("Switching to TEMPLATE SCENE");

	// TODO
	// Some returning animation ?

	return this->eventLoop();
}
