#include "Viewport.hpp"

Viewport::Viewport(float fov) : fov(fov)
{
	position		= glm::vec3(0);
	direction		= glm::vec3(0, 0, -1);
	m_focalDistance	= 1;

	reset();
}

void Viewport::reset()
{	
	//Compute viewport size with fov
	float width = 2 * tan(glm::radians(fov) / 2);
	float height = width / Settings::aspectRatio;

	glm::vec3 u = glm::vec3(width, 0, 0);
	glm::vec3 v = glm::vec3(0, -height, 0);

	dx = u / Settings::resolution.x;
	dy = v / Settings::resolution.y;

	glm::vec3 startCorner = position - m_focalDistance * direction - (u / 2) - (v / 2);
	startPixel = startCorner + 0.5 * (dx + dy);
}

Ray Viewport::generate(int x, int y)
{
	glm::vec3 direction = glm::normalize((startPixel + (dy * y) + (dx * x)) - position);
	return { position, direction };
}