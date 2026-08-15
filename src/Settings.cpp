#include "Settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const int			Settings::seed			= time(nullptr);
const glm::ivec2	Settings::screen		= glm::ivec2(1280, 720);
glm::ivec2			Settings::iResolution	= glm::ivec2(320, 180);
glm::vec2			Settings::resolution	= glm::vec2(iResolution.x, iResolution.y);
float				Settings::aspectRatio	= Settings::resolution.x / Settings::resolution.y;
