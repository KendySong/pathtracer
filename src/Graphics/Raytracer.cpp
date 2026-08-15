#include "Raytracer.hpp"

glm::vec3 Raytracer::trace(const Ray& ray, const Sphere& sphere)
{
	if (hit(ray, sphere))
	{
		return sphere.color;
	}

	return glm::mix(glm::vec3(1, 1, 1), glm::vec3(0.5, 0.7, 1.0), (ray.direction.y + 1) / 2);
}

bool Raytracer::hit(const Ray& ray, const Sphere& sphere)
{
	glm::vec3 oc = sphere.position - ray.origin;

	float a = glm::dot(ray.direction, ray.direction);
	float b = -2 * glm::dot(ray.direction, oc);
	float c = glm::dot(oc, oc) - sphere.radius * sphere.radius;

	float discriminant = b * b - 4 * a * c;
	return discriminant >= 0;
}