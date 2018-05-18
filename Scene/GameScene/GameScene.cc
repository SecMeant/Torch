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
			//this->player.direction = Direction::N;
			this->player.playerSprite.currentAnimation
				= MotionSprite::spriteID::idle;
			this->player.move(0.0f, -3.0f);
			break;
		
		case sf::Keyboard::Left:
			this->player.direction = Direction::W;
			this->player.playerSprite.currentAnimation
				= MotionSprite::spriteID::moveHorizontal;
			this->player.move(-3.0f, 0.0f);
			break;
	
		case sf::Keyboard::Right:
			this->player.direction = Direction::E;
			this->player.playerSprite.currentAnimation
				= MotionSprite::spriteID::moveHorizontal;
			this->player.move(3.0f, 0.0f);
			break;

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
