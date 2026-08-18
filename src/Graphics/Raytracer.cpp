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
		Ray scattered;
		glm::vec3 attenuation;
		if (nearestContext.material->scatter(ray, nearestContext, attenuation, scattered))
		{
			return attenuation * Raytracer::trace(scattered, world, depth+1);
		}
		else
		{
			return { 0, 0, 0 };
		}
	}
	
	return glm::mix(glm::vec3(1, 1, 1), glm::vec3(0.5, 0.7, 1.0), (ray.direction.y + 1) / 2);
}