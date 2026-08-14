#include "Framebuffer.hpp"

FrameBuffer::FrameBuffer(SDL_Renderer* renderer) : p_renderer(renderer)
{
	p_framebuffer = nullptr;

	this->reset();
}

void FrameBuffer::setPixel(std::uint32_t x, std::uint32_t y, std::uint32_t color)
{
	p_framebuffer[y * Settings::iResolution.x + x] = color;
}

void FrameBuffer::setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	p_framebuffer[y * Settings::iResolution.x + x] = Color::convert(r, g, b);
}

void FrameBuffer::setPixel(std::uint32_t x, std::uint32_t y, const glm::vec3& color)
{
	p_framebuffer[y * Settings::iResolution.x + x] = Color::convert(color);
}

std::uint32_t FrameBuffer::at(std::uint32_t x, std::uint32_t y)
{
	return p_framebuffer[y * Settings::iResolution.x + x];
}

void FrameBuffer::clear()
{
	memset(p_framebuffer, 0, Settings::iResolution.x * Settings::iResolution.y * sizeof(std::uint32_t));
}

void FrameBuffer::reset()
{
	delete[] p_framebuffer;

	p_framebuffer = new std::uint32_t[Settings::iResolution.x * Settings::iResolution.y];
	memset(p_framebuffer, 0, sizeof(std::uint32_t) * Settings::iResolution.x * Settings::iResolution.y);

	texture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, Settings::iResolution.x, Settings::iResolution.y);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

std::uint32_t* FrameBuffer::data()
{
	return p_framebuffer;
}