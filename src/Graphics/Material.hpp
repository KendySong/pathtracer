#pragma once

#include <glm/gtc/random.hpp>

#include "Ray.hpp"
#include "Math.hpp"
#include "Hittable.hpp"

class Material
{
public :
	virtual ~Material() = default;

	virtual bool scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const;
private :

};

class Lambertian : public Material
{
public :
	Lambertian() = default;
	Lambertian(const glm::vec3& albedo);

	bool scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const override;
	
	glm::vec3 albedo;
};

class Metal : public Material
{
public:
	Metal() = default;
	Metal(const glm::vec3& albedo);

	bool scatter(const Ray& ray, const HitContext& context, glm::vec3& attenuation, Ray& scattered) const override;

	glm::vec3 albedo;
};