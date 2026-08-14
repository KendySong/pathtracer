#include "Math.hpp"

glm::vec3 operator/(const glm::vec3& v, int s)
{
	return v / (float)s;
}

glm::vec3 operator*(double s, const glm::vec3& v)
{
	return {(float)s * v.x, (float)s * v.y , (float)s * v.z };
}

glm::vec3 operator*(const glm::vec3& v, double s)
{
	return { (float)s * v.x, (float)s * v.y , (float)s * v.z };
}