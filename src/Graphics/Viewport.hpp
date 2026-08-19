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
	Ray generateAA(int x, int y);

	float fov;
	glm::vec3 position;
	glm::vec3 lookAt;
	
	glm::vec3 startPixel;
	glm::vec3 dx;
	glm::vec3 dy;

private :
	float m_focalDistance;
	glm::vec3 m_up;

	glm::vec3 m_u;
	glm::vec3 m_v;
	glm::vec3 m_w;
};