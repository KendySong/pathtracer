#pragma once
#include <glm/glm.hpp>

#include "Ray.hpp"

class Material;

struct HitContext
{
public :
    float t;
    glm::vec3 point;
    glm::vec3 normal;
    bool frontFace;
    Material* material;

    void setFaceNormal(const Ray& ray, const glm::vec3& outNormal);
};

class Hittable
{
public :
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, HitContext& context) const = 0;
private :
};