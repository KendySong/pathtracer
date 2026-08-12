#include "Settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const int			Settings::seed = time(nullptr);
const std::uint32_t Settings::width = 1280;
const std::uint32_t Settings::height = 720;

glm::ivec2			Settings::resolution = glm::ivec2(1280, 720);