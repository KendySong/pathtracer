#pragma once
#include <cstdint>

#include <SDL3/SDL.h>

#include <glm/glm.hpp>

class Color
{
public :
    static std::uint32_t convert(std::uint8_t r, std::uint8_t g, std::uint8_t b);
    static std::uint32_t convert(const glm::vec3& color);
    static SDL_Color convert(std::uint32_t colorARGB);
};