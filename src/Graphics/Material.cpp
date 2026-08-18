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

Metal::Metal(const glm::vec3& albedo, float fuzz) : albedo(albedo), fuzz(fuzz)
{

}

bool Metal::scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 direction = glm::reflect(ray.direction, context.normal);
	if (fuzz != 0)
	{
		direction += glm::sphericalRand(fuzz);
	}
	 

	scattered = Ray(context.point, glm::normalize(direction));
	attenuation = albedo;
	return glm::dot(scattered.direction, context.normal) > 0;
}

Dieletric::Dieletric(float refractionIndex) : refractionIndex(refractionIndex)
{

}


bool Dieletric::scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const
{
	float refractionRatio = context.frontFace ? 1 / refractionIndex : refractionIndex;
	scattered	= Ray(context.point, glm::refract(ray.direction, context.normal, refractionRatio));
	attenuation = glm::vec3(1.0f);

	return true;
}