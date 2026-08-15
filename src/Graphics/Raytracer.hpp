#pragma once
#include <vector>

#include "Ray.hpp"
#include "Color.hpp"
#include "Math.hpp"
#include "Sphere.hpp"

class Raytracer
{
public :
	static glm::vec3 trace(const Ray& ray, const Sphere& sphere);

private :
	static float hit(const Ray& ray, const Sphere& sphere);
};