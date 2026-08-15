#pragma once
#include <glm/glm.hpp>

class Sphere
{
public :
    Sphere();
    Sphere(glm::vec3 position);
    Sphere(glm::vec3 position, float radius);
    Sphere(float radius);

    glm::vec3 position;
    glm::vec3 color;
    float radius;
};