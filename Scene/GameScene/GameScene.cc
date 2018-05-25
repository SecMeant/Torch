#include "GameScene.hpp"

GameScene::GameScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd)
{
	puts("GAMESCENE CREATION MESSAGE");
	this->setBackground(TextureManager::gamesceneBackground);

	this->level.loadMap("./Level/mapfiles/test.map");
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
		this->level.drawAll(*parentWindow);
		this->player.updatePosition();
		this->player.updateOrientation();
		this->drawPlayer();
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

void GameScene::drawPlayer()
{
	this->player.torch.update();
	this->player.light.update();
	this->player.playerSprite.update();

	// Drawing light texture
	auto frame = this->player.light.getFrame();
	frame.setPosition(this->player.defaultPosition.first - 6,
			              this->player.defaultPosition.second + 15 /* Bottom texture offset */);
	this->parentWindow->draw(frame);

	if (this->player.Moveable::direction == Direction::W)
	{
		// Drawing torch texture
		frame = this->player.torch.getFrame();
		frame.setPosition(this->player.defaultPosition.first - 6,
											this->player.defaultPosition.second - 8);
		this->parentWindow->draw(frame);

		// Drawing player texture
		frame = this->player.playerSprite.getFrame();
		frame.setPosition(this->player.defaultPosition.first,
				              this->player.defaultPosition.second);
		this->parentWindow->draw(frame);
	}
	else
	{
		// Drawing player texture
		frame = this->player.playerSprite.getFrame();
		frame.setPosition(this->player.defaultPosition.first,
				              this->player.defaultPosition.second);
		this->parentWindow->draw(frame);

		// Drawing torch texture
		frame = this->player.torch.getFrame();
		frame.setPosition(this->player.defaultPosition.first - 6,
											this->player.defaultPosition.second - 6);
		this->parentWindow->draw(frame);
	}

	return;
}

sceneID GameScene::switchScene()
{
	puts("Switching to GAMESCENE");

	this->level.printObjects();

	return this->eventLoop();
}
