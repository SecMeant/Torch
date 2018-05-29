#include "LightManager.hpp"

LightManager::LightManager(sf::Vector2u windowSize)
{
	if(not this->darkness.create(windowSize.x, windowSize.y))
	{
		puts("Error while creating darkness in LightManager.");
	}
}

bool LightManager::registerLightSource
(LightSource* ls)
{
	for(auto light:this->lightSources)
	{
		if(ls == light)
			return false;
	}

	this->lightSources.push_back(ls);
	return true;
}

void LightManager::removeLightSource
(LightSource* ls)
{
	typedef std::vector<LightSource*>::iterator light_it;

	light_it light = this->lightSources.begin();
	light_it end = this->lightSources.end();
	while(light != end)
	{
		if(ls == *light)
		{
			this->lightSources.erase(light);
			return;
		}
		light++;
	}
}

void LightManager::applyDarkness
(sf::RenderWindow &wnd, float originx, float originy)
{
	static sf::CircleShape circle;

	circle.setFillColor(sf::Color::Transparent);
	this->darkness.clear(sf::Color::Black);
	for(const auto light:this->lightSources)
	{
		float posx;
		posx  = light->posx;
		posx -= originx;

		float posy;
		posy  = light->posy;
		posy -= originy;

		circle.setRadius(light->radius);
		circle.setOrigin(light->radius, light->radius);
		circle.setPosition(posx, posy);
		this->darkness.draw(circle, sf::BlendNone);
		this->darkness.display();
	}
	wnd.draw(sf::Sprite(this->darkness.getTexture()));
}
