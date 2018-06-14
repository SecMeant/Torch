#ifndef TORCH_H
#define TORCH_H

#include "../../utility/stdshared.hpp"
#include "../Object.hpp"
#include "../../Interfaces/LightSource/LightSource.hpp"

class OTorch:public Object, public LightSource
{
public:
	static constexpr float defRadius = 140.0f;

	OTorch(float x, float y);
	OTorch(OTorch &t);
	OTorch(OTorch &&t);

	~OTorch();
};

#endif // TORCH_H
