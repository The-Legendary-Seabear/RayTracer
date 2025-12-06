#pragma once
#include "Color.h"

class Object
{
public:
	Object() = default;
	Object(const color3_t& color) ? ? ?



		virtual bool Hit(const ray_t & ray, float minDistance, float maxDistance, raycastHit_t & raycastHit) < make pure virtual >

protected:
	color3_t color;
};
