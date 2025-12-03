#pragma once
#include <glm/glm.hpp>

struct Ray {
public:
	
	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

	glm::vec3 at(float t) const {
		return origin + t * direction;
	}


	glm::vec3 origin;
	glm::vec3 direction;



};
