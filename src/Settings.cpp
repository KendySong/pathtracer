#include "Settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const int			Settings::seed					= time(nullptr);
const glm::ivec2	Settings::screen				= glm::ivec2(1600, 900);
glm::ivec2			Settings::iResolution			= glm::ivec2(320, 180);
glm::vec2			Settings::resolution			= glm::vec2(iResolution.x, iResolution.y);
float				Settings::aspectRatio			= Settings::resolution.x / Settings::resolution.y;
bool				Settings::antialiasing			= true;
int					Settings::sampleAA				= 4;	// useless upper 25	
bool				Settings::continiousRendering	= true;
int					Settings::bounceLimit			= 4;
float				Settings::minT					= 0.01;
bool				Settings::gammaCorrection		= false;