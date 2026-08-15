#include "Raytracer.hpp"

glm::vec3 Raytracer::trace(const Ray& ray, const Sphere& sphere)
{
	float t = hit(ray, sphere);
	if (t >= 0)
	{
		glm::vec3 n = Math::remapToUV(glm::normalize(ray.at(t) - sphere.position));
		return n;
	}


	return glm::mix(glm::vec3(1, 1, 1), glm::vec3(0.5, 0.7, 1.0), (ray.direction.y + 1) / 2);
}

float Raytracer::hit(const Ray& ray, const Sphere& sphere)
{
	glm::vec3 oc = sphere.position - ray.origin;

	float a = glm::dot(ray.direction, ray.direction);
	float b = -2 * glm::dot(ray.direction, oc);
	float c = glm::dot(oc, oc) - sphere.radius * sphere.radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		float t1 = (-b - sqrt(discriminant)) / (2 * a);	
		if (t1 > 0)
		{
			return t1;
		}

		float t2 = (-b + sqrt(discriminant)) / (2 * a);
		if (t2 > 0)
		{
			return t2;
		}
	}

	return -1;
}