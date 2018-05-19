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

			if(event.type == sf::Event::KeyPressed)
			{
				auto ret = this->handleKeyPressed(event);

				if(ret != sceneID::none)
					return ret;
			}

		}

		this->parentWindow->clear();
		this->parentWindow->draw(this->background);
		this->player.updatePosition();
		this->player.updateOrientation();
		this->player.draw(*parentWindow);
		this->parentWindow->display();
	}
	return {sceneID::none};
}

sceneID GameScene::handleKeyPressed
(const sf::Event &kev)
{
	sceneID ret = sceneID::none;
	switch(kev.key.code)
	{
		case sf::Keyboard::Up:
			this->player.direction = Direction::N;
			break;
		
		case sf::Keyboard::Left:
			this->player.direction = Direction::W;
			break;
	
		case sf::Keyboard::Right:
			this->player.direction = Direction::E;
			break;

		case sf::Keyboard::Down:
			this->player.direction = Direction::S;
			break;

		case sf::Keyboard::Space:
			this->player.playerSprite.currentAnimation
				= MotionSprite::spriteID::idle;
			this->player.stop();

		default:
			break;
	}

	return ret;
}

sceneID GameScene::switchScene()
{
	puts("Switching to GAMESCENE");

	// TODO
	// Some returning animation ?

	return this->eventLoop();
}
