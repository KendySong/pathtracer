#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "Hittable.hpp"

class Sphere : public Hittable
{
public :
    Sphere();
    Sphere(glm::vec3 position);
    Sphere(glm::vec3 position, float radius);
    Sphere(glm::vec3 position, float radius, glm::vec3 color);
    Sphere(float radius);

    bool hit(const Ray& ray, HitContext& context) const override;

    glm::vec3 position;
    glm::vec3 color;
    float radius;
};