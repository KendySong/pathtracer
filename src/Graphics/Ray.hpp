#pragma once
#include <glm/glm.hpp>

class Ray
{
public :
	Ray();
	Ray(glm::vec3 origin, glm::vec3 direction);

	glm::vec3 at(float t);

	glm::vec3 origin;
	glm::vec3 direction;
};