#ifndef TORCH_H
#define TORCH_H

#include "../../utility/stdshared.hpp"
#include "../DynamicObject/DynamicObject.hpp"
#include "../../Interfaces/LightSource/LightSource.hpp"

class OTorch:public DynamicObject, public LightSource
{
public:
	static constexpr float defRadius = 140.0f;

	OTorch(float x, float y);
	OTorch(OTorch &t);
	OTorch(OTorch &&t);

	~OTorch();
	OTorch& operator=(const OTorch&) = delete;
	OTorch(const OTorch&) = delete;
};

#endif // TORCH_H
