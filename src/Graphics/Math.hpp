#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

#include <glm/glm.hpp>

class Math
{
public :
	static glm::vec3 remapToUV(const glm::vec3& v);
	static glm::vec3 remapToNDC(const glm::vec3& v);

	static float random();
	static float random(float min, float max);
	static glm::vec3 randomv();
	static glm::vec3 randomv(float min, float max);

	static glm::vec3 clamp(const glm::vec3& v, float min, float max);
	static glm::vec3 linearToGamma2(const glm::vec3& color);

	static bool nearZero(const glm::vec3& v);
};

glm::vec3 operator/(const glm::vec3& v, int s);
glm::vec3 operator*(double s, const glm::vec3& v);
glm::vec3 operator*(const glm::vec3& v, double s);