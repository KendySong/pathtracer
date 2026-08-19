#include "Framebuffer.hpp"

FrameBuffer::FrameBuffer(SDL_Renderer* renderer) : p_renderer(renderer)
{
	p_framebuffer  = nullptr;
	p_accumulation = nullptr;
	sampleCount = 0;

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

void FrameBuffer::addAccumulation(std::uint32_t x, std::uint32_t y, std::uint32_t color)
{
	p_accumulation[y * Settings::iResolution.x + x] += Color::convert(color);
}

void FrameBuffer::addAccumulation(std::uint32_t x, std::uint32_t y, glm::vec3& color)
{
	p_accumulation[y * Settings::iResolution.x + x] += color;
}

glm::vec3 FrameBuffer::getAccumulation(std::uint32_t x, std::uint32_t y)
{
	return p_accumulation[y * Settings::iResolution.x + x];
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

	sampleCount = 0;
	p_framebuffer  = new std::uint32_t[Settings::iResolution.x * Settings::iResolution.y];
	p_accumulation = new glm::vec3[Settings::iResolution.x * Settings::iResolution.y];
	
	memset(p_framebuffer,  0, sizeof(std::uint32_t) * Settings::iResolution.x * Settings::iResolution.y);
	memset(p_accumulation, 0, sizeof(std::uint32_t) * Settings::iResolution.x * Settings::iResolution.y);

	texture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, Settings::iResolution.x, Settings::iResolution.y);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

std::uint32_t* FrameBuffer::data()
{
	return p_framebuffer;
}