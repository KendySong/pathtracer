#include "Hittable.hpp"

void HitContext::setFaceNormal(const Ray& ray, const glm::vec3& outNormal)
{
	//The normal will point against the ray
	frontFace = glm::dot(ray.direction, outNormal) < 0;
	normal = frontFace ? outNormal : -outNormal;
}