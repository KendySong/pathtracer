#pragma once

#include <glm/glm.hpp>

class Math
{
public :
	static glm::vec3 remapToUV(const glm::vec3& v);
	static glm::vec3 remapToNDC(const glm::vec3& v);
};

glm::vec3 operator/(const glm::vec3& v, int s);
glm::vec3 operator*(double s, const glm::vec3& v);
glm::vec3 operator*(const glm::vec3& v, double s);