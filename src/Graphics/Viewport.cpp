#include "Viewport.hpp"

Viewport::Viewport(float fov) : fov(fov)
{
	position		= glm::vec3(0);
	lookAt			= glm::vec3(0);
	m_focalDistance	= 1;
	m_up			= { 0, 1, 0 };

	reset();
}

void Viewport::reset()
{	
	//Compute viewport basis
	m_focalDistance = (position - lookAt).length();
	m_w = glm::normalize(position - lookAt);
	m_u = glm::normalize(glm::cross(m_up, m_w));
	m_v = glm::cross(m_w, m_u);

	//Compute viewport size with fov
	float height = 2 * tan(glm::radians(fov) / 2.0f) * m_focalDistance;
	float width = height * Settings::aspectRatio;

	glm::vec3 u =  width  * m_u;
	glm::vec3 v = -height * m_v;

	dx = u / Settings::resolution.x;
	dy = v / Settings::resolution.y;

	glm::vec3 startCorner = position - m_focalDistance * m_w - (u / 2) - (v / 2);
	startPixel = startCorner + 0.5 * (dx + dy);
}

Ray Viewport::generate(int x, int y)
{
	glm::vec3 direction = glm::normalize((startPixel + (dy * y) + (dx * x)) - position);
	return { position, direction };
}

Ray Viewport::generateAA(int x, int y)
{
	glm::vec2 offset = { Math::random() - 0.5, Math::random() - 0.5 };
	glm::vec3 direction = glm::normalize((startPixel + (dy * (y + offset.y)) + (dx * (x + offset.x))) - position);
	return { position, direction };
}