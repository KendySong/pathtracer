#include "Resolution.hpp"

glm::ivec2 Resolution::getFromIndex(int index)
{
	switch (index)
	{
	case 0 :
		return { 1920, 1080 };
		break;

	case 1:
		return { 1600, 900 };
		break;

	case 2:
		return { 1280, 720 };
		break;

	case 3:
		return { 640, 360 };
		break;

	case 4:
		return { 320, 180 };
		break;

	case 5:
		return { 160, 90 };
		break;

	case 6:
		return { 80, 45 };
		break;

	case 7:
		return { 32, 18 };
		break;

	default :
		return { 320, 180 };
		break;
	}
}