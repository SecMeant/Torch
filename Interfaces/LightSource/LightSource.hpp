#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../../utility/stdshared.hpp"
#include "../../Object/Object.hpp"

class LightSource
{
public:
	float *posx;
	float *posy;

	LightSource(float *px, float *py, float lr)
	:posx(px), posy(py), radius(lr), tileradius(lr/32.0f){}

	// Sets new radius and calculates tile radius
	inline void setRadius(float newRadius);
	
	// Radius in pixels
	inline float getRadius();

	// Radius in tiles
	// Stored to speed up calculating it for every time
	// light needs it for rendering
	inline int32_t getTileRadius();
	
	// arg Obj should have origin set to its middle
	bool isInRadius(sf::FloatRect obj) const;
	bool isInRadius(const Object &obj) const;

	static float getDistanceBetween
	(sf::Vector2f v1, sf::Vector2f v2);

private:
	float radius;
	int32_t tileradius;

};

void LightSource::setRadius(float newRadius)
{
	this->radius = newRadius;
	this->tileradius = newRadius / 32.0f;
}

float LightSource::getRadius()
{
	return this->radius;
}

int32_t LightSource::getTileRadius()
{
	return this->tileradius;
}

#endif // LIGHTSOURCE_H
