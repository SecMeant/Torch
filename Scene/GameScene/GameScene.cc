#include "GameScene.hpp"

GameScene::GameScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd)
{
	puts("GAMESCENE CREATION MESSAGE");
	this->setBackground(TextureManager::gamesceneBackground);

	this->level.loadMap("./Level/mapfiles/test.map");

	this->player.position.x = 50;
	this->player.position.y = 50;
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
		this->drawObjects();
		this->playerMoveIfValid();
		this->player.updateDirections();
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

void GameScene::playerMoveIfValid()
{
	sf::Vector2f newPos = this->player.calcNewPosition();
	if(this->isMoveLegal(newPos))
	{
		this->player.position = newPos;
	}
}

bool GameScene::isMoveLegal(sf::Vector2f pos)
{
	sf::FloatRect newRect(pos, {16,22});

	for(const auto& obj:this->level.getObjects())
	{
		if(newRect.intersects(obj.getObjectRange()))
			return false;
	}

	return true;
}

void GameScene::drawPlayer()
{
	this->player.torch.update();
	this->player.light.update();
	this->player.playerSprite.update();

	// Drawing light texture
	auto frame = this->player.light.getFrame();
	frame.setPosition(this->defShiftx - 6,
			              this->defShifty + 15/* Bottom texture offset */);
	this->parentWindow->draw(frame);

	if (this->player.Moveable::direction == Direction::W)
	{
		// Drawing torch texture
		frame = this->player.torch.getFrame();
		frame.setPosition(this->defShiftx - 6,
											this->defShifty - 8);
		this->parentWindow->draw(frame);

		// Drawing player texture
		frame = this->player.playerSprite.getFrame();
		frame.setPosition(this->defShiftx,
				              this->defShifty);
		this->parentWindow->draw(frame);
	}
	else
	{
		// Drawing player texture
		frame = this->player.playerSprite.getFrame();
		frame.setPosition(this->defShiftx,
				              this->defShifty);
		this->parentWindow->draw(frame);

		// Drawing torch texture
		frame = this->player.torch.getFrame();
		frame.setPosition(this->defShiftx - 6,
											this->defShifty - 6);
		this->parentWindow->draw(frame);
	}

	return;
}

void GameScene::drawObjects()
{
	sf::Sprite sprite;

	for(const auto& obj:this->level.getObjects())
	{
		float posx;
		posx  = obj.x*this->level.defaultTileWidth;
		posx -= this->player.position.x;
		posx += this->defShiftx;

		float posy;
		posy = obj.y*this->level.defaultTileHeight;
		posy -= this->player.position.y;
		posy += this->defShifty;

		if(not this->player.isInRadius(obj))
			continue;

		if(obj.id == 0)
		{
			sprite.setTexture(TextureManager::wall);
			sprite.setPosition(posx, posy);
			this->parentWindow->draw(sprite);
		}
		else if(obj.id == 1)
		{
			sprite.setTexture(TextureManager::box);
			sprite.setPosition(posx, posy);
			this->parentWindow->draw(sprite);
		}
	}
}

sceneID GameScene::switchScene()
{
	puts("Switching to GAMESCENE");
	
	return this->eventLoop();
}
