#pragma once
#include <cstdint>

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <glm/glm.hpp>

#include "Color.hpp"
#include "../Settings.hpp"

class FrameBuffer
{
public :
	FrameBuffer(SDL_Renderer* renderer);
	
	void setPixel(std::uint32_t x, std::uint32_t y, std::uint32_t color);
	void setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
	void setPixel(std::uint32_t x, std::uint32_t y, const glm::vec3& color);

	std::uint32_t at(std::uint32_t x, std::uint32_t y);

	void clear();
	void reset();
	std::uint32_t* data();

	SDL_Texture* texture;

private :
	std::uint32_t* p_framebuffer;
	SDL_Renderer*  p_renderer;
};