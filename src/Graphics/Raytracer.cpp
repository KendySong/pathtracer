#include "Raytracer.hpp"

glm::vec3 Raytracer::trace(const Ray& ray, const std::vector<Hittable*>& world, int depth)
{
	if (depth > Settings::bounceLimit)
	{
		return { 0, 0, 0 };
	}

	//Search for the nearest object of the sphere
	bool hitAnything = false;
	HitContext nearestContext;
	float closestT = std::numeric_limits<float>::infinity();
	for (size_t i = 0; i < world.size(); i++)
	{
		HitContext current;
		if (world[i]->hit(ray, current))
		{
			if (current.t < closestT)
			{
				closestT		= current.t;
				nearestContext	= current;
				hitAnything		= true;
			}
		}
	}

	if (hitAnything)
	{	
		glm::vec3 direction = randomHemisphere(nearestContext.normal);
		return 0.5 * Raytracer::trace(Ray(nearestContext.point, direction), world, depth+1);
	}
	

	return glm::mix(glm::vec3(1, 1, 1), glm::vec3(0.5, 0.7, 1.0), (ray.direction.y + 1) / 2);
}

glm::vec3 Raytracer::randomHemisphere(const glm::vec3& n)
{
	glm::vec3 unitSphere = Math::randomv(-1, 1);

	//Check if random vector is pointing outside
	if (glm::dot(n, unitSphere) > 0)
	{
		return unitSphere;
	}
	else
	{
		return -unitSphere;
	}
}