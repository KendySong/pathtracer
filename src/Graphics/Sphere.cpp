#include "Sphere.hpp"

Sphere::Sphere() : Sphere(glm::vec3(0), 1)
{

}

Sphere::Sphere(glm::vec3 position) : Sphere(position, 1)
{
	
}

Sphere::Sphere(glm::vec3 position, float radius) : position(position), radius(radius), color({ 1, 1, 1 })
{

}

Sphere::Sphere(float radius) : Sphere(glm::vec3(0), radius)
{

}

bool Sphere::hit(const Ray& ray, HitContext& context) const
{
	glm::vec3 oc = this->position - ray.origin;

	float a = glm::dot(ray.direction, ray.direction);
	float b = -2 * glm::dot(ray.direction, oc);
	float c = glm::dot(oc, oc) - this->radius * this->radius;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		return false;
	}

	float t1 = (-b - sqrt(discriminant)) / (2 * a);
	float t2 = (-b + sqrt(discriminant)) / (2 * a);

	if (t1 > 0)
	{
		context.t = t1;
	}
	else if (t2 > 0)
	{
		context.t = t2;
	}
	else 
	{
		return false;
	}

	context.point = ray.at(context.t);
	context.normal = (context.point - this->position) / this->radius;
	return true;
}