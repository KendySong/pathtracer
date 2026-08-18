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
	float refractionRatio	= context.frontFace ? 1.0f / refractionIndex : refractionIndex;
	float cosTheta			= std::min(glm::dot(-ray.direction, context.normal), 1.0f);
	bool  canRefract		= refractionRatio * sqrt(1 - cosTheta * cosTheta) < 1.0;

	glm::vec3 direction;
	if (canRefract)
	{
		direction = glm::refract(ray.direction, context.normal, refractionRatio);
	}
	else
	{
		direction = glm::reflect(ray.direction, context.normal);
	}

	scattered   = Ray(context.point, direction);
	attenuation = glm::vec3(1.0f);
	return true;
}

float Dieletric::reflectance(float cos, float refractionRatio)
{
	//https://en.wikipedia.org/wiki/Schlick%27s_approximation
	float r0 = (1 - refractionRatio) / (1 + refractionRatio);
	r0 = r0 * r0;

	return r0 + (1 - r0) * pow((1 - cos), 5);
}