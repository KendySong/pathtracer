#include "Sphere.hpp"

Sphere::Sphere() : Sphere(glm::vec3(0), 1)
{

}

Sphere::Sphere(glm::vec3 position) : Sphere(position, 1)
{
	
}

Sphere::Sphere(glm::vec3 position, float radius) : position(position), radius(radius)
{

}

Sphere::Sphere(float radius) : Sphere(glm::vec3(0), radius)
{

}