#include "Settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const int			Settings::seed			= time(nullptr);
const glm::ivec2	Settings::screen		= glm::ivec2(1280, 720);
glm::ivec2			Settings::iResolution	= glm::ivec2(640, 360);
glm::vec2			Settings::resolution	= glm::vec2(0);
float				Settings::aspectRatio	= Settings::iResolution.x / Settings::iResolution.y;