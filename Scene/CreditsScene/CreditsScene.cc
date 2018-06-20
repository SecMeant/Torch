#include "CreditsScene.hpp"

CreditsScene::CreditsScene(const std::shared_ptr<sf::RenderWindow> &wnd)
:Scene(wnd), mainsceneTextBtn(TextureManager::defaultFont,{170,170,170},{255,255,255})
{
	puts("CREDITSSCENE CREATION MESSAGE");
	this->initializeButtons();
	this->setBackground(TextureManager::creditssceneBackground);
}

void CreditsScene::initializeButtons()
{
	this->mainsceneTextBtn.text.setPosition(550,600);
	this->mainsceneTextBtn.text.setCharacterSize(48);
	this->mainsceneTextBtn.text.setString("Return");
}

void CreditsScene::handleMouseHovers
(const sf::Event &ev)
{
	this->mainsceneTextBtn.handleHoverEvent(ev);
}

sceneID CreditsScene::handleMouseReleased
(const sf::Event &ev)
{
	sceneID ret = sceneID::none;

	if(this->mainsceneTextBtn.clicked(ev))
		ret = sceneID::mainmenu;

	return ret;
}

sceneID CreditsScene::eventLoop()
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
		this->parentWindow->draw(this->mainsceneTextBtn.text);
		this->parentWindow->display();
	}
	return {sceneID::none};
}

sceneID CreditsScene::switchScene()
{
	puts("Switching to MAINSCENE");

	this->mainsceneTextBtn.reset();

	return this->eventLoop();
}
