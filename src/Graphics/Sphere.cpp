#include "Sphere.hpp"

Sphere::Sphere(Material* material) : Sphere(glm::vec3(0), 1, material)
{
	
}

Sphere::Sphere(glm::vec3 position, Material* material) : Sphere(position, 1, material)
{
	
}

Sphere::Sphere(glm::vec3 position, float radius, Material* material) : position(position), radius(radius), material(material)
{

}

Sphere::Sphere(float radius, Material* material) : Sphere(glm::vec3(0), radius, material)
{

}

bool Sphere::hit(const Ray& ray, HitContext& context) const
{	
	glm::vec3 oc = this->position - ray.origin;
	
	float a = 1;													//normally equal to glm::length2(ray.direction) but ray.direction is normalized
	float h = glm::dot(ray.direction, oc);
	float c = glm::length2(oc) - this->radius * this->radius;
	float discriminant = h * h - a * c;

	if (discriminant < 0)
	{
		return false;
	}

	float t1 = (h - sqrt(discriminant)) / a;
	float t2 = (h + sqrt(discriminant)) / a;

	if (t1 > 0 && t1 > Settings::minT)
	{
		context.t = t1;
	}
	else if (t2 > 0 && t2 > Settings::minT)
	{
		context.t = t2;
	}
	else
	{
		return false;
	}

	context.point = ray.at(context.t);
	context.setFaceNormal(ray, (context.point - this->position) / this->radius);
	context.material = material;
	return true;
}