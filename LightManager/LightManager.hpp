#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "../utility/stdshared.hpp"
#include "../Interfaces/LightSource/LightSource.hpp"

#include <vector>

class LightManager
{
private:
	sf::RenderTexture darkness;

	std::vector<LightSource*> lightSources;

public:
	LightManager(sf::Vector2u windowSize);

	// Adds light source to list. If given light is already
	// added false is returned. True otherwise.
	bool registerLightSource(LightSource* ls);

	// Removes lightsource from list by its address
	void removeLightSource(LightSource* ls);

	// Makes areas visible only if in light radius
	// Origin x and y describes current camera location
	// All light coordinates will be calculated realtive to it
	void applyDarkness
	(sf::RenderWindow &wnd, float originx, float originy);

	inline const std::vector<LightSource*>& getLightSources() const
	{return this->lightSources;}
};

#endif // LIGHTMANAGER_H
