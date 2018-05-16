#include "Scene.hpp"

Scene::Scene
(const std::shared_ptr<sf::RenderWindow> &wnd)
:parentWindow(wnd)
{
	puts("Creating scene");
}

void Scene::setBackground
(const sf::Texture &tex)
{
	this->background.setPosition(0,0);
	this->background.setTexture(tex);
}

