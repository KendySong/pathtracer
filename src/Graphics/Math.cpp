#include "Math.hpp"


glm::vec3 Math::remapToUV(const glm::vec3 & v)
{
	//Remap interval from [-1;1] to [0;1]
	return (v + glm::vec3(1)) / 2;
}

glm::vec3 Math::remapToNDC(const glm::vec3& v)
{
	//Remap interval from [0;1] to [-1;1]
	return v * 2 - glm::vec3(1);
}

float Math::random()
{
	//return [0;1[
	return (float)rand() / (RAND_MAX + 1);
}

float Math::random(float min, float max)
{
	//return [min;max[
	return min + (max - min) * random();
}


glm::vec3 Math::clamp(const glm::vec3& v, float min, float max)
{
	return { glm::clamp(v.x, min, max), glm::clamp(v.y, min, max) , glm::clamp(v.z, min, max) };
}





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