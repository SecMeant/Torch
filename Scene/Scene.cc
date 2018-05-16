#include "Scene.hpp"

Scene::Scene
(const std::shared_ptr<sf::RenderWindow> &wnd)
:parentWindow(wnd)
{
	puts("Creating scene");
}

void Scene::initializeBackground()
{
	this->background.texture.loadFromFile(
			this->background.assetPath.c_str());
	this->background.shape.setSize(sf::Vector2f(800,600));
	this->background.shape.setPosition(0,0);
	this->background.shape.setTexture(&this->background.texture);
}

