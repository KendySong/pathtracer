#include "Raytracer.hpp"

glm::vec3 Raytracer::trace(const Ray& ray, const Sphere& sphere)
{
	HitContext context;
	if (sphere.hit(ray, context))
	{
		glm::vec3 n = Math::remapToUV(context.normal);
		return n;
	}

	return glm::mix(glm::vec3(1, 1, 1), glm::vec3(0.5, 0.7, 1.0), (ray.direction.y + 1) / 2);
}