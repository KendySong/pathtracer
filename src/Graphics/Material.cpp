#include "Material.hpp"

bool Material::scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const
{
	return false;
}

Lambertian::Lambertian(const glm::vec3& albedo) : albedo(albedo)
{

}

bool Lambertian::scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 direction = context.normal + glm::sphericalRand(1.0f);
	if (Math::nearZero(direction))
	{
		direction = context.normal;
	}
	scattered = Ray(context.point, glm::normalize(direction));
	attenuation = albedo;
	return true;
}

Metal::Metal(const glm::vec3& albedo) : albedo(albedo)
{

}

bool Metal::scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 direction = glm::reflect(ray.direction, context.normal);
	scattered = Ray(context.point, direction);
	attenuation = albedo;
	return true;
}