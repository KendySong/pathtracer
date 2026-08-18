#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "../Settings.hpp"
#include "Hittable.hpp"
#include "Material.hpp"

class Sphere : public Hittable
{
public :
    Sphere() = default;
    Sphere(Material* material);
    Sphere(glm::vec3 position, Material* material);
    Sphere(glm::vec3 position, float radius, Material* material);
    Sphere(float radius, Material* material);

    bool hit(const Ray& ray, HitContext& context) const override;

    glm::vec3 position;
    float radius;
    Material* material;
};