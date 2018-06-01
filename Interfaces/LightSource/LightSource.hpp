#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../../utility/stdshared.hpp"
#include "../../Object/Object.hpp"

class LightSource
{
public:
	float *posx;
	float *posy;
	float radius;

	LightSource(float *px, float *py, float lr)
	:posx(px), posy(py), radius(lr){}
	
	// arg Obj should have origin set to its middle
	bool isInRadius(sf::FloatRect obj) const;
	bool isInRadius(const Object &obj) const;

	static float getDistanceBetween
	(sf::Vector2f v1, sf::Vector2f v2);

};

#endif // LIGHTSOURCE_H
