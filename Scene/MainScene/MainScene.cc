#include "MainScene.hpp"

MainScene::MainScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd), gamesceneTextBtn(TextureManager::defaultFont, {0,0,0}, {255,255,255})
{
	puts("MAINSCENE CREATION MESSAGE");
	this->initializeButtons();
	this->setBackground(TextureManager::mainsceneBackground);
}

void MainScene::initializeButtons()
{
	this->gamesceneTextBtn.text.setPosition(50,500);
	this->gamesceneTextBtn.text.setString("Game Scene");
}

void MainScene::handleMouseHovers
(const sf::Event &ev)
{
	this->gamesceneTextBtn.handleHoverEvent(ev);
}

sceneID MainScene::handleMouseReleased
(const sf::Event &ev)
{
	sceneID ret = sceneID::none;

	if(this->gamesceneTextBtn.clicked(ev))
		ret = sceneID::gamescene;

	return ret;
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
			
			if (event.type == sf::Event::MouseButtonReleased)
			{
				auto ret = this->handleMouseReleased(event);
				if(ret != sceneID::none)
					return ret;
			}
		
			if (event.type == sf::Event::MouseMoved)
				this->handleMouseHovers(event);

			// TODO event handling
		}

		this->parentWindow->clear();
		this->parentWindow->draw(this->background);
		this->parentWindow->draw(this->gamesceneTextBtn.text);
		this->parentWindow->display();
	}
	return {sceneID::none};
}

sceneID MainScene::switchScene()
{
	puts("Switching to MAINSCENE");

	this->gamesceneTextBtn.reset();

	// TODO
	// Some returning animation ?

	return this->eventLoop();
}
