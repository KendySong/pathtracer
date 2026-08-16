#pragma once
#include <glm/glm.hpp>

#include "Hitabble.hpp"

class Sphere : public Hittable
{
public :
    Sphere();
    Sphere(glm::vec3 position);
    Sphere(glm::vec3 position, float radius);
    Sphere(float radius);

    bool hit(const Ray& ray, HitContext& context) const override;

    glm::vec3 position;
    glm::vec3 color;
    float radius;
};