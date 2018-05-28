#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../../utility/stdshared.hpp"
#include "../../Level/Level.hpp"

class LightSource
{
public:
	float& posx;
	float& posy;
	float lightRadius;

	LightSource(float& px, float& py, float lr)
	:posx(px), posy(py), lightRadius(lr){}
	
	// arg Obj should have origin set to its middle
	bool isInRadius(sf::FloatRect obj) const;
	bool isInRadius(const Level::mapObject &obj) const;

	static float getDistanceBetween
	(sf::Vector2f v1, sf::Vector2f v2);
};

#endif // LIGHTSOURCE_H
