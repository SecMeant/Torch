#include "MainScene.hpp"

MainScene::MainScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd), gamesceneTextBtn(TextureManager::defaultFont,{170,170,170},{255,255,255})
 ,creditsTextBtn(TextureManager::defaultFont,{170,170,170},{255,255,255}),
 torch(TextureManager::torch, 0, 0, 9, 15, 3, 0.15f, 20.0f, 20.0f)
{
	puts("MAINSCENE CREATION MESSAGE");
	this->initializeButtons();
	this->setBackground(TextureManager::mainsceneBackground);
}

void MainScene::initializeButtons()
{
	this->gamesceneTextBtn.text.setPosition(260,150);
	this->gamesceneTextBtn.text.setCharacterSize(48);
	this->gamesceneTextBtn.text.setString("Play");

	this->creditsTextBtn.text.setPosition(230,230);
	this->creditsTextBtn.text.setCharacterSize(48);
	this->creditsTextBtn.text.setString("Controls");
}

void MainScene::handleMouseHovers
(const sf::Event &ev)
{
	this->gamesceneTextBtn.handleHoverEvent(ev);
	this->creditsTextBtn.handleHoverEvent(ev);
}

sceneID MainScene::handleMouseReleased
(const sf::Event &ev)
{
	sceneID ret = sceneID::none;

	if(this->gamesceneTextBtn.clicked(ev))
		ret = sceneID::gamescene;

	if(this->creditsTextBtn.clicked(ev))
		ret = sceneID::credits;

	return ret;
}

void MainScene::drawTorch()
{
	sf::Sprite *sprite;
	this->torch.update();
	sprite = &this->torch.getFrame();
	sprite->setPosition(930,460);
	this->parentWindow->draw(*sprite);
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
		this->parentWindow->draw(this->creditsTextBtn.text);
		this->drawTorch();
		this->parentWindow->display();
	}
	return {sceneID::none};
}

sceneID MainScene::switchScene()
{
	puts("Switching to MAINSCENE");

	this->gamesceneTextBtn.reset();
	this->creditsTextBtn.reset();

	return this->eventLoop();
}
