#pragma once
#include <cstdint>
#include <iostream>
#include <glm/glm.hpp>

class Settings
{
public:
    static Settings instance;

    static const int           seed;
    static const std::uint32_t width;
    static const std::uint32_t height;

    static       glm::ivec2 resolution;

private:
    Settings();
};