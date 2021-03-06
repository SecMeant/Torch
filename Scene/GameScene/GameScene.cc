#include "GameScene.hpp"

GameScene::GameScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd), LightManager(wnd->getSize()),
 torchState(10,DynamicSprite(TextureManager::torch,0,0,9,15,3,0.25f),{15,20}),
 webState(0,DynamicSprite(TextureManager::web,0,0,32,32,1,0.25f,1.0f,1.0f),{15,60}),
 smoothDarkness(false), currentFrameParity(0)
{
	puts("GAMESCENE CREATION MESSAGE");
	this->setBackground(TextureManager::gamesceneBackground);

	this->level.loadMap("./Level/mapfiles/test.map",
			                static_cast<LightManager *>(this));

	this->player.position.x = 50;
	this->player.position.y = 50;
	this->LightManager::registerLightSource(static_cast<LightSource*>(&this->player));

	srand(time(NULL));
	this->clock.restart();
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
		this->checkLogic();
		this->renderFrame();
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

		case sf::Keyboard::F1:
			this->smoothDarkness = !this->smoothDarkness;
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
		if(this->level.getMapObject(pos.x, pos.y)->isBlocking)
			return false;
	}

	// Player came to new tile in height
	if((this->player.position.y)/32.0 != pos.y)
	{
		if(this->level.getMapObject(pos.x, pos.y)->isBlocking)
			return false;
	}
	
	return true;
}

void GameScene::drawPlayer()
{
	this->player.torch.update();
	this->player.light.update();
	this->player.broom.update();
	this->player.playerSprite.update();

	// Drawing light texture
	auto frame = this->player.light.getFrame();
	frame.setPosition(this->defShiftx - 6,
			              this->defShifty + 15/* Bottom texture offset */);
	this->parentWindow->draw(frame);

	if (this->player.Moveable::direction == Direction::W)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			// Drawing broom texture
			frame = this->player.broom.getFrame();
			frame.setPosition(this->defShiftx,
												this->defShifty + 10);
			this->parentWindow->draw(frame);
		}
		else
		{
			// Drawing torch texture
			frame = this->player.torch.getFrame();
			frame.setPosition(this->defShiftx - 6,
												this->defShifty - 8);
			this->parentWindow->draw(frame);
		}

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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			// Drawing broom texture
			frame = this->player.broom.getFrame();
			frame.setPosition(this->defShiftx,
												this->defShifty + 10);
			this->parentWindow->draw(frame);
		}
		else
		{
			// Drawing torch texture
			frame = this->player.torch.getFrame();
			frame.setPosition(this->defShiftx - 6,
												this->defShifty - 8);
			this->parentWindow->draw(frame);
		}
	}

	return;
}

void GameScene::drawObjects()
{
	sf::Sprite sprite;
	
	for(const auto light:this->LightManager::getLightSources())
	{
		int32_t xbegin = (int32_t)(*light->posx/32.0f);
		int32_t ybegin = (int32_t)(*light->posy/32.0f);
		int32_t xend = xbegin + light->getTileRadius()+5;
		int32_t yend = ybegin + light->getTileRadius()+5;
		int32_t x;
		int32_t y;
		Object* obj;
		DynamicObject* dobj;

		xbegin -= light->getTileRadius()+5;
		ybegin -= light->getTileRadius()+5;
		x = xbegin;
		y = ybegin;
		
		float posx;
		float posy;

		while(y <= yend)
		{
			if(x == xend)
			{
				x = xbegin;
				++y;
			}
			
			obj = this->level.getMapObject(x,y);
			if(obj != nullptr)
			{
				// already drawn
				if(obj->lastFrameParity == this->currentFrameParity)
				{
					x++;
					continue;
				}

				if(light->isInRadius(*obj))
				{
					posx  = obj->position.x;
					posx -= this->player.position.x;
					posx += this->defShiftx;

					posy = obj->position.y;
					posy -= this->player.position.y;
					posy += this->defShifty;

					sprite.setTexture(*obj->texture);
					sprite.setPosition(posx, posy);
					this->parentWindow->draw(sprite);
					obj->lastFrameParity = this->currentFrameParity;
				}
			}

			dobj = this->level.getObject(x,y);
			if(dobj != nullptr)
			{
				if(light->isInRadius(*obj))
				{
					posx  = dobj->position.x;
					posx -= this->player.position.x;
					posx += this->defShiftx+8;

					posy = dobj->position.y;
					posy -= this->player.position.y;
					posy += this->defShifty+8;

					dobj->sprite.update();
					auto dsprite = dobj->sprite.getFrame();
					dsprite.setPosition(posx, posy);
					this->parentWindow->draw(dsprite);
				}
			}
			++x;
		}
	}
}

void GameScene::drawStats()
{
	this->torchState.draw(*this->parentWindow);
	this->webState.draw(*this->parentWindow);
}

sceneID GameScene::switchScene()
{
	puts("Switching to GAMESCENE");

	for(LightSource* plight: this->getLightSources())
	{
		printf("LIGHT: %f %f %f\n",
				*(plight->posx), *(plight->posy), plight->getRadius());
	}

	return this->eventLoop();
}

void GameScene::placeTorch()
{
	int32_t x = (int32_t)this->player.position.x / 32;
	int32_t y = (int32_t)this->player.position.y / 32;
	Object* obj = this->level.getMapObject(x,y);

	if(obj->type != Object::Type::Ground)
		return;

	if(this->torchState.value > 0)
	{
		this->spawnLight(x,y);
		--this->torchState.value;
	}

	printf("Torch count: %u\n",this->torchState.value);
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
	
	this->level.removeObject(this->level.getObject(x,y));
	this->removeLightSource(static_cast<LightSource*>(dynamic_cast<OTorch*>(obj)));

	++this->torchState.value;
}

void GameScene::spawnLight(int32_t x, int32_t y)
{
	OTorch* tobj;
	
	tobj = new OTorch(x*Level::defaultTileWidth,y*Level::defaultTileHeight);
	tobj->isBlocking = false;
	tobj->setSprite({TextureManager::torch, 0, 0, 9, 15, 3, 0.25f});

	this->level.insertObject(static_cast<DynamicObject*>(tobj));

	this->registerLightSource(static_cast<LightSource*>(tobj));
}

void GameScene::renderFrame()
{
		this->parentWindow->clear(sf::Color::Black);
		
		this->drawObjects();
		
		this->playerMoveIfValid();
		this->player.updateDirections();
		this->player.updateOrientation();
		this->drawPlayer();
	
		if(this->smoothDarkness)
		{
			/*** Might cause performance hit  ***/
			this->LightManager::applyDarkness(*this->parentWindow,
				this->player.position.x - this->defShiftx,
				this->player.position.y - this->defShifty);
		}

		this->drawStats();
		
		this->currentFrameParity = !this->currentFrameParity;
		this->parentWindow->display();
}

void GameScene::checkLogic()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		int32_t posx = this->player.position.x/32.0f;
		int32_t posy = this->player.position.y/32.0f;
		
		auto obj = this->level.getObject(posx, posy+1);
		if(obj != nullptr && obj->type == Object::Type::Target)
		{
			this->level.removeObject(obj);
			--this->webState.value;
		}
	}

	if (this->clock.getElapsedTime().asSeconds() < 2)
		return;

	this->clock.restart();

	while(true)
	{
		auto randPos = rand()%this->level.getTotalMapSize();
		auto randPosX = randPos%this->level.mapHeader.mapWidth;
		auto randPosY = randPos/this->level.mapHeader.mapHeight;

		auto obj = this->level.getMapObject(randPosX, randPosY);
		if(obj == nullptr)
			continue;

		if(obj->type != Object::Type::Ground)
			continue;

		auto testweb = new DynamicObject(Object::Type::Target, &TextureManager::web,
			{static_cast<float>(randPosX*Level::defaultTileWidth),
			 static_cast<float>(randPosY*Level::defaultTileHeight)});
		testweb->setSprite({TextureManager::web, 0, 0, 32, 32, 1, 0.0f, 1.0f, 1.0f});
		this->level.insertObject(testweb);
		++this->webState.value;

		return; // Breaks while
 	}
}



