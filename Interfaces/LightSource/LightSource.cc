#include "LightSource.hpp"
#include <math.h>

bool LightSource::isInRadius(sf::FloatRect obj) const
{
	sf::Vector2f p1(posx, posy);
	sf::Vector2f p2(obj.left, obj.top);
	if(getDistanceBetween(p1,p2) < this->lightRadius)
		return false;
	return true;
}

bool LightSource::isInRadius(const Level::mapObject &obj) const
{
	sf::Vector2f p1(posx, posy);
	sf::Vector2f p2 = obj.getObjectCoords();
	if(getDistanceBetween(p1,p2) < this->lightRadius)
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
