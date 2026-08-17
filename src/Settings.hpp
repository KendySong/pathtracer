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
    static       glm::ivec2 iResolution;
    static       glm::vec2  resolution;
    static       float      aspectRatio;
    static       bool       antialiasing;
    static       int        sampleAA;
    static       bool       continiousRendering;
    static       int        bounceLimit;
    static       float      minT;


private:
    Settings();
};