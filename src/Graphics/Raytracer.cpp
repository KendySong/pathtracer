#include "Raytracer.hpp"

glm::vec3 Raytracer::trace(const Ray& ray, const std::vector<Hittable*>& world)
{
	HitContext context;
	for (size_t i = 0; i < world.size(); i++)
	{
		if (world[i]->hit(ray, context))
		{
			glm::vec3 n = Math::remapToUV(context.normal);
			return n;
		}
	}

	

	return glm::mix(glm::vec3(1, 1, 1), glm::vec3(0.5, 0.7, 1.0), (ray.direction.y + 1) / 2);
}