#include "OTorch.hpp"

OTorch::OTorch(float x, float y)
:Object(&TextureManager::nulltexture, sf::Vector2f(x,y),
				sf::Vector2f(40,40)),
 LightSource(&this->position.x, &this->position.y, defRadius){}

OTorch::OTorch(OTorch &t)
:Object(t.texture, t.position, t.size),
 LightSource(&this->position.x, &this->position.y, defRadius)
{puts("called");}

OTorch::OTorch(OTorch &&t)
:Object(t.texture, t.position, t.size),
 LightSource(&this->position.x, &this->position.y, defRadius)
{puts("called");}
