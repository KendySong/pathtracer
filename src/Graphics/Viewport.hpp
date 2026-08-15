#pragma once
#include <glm/glm.hpp>

#include "Math.hpp"
#include "Ray.hpp"
#include "../Settings.hpp"

class Viewport
{
public :
	Viewport(float fov);
	void reset();
	Ray generate(int x, int y);

	glm::vec3 dx;
	glm::vec3 dy;
	float fov;
	
	glm::vec3 position;
	glm::vec3 direction;	//To implement future camera movement

	glm::vec3 startPixel;

private :
	float m_focalDistance;
};