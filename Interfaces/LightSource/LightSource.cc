#include "LightSource.hpp"
#include <math.h>

// Placeholder until better solution comes
// Used to remove object suddenly appearing on border of light
constexpr float radiusShift = 32;

bool LightSource::isInRadius(sf::FloatRect obj) const
{
	sf::Vector2f p1(posx, posy);
	sf::Vector2f p2(obj.left, obj.top);
	if(getDistanceBetween(p1,p2) < this->radius+32)
		return true;
	return false;
}

bool LightSource::isInRadius(const Object &obj) const
{
	sf::Vector2f p1(posx, posy);
	sf::Vector2f p2 = obj.getObjectCoords();
	if(getDistanceBetween(p1,p2) < this->radius+32)
		return true;
	return false;
}

float LightSource::getDistanceBetween
(sf::Vector2f v1, sf::Vector2f v2)
{
	float ret;
	ret  = (v1.x-v2.x)*(v1.x-v2.x);
	ret += (v1.y-v2.y)*(v1.y-v2.y);
	ret = sqrt(ret);

	return ret;
}
