#pragma once

#include <glm/glm.hpp>

#include "../../Settings.hpp"

class Resolution
{
public :
    static glm::ivec2 getFromIndex(int index);

    inline static const char* format[]  = { "1920x1080", "1600x900", "1280x720", "640x360", "320x180", "160x90", "80x45", "32x18" };
    inline static const int size        = 8; 
};