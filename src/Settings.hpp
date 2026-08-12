#pragma once
#include <cstdint>
#include <iostream>
#include <glm/glm.hpp>

class Settings
{
public:
    static Settings instance;

    static const int        seed;
    static const glm::ivec2 screen;
    static       glm::ivec2 resolution;
    static       float      aspectRatio;

private:
    Settings();
};