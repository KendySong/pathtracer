#include "Settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const int			Settings::seed			= time(nullptr);
const glm::ivec2	Settings::screen		= glm::ivec2(1280, 720);
glm::ivec2			Settings::resolution	= glm::ivec2(640, 360);
float				Settings::aspectRatio	= Settings::resolution.x / Settings::resolution.y;