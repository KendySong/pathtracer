#include "color.hpp"

std::uint32_t Color::convert(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	return 0xFF000000 | (r << 16) | (g << 8) | b;
}

std::uint32_t Color::convert(const glm::vec3& color)
{
	return 0xFF000000 | ((0x000000FF & (std::uint8_t)color.x) << 16) | ((0x000000FF & (std::uint8_t)color.y) << 8) | (0x000000FF & (std::uint8_t)color.z);
}

SDL_Color Color::convert(std::uint32_t colorARGB)
{
	return { 
		(std::uint8_t)((0x00FF0000 & colorARGB) >> 16), 
		(std::uint8_t)((0x0000FF00 & colorARGB) >> 8 ), 
		(std::uint8_t)(0x000000FF & colorARGB), 
		(std::uint8_t)((0xFF000000 & colorARGB) >> 24)
	};
}