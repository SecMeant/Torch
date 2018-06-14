#include "GameScene.hpp"

GameScene::GameScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd), LightManager(wnd->getSize())
{
	puts("GAMESCENE CREATION MESSAGE");
	this->setBackground(TextureManager::gamesceneBackground);

	this->level.loadMap("./Level/mapfiles/test.map",
			                static_cast<LightManager *>(this));

	this->player.position.x = 50;
	this->player.position.y = 50;
	this->LightManager::registerLightSource(static_cast<LightSource*>(&this->player));
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
				static_cast<void> (1337); // nop

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
		this->LightManager::applyDarkness(*this->parentWindow,
			this->player.position.x - this->defShiftx,
			this->player.position.y - this->defShifty);
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

		case sf::Keyboard::LControl:
			this->pickUp();
			break;

		case sf::Keyboard::Space:
			this->placeTorch();
			break;

		case sf::Keyboard::Escape:
			ret = sceneID::mainmenu;
			break;

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
	// Convert to tile coords
	pos.x = pos.x/32.0;
	pos.y = (pos.y+16)/32.0; // 16 is legs offset

	// Player came to new tile in width
	if(this->player.position.x/32.0 != pos.x)
	{
		if(this->level.getObject(pos.x, pos.y)->isBlocking)
			return false;
	}

	// Player came to new tile in height
	if((this->player.position.y)/32.0 != pos.y)
	{
		if(this->level.getObject(pos.x, pos.y)->isBlocking)
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
		posx  = obj->position.x;
		posx -= this->player.position.x;
		posx += this->defShiftx;

		float posy;
		posy = obj->position.y;
		posy -= this->player.position.y;
		posy += this->defShifty;

		for(const auto light:this->LightManager::getLightSources())
		{
			if(light->isInRadius(*obj))
			{
				sprite.setTexture(*obj->texture);
				sprite.setPosition(posx, posy);
				this->parentWindow->draw(sprite);
			}
		}
	}
}

sceneID GameScene::switchScene()
{
	puts("Switching to GAMESCENE");

	for(LightSource* plight: this->getLightSources())
	{
		printf("LIGHT: %f %f %f\n",
				*(plight->posx), *(plight->posy), plight->radius);
	}

	return this->eventLoop();
}

void GameScene::placeTorch()
{
	int32_t x = (int32_t)this->player.position.x / 32;
	int32_t y = (int32_t)this->player.position.y / 32;
	Object* obj = this->level.getObject(x,y);

	if(obj->type != Object::Type::Ground)
		return;

	if(this->player.torchCount > 0)
	{
		this->level.spawnLight(x,y,static_cast<LightManager*>(this));
		--this->player.torchCount;
	}

	printf("Torch count: %u\n",this->player.torchCount);
}

void GameScene::pickUp()
{
	int32_t x = this->player.position.x;
	int32_t y = this->player.position.y;

	x /= 32;
	y /= 32;

	printf("Pickup at %u %u\n",x,y);
	Object* obj = this->level.getObject(x,y);
	
	if(obj == nullptr || obj->type != Object::Type::Torch)
		return;
	
	this->removeLightSource(static_cast<LightSource*>(dynamic_cast<OTorch*>(obj)));
	this->level.insertObject(x,y,new Object(Object::Type::Ground,&TextureManager::ground,
		{(float)x*Level::defaultTileWidth,(float)y*Level::defaultTileHeight}));

	this->player.torchCount++;
	printf("Torch count: %u\n", this->player.torchCount);
}
