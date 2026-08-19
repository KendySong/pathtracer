#include "color.hpp"

std::uint32_t Color::convert(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	return 0xFF000000 | (r << 16) | (g << 8) | b;
}

std::uint32_t Color::convert(const glm::vec3& color)
{
	return 0xFF000000 | ((0x000000FF & (std::uint8_t)color.x) << 16) | ((0x000000FF & (std::uint8_t)color.y) << 8) | (0x000000FF & (std::uint8_t)color.z);
}

glm::vec3 Color::convert(std::uint32_t colorARGB)
{
	float r = ((0x00FF0000 & colorARGB) >> 16);
	float g = ((0x0000FF00 & colorARGB) >> 8);
	float b = (0x000000FF & colorARGB);

	return { 
		r,
		g, 
		b
	};
}